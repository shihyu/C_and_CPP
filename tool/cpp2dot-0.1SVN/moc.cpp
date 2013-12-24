/****************************************************************************
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#include "moc.h"
#include "qdatetime.h"
#include "utils.h"
#include "outputrevision.h"
#include "preprocessor.h"
// for normalizeTypeInternal
//#include <private/qmetaobject_p.h>


// This code is shared with moc.cpp
static QByteArray normalizeTypeInternal(const char *t, const char *e, bool fixScope = false, bool adjustConst = true)
{
    int len = e - t;
    /*
      Convert 'char const *' into 'const char *'. Start at index 1,
      not 0, because 'const char *' is already OK.
    */
    QByteArray constbuf;
    for (int i = 1; i < len; i++) {
        if ( t[i] == 'c'
             && strncmp(t + i + 1, "onst", 4) == 0
             && (i + 5 >= len || !is_ident_char(t[i + 5]))
             && !is_ident_char(t[i-1])
             ) {
            constbuf = QByteArray(t, len);
            if (is_space(t[i-1]))
                constbuf.remove(i-1, 6);
            else
                constbuf.remove(i, 5);
            constbuf.prepend("const ");
            t = constbuf.data();
            e = constbuf.data() + constbuf.length();
            break;
        }
        /*
          We musn't convert 'char * const *' into 'const char **'
          and we must beware of 'Bar<const Bla>'.
        */
        if (t[i] == '&' || t[i] == '*' ||t[i] == '<')
            break;
    }
    if (adjustConst && e > t + 6 && strncmp("const ", t, 6) == 0) {
        if (*(e-1) == '&') { // treat const reference as value
            t += 6;
            --e;
        } else if (is_ident_char(*(e-1))) { // treat const value as value
            t += 6;
        }
    }
    QByteArray result;
    result.reserve(len);

#if 1
    // consume initial 'const '
    if (strncmp("const ", t, 6) == 0) {
        t+= 6;
        result += "const ";
    }
#endif

    // some type substitutions for 'unsigned x'
    if (strncmp("unsigned", t, 8) == 0) {
        // make sure "unsigned" is an isolated word before making substitutions
        if (!t[8] || !is_ident_char(t[8])) {
            if (strncmp(" int", t+8, 4) == 0) {
                t += 8+4;
                result += "uint";
            } else if (strncmp(" long", t+8, 5) == 0) {
                if ((strlen(t + 8 + 5) < 4 || strncmp(t + 8 + 5, " int", 4) != 0) // preserve '[unsigned] long int'
                    && (strlen(t + 8 + 5) < 5 || strncmp(t + 8 + 5, " long", 5) != 0) // preserve '[unsigned] long long'
                   ) {
                    t += 8+5;
                    result += "ulong";
                }
            } else if (strncmp(" short", t+8, 6) != 0  // preserve unsigned short
                && strncmp(" char", t+8, 5) != 0) {    // preserve unsigned char
                //  treat rest (unsigned) as uint
                t += 8;
                result += "uint";
            }
        }
    } else {
        // discard 'struct', 'class', and 'enum'; they are optional
        // and we don't want them in the normalized signature
        struct {
            const char *keyword;
            int len;
        } optional[] = {
            { "struct ", 7 },
            { "class ", 6 },
            { "enum ", 5 },
            { 0, 0 }
        };
        int i = 0;
        do {
            if (strncmp(optional[i].keyword, t, optional[i].len) == 0) {
                t += optional[i].len;
                break;
            }
        } while (optional[++i].keyword != 0);
    }

    while (t != e) {
        char c = *t++;
        if (fixScope && c == ':' && *t == ':' ) {
            ++t;
            c = *t++;
            int i = result.size() - 1;
            while (i >= 0 && is_ident_char(result.at(i)))
                --i;
            result.resize(i + 1);
        }
        result += c;
        if (c == '<') {
            //template recursion
            const char* tt = t;
            int templdepth = 1;
            while (t != e) {
                c = *t++;
                if (c == '<')
                    ++templdepth;
                if (c == '>')
                    --templdepth;
                if (templdepth == 0) {
                    result += normalizeTypeInternal(tt, t-1, fixScope, false);
                    result += c;
                    if (*t == '>')
                        result += ' '; // avoid >>
                    break;
                }
            }
        }
    }

    return result;
}
// only moc needs this function
static QByteArray normalizeType(const char *s, bool fixScope = false)
{
    int len = qstrlen(s);
    char stackbuf[64];
    char *buf = (len >= 64 ? new char[len + 1] : stackbuf);
    char *d = buf;
    char last = 0;
    while(*s && is_space(*s))
        s++;
    while (*s) {
        while (*s && !is_space(*s))
            last = *d++ = *s++;
        while (*s && is_space(*s))
            s++;
        if (*s && ((is_ident_char(*s) && is_ident_char(last))
                   || ((*s == ':') && (last == '<')))) {
            last = *d++ = ' ';
        }
    }
    *d = '\0';
    QByteArray result;
    if (strncmp("void", buf, d - buf) != 0)
        result = normalizeTypeInternal(buf, d, fixScope);
    if (buf != stackbuf)
        delete [] buf;
    return result;
}

bool Moc::parseClassHead(ClassDef *def)
{
    // figure out whether this is a class declaration, or only a
    // forward or variable declaration.
    int i = 0;
    Token token;
    do {
        token = lookup(i++);
        if (token == COLON || token == LBRACE)
            break;
        if (token == SEMIC || token == RANGLE)
            return false;
    } while (token);

    if (!test(IDENTIFIER)) // typedef struct { ... }
        return false;
    QByteArray name = lexem();

    // support "class IDENT name" and "class IDENT(IDENT) name"
    if (test(LPAREN)) {
        until(RPAREN);
        if (!test(IDENTIFIER))
            return false;
        name = lexem();
    } else  if (test(IDENTIFIER)) {
        name = lexem();
    }

    def->qualified += name;
    while (test(SCOPE)) {
        def->qualified += lexem();
        if (test(IDENTIFIER)) {
            name = lexem();
            def->qualified += name;
        }
    }
    def->classname = name;
    if (test(COLON)) {
        do {
            test(VIRTUAL);
            FunctionDef::Access access = FunctionDef::Public;
            if (test(PRIVATE))
                access = FunctionDef::Private;
            else if (test(PROTECTED))
                access = FunctionDef::Protected;
            else
                test(PUBLIC);
            test(VIRTUAL);
            const QByteArray type = parseType().name;
            // ignore the 'class Foo : BAR(Baz)' case
            if (test(LPAREN)) {
                until(RPAREN);
            } else {
                def->superclassList += qMakePair(type, access);
            }
        } while (test(COMMA));
    }
    if (!test(LBRACE))
        return false;
    def->begin = index - 1;
    bool foundRBrace = until(RBRACE);
    def->end = index;
    index = def->begin + 1;
    return foundRBrace;
}

Type Moc::parseType(bool templateType)
{
    Type type;
    bool hasSignedOrUnsigned = false;
    bool isVoid = false;
    type.firstToken = lookup();
    for (;;) {
        switch (next()) {
            case SIGNED:
            case UNSIGNED:
                hasSignedOrUnsigned = true;
                // fall through
            case CONST:
            case VOLATILE:
                type.name += lexem();
                type.name += ' ';
                if (lookup(0) == VOLATILE)
                    type.isVolatile = true;
                continue;
            case Q_MOC_COMPAT_TOKEN:
            case Q_QT3_SUPPORT_TOKEN:
            case Q_INVOKABLE_TOKEN:
            case Q_SCRIPTABLE_TOKEN:
            case Q_SIGNALS_TOKEN:
            case Q_SLOTS_TOKEN:
            case Q_SIGNAL_TOKEN:
            case Q_SLOT_TOKEN:
                type.name += lexem();
                type.isBaseType = isBaseSerializableAttribute(type.name);
                type.isContainer = isContainer(type.name);
                type.m_id = getTypeId(type.name);
                return type;
            default:
                prev();
                break;
        }
        break;
    }
    test(ENUM) || test(CLASS) || test(STRUCT);
    for(;;) {
        switch (next()) {
        case IDENTIFIER:
            // void mySlot(unsigned myArg)
            if (hasSignedOrUnsigned) {
                prev();
                break;
            }
        case CHAR:
        case SHORT:
        case INT:
        case LONG:
            type.name += lexem();
            // preserve '[unsigned] long long', 'short int', 'long int', 'long double'
            if (test(LONG) || test(INT) || test(DOUBLE)) {
                type.name += ' ';
                prev();
                continue;
            }
            break;
        case FLOAT:
        case DOUBLE:
        case VOID:
        case BOOL:
            type.name += lexem();
            isVoid |= (lookup(0) == VOID);
            break;
        case INTEGER_LITERAL:
        case CHARACTER_LITERAL:
        case STRING_LITERAL:
        case BOOLEAN_LITERAL:
        case FLOATING_LITERAL:
            if( templateType )
            {
                //To avoid a dead-lock with the types like XXX<X, 32>
                type.name += lexem();
                type.isBaseType = true;
                type.isContainer = false;
                type.isScoped = false;
                type.isVolatile = false;
                type.m_id = Type::UNKNOWNID;
                return type;
            }
        default:
            prev();
            ;
        }
        if (test(LANGLE)) {
            if(type.name.isEmpty())
                return type;
            type.name += "<";
            do {
                Type tmpType = parseType(true);
                type.templateTypes.push_back(tmpType);
                type.name += " " + type.templateTypes.last().name;
                if( lookup(0) == COMMA  )
                {
                    type.name += ",";
                }
            } while(lookup(0) == COMMA);

            if (test(RANGLE)){
                type.name += " >";
                type.isBaseType = isBaseSerializableAttribute(type.name);
                type.isContainer = isContainer(type.name);
                type.m_id = getTypeId(type.name);
                if( test(STAR) )
                {
                    type.referenceType = Type::Pointer;
                    type.name += " *";
                }
                if( test(AND) )
                {
                    type.referenceType = Type::Reference;
                    type.name += " &";
                }
                return type;
            }
        }
        if( templateType && (test(STAR) || test(COMMA)) )
        {
            if( lookup(0) == STAR)
            {
                type.referenceType = Type::Pointer;
                type.name += " *";
                test(COMMA);
            }
            type.isBaseType = isBaseSerializableAttribute(type.name);
            type.isContainer = isContainer(type.name);
            type.m_id = getTypeId(type.name);
            return type;
        }
        if (test(SCOPE)) {
            type.name += lexem();
            type.isScoped = true;
        } else {
            break;
        }
    }
    while (test(CONST) || test(VOLATILE) || test(SIGNED) || test(UNSIGNED)
           || test(STAR) || test(AND)) {
        type.name += ' ';
        type.name += lexem();
        if (lookup(0) == AND)
            type.referenceType = Type::Reference;
        else if (lookup(0) == STAR)
            type.referenceType = Type::Pointer;
    }
    // transform stupid things like 'const void' or 'void const' into 'void'
    if (isVoid && type.referenceType == Type::NoReference) {
        type.name = "void";
    }
    type.isBaseType = isBaseSerializableAttribute(type.name);
    type.isContainer = isContainer(type.name);
    type.m_id = getTypeId(type.name);
    return type;
}

Type::TypeNameId Moc::getTypeId(QByteArray name)
{
    for( int i = 0; i < Type::BaseSerializableTypeNames.size(); i++)
    {
        QByteArray n = Type::BaseSerializableTypeNames.at(i);
        QByteArray shortType = name.split('<').first();
        if( shortType == n )
            return (Type::TypeNameId)i;
    }
    return Type::UNKNOWNID;
}

bool Moc::parseEnum(EnumDef *def)
{
    bool isTypdefEnum = false; // typedef enum { ... } Foo;

    if (test(IDENTIFIER)) {
        def->name = lexem();
    } else {
        if (lookup(-1) != TYPEDEF)
            return false; // anonymous enum
        isTypdefEnum = true;
    }
    if (!test(LBRACE))
        return false;
    do {
        if (lookup() == RBRACE) // accept trailing comma
            break;
        next(IDENTIFIER);
        def->values += lexem();
    } while (test(EQ) ? until(COMMA) : test(COMMA));
    next(RBRACE);
    if (isTypdefEnum) {
        if (!test(IDENTIFIER))
            return false;
        def->name = lexem();
    }
    return true;
}

void Moc::parseFunctionArguments(FunctionDef *def)
{
    Q_UNUSED(def);
    while (hasNext()) {
        ArgumentDef  arg;
        arg.type = parseType();
        if (arg.type.name == "void")
            break;
        if (test(IDENTIFIER))
            arg.name = lexem();
        while (test(LBRACK)) {
            arg.rightType += lexemUntil(RBRACK);
        }
        if (test(CONST) || test(VOLATILE)) {
            arg.rightType += ' ';
            arg.rightType += lexem();
        }
        arg.normalizedType = normalizeType(arg.type.name + ' ' + arg.rightType);
        arg.typeNameForCast = normalizeType(noRef(arg.type.name) + "(*)" + arg.rightType);
        if (test(EQ))
            arg.isDefault = true;
        def->arguments += arg;
        if (!until(COMMA))
            break;
    }
}

bool Moc::testFunctionAttribute(FunctionDef *def)
{
    if (index < symbols.size() && testFunctionAttribute(symbols.at(index).token, def)) {
        ++index;
        return true;
    }
    return false;
}

bool Moc::testFunctionAttribute(Token tok, FunctionDef *def)
{
    switch (tok) {
        case Q_MOC_COMPAT_TOKEN:
        case Q_QT3_SUPPORT_TOKEN:
            def->isCompat = true;
            return true;
        case Q_INVOKABLE_TOKEN:
            def->isInvokable = true;
            return true;
        case Q_SIGNAL_TOKEN:
            def->isSignal = true;
            return true;
        case Q_SLOT_TOKEN:
            def->isSlot = true;
            return true;
        case Q_SCRIPTABLE_TOKEN:
            def->isInvokable = def->isScriptable = true;
            return true;
        default: break;
    }
    return false;
}

// returns false if the function should be ignored
bool Moc::parseFunction(FunctionDef *def, bool inMacro)
{
    def->isVirtual = false;
    while (test(INLINE) || test(STATIC) || test(VIRTUAL)
           || testFunctionAttribute(def)) {
        if (lookup() == EXPLICIT)
            def->isExplicit = true;
        if (lookup() == INLINE)
            def->isInline = true;
        if (lookup() == STATIC)
            def->isStatic = true;
        if (lookup() == VIRTUAL)
            def->isVirtual = true;
    }
    bool templateFunction = (lookup() == TEMPLATE);
    def->type = parseType();
    if (def->type.name.isEmpty()) {
        if (templateFunction)
            error("Template function as signal or slot");
        else
            error();
    }
    bool scopedFunctionName = false;
    if (test(LPAREN)) {
        def->name = def->type.name;
        scopedFunctionName = def->type.isScoped;
        def->type = Type("int");
    } else {
        Type tempType = parseType();;
        while (!tempType.name.isEmpty() && lookup() != LPAREN) {
            if (testFunctionAttribute(def->type.firstToken, def))
                ; // fine
            else if (def->type.firstToken == Q_SIGNALS_TOKEN)
                error();
            else if (def->type.firstToken == Q_SLOTS_TOKEN)
                error();
            else {
                if (!def->tag.isEmpty())
                    def->tag += ' ';
                def->tag += def->type.name;
            }
            def->type = tempType;
            tempType = parseType();
        }
        next(LPAREN, "Not a signal or slot declaration");
        def->name = tempType.name;
        scopedFunctionName = tempType.isScoped;
    }

    // we don't support references as return types, it's too dangerous
    if (def->type.referenceType == Type::Reference)
        def->type = Type("void");

    def->normalizedType = normalizeType(def->type.name);

    if (!test(RPAREN)) {
        parseFunctionArguments(def);
        next(RPAREN);
    }

    // support optional macros with compiler specific options
    while (test(IDENTIFIER))
        ;

    def->isConst = test(CONST);

    while (test(IDENTIFIER))
        ;

    if (inMacro) {
        next(RPAREN);
        prev();
    } else {
        if (test(THROW)) {
            next(LPAREN);
            until(RPAREN);
        }
        if (test(SEMIC))
            ;
        else if ((def->inlineCode = test(LBRACE)))
            until(RBRACE);
        else if ((def->isAbstract = test(EQ)))
            until(SEMIC);
        else
            error();
    }

    if (scopedFunctionName) {
        QByteArray msg("Function declaration ");
        msg += def->name;
        msg += " contains extra qualification. Ignoring as signal or slot.";
        warning(msg.constData());
        return false;
    }
    return true;
}

bool Moc::parseMaybeAttribute(AttributeDef *def)
{
    while (test(INLINE) || test(VIRTUAL) ) {
            return false;
    }
    def->isStatic = false;
    if( test(STATIC) )
            def->isStatic = true;
    if( test(CONST) )
        def->isConst     = true;
    def->type = parseType();
    if (def->type.name.isEmpty()) {
            return false;
    }

    def->normalizedType = normalizeType(def->type.name);
    if(def->type.name.startsWith("::"))
        return false;
//    if(def->type.name.contains("::"))
//        error("Scoped types are not supported, use the \"using namespace\" keyword. ");
//    bool doubleColon = true;
//    while(test(COLON) && doubleColon)
//    {
//        doubleColon = false;
//        next();
//        if(test(COLON))
//        {
//            doubleColon = true;
//            warning("Scoped types are not supported, use the \"using namespace\" keyword. ");
//            return false;
//            Type tmp = parseType();
//            if(tmp.name.isEmpty())
//                return false;
//            def->type.name += "::" + tmp.name;
//        }
//    }
    Type t = parseType();
    if(t.name.isEmpty())
        return false;
    if ( test(SEMIC) || test(COMMA))
        def->name = t.name;
    else
    {
        return false;
    }
    //Verifying type
    def->isBaseType = isBaseSerializableAttribute(def->type);

    def->isContainer = def->type.isContainer;
    if(def->normalizedType == "*")
        return false;
    if(def->normalizedType == "&")
        return false;

    return true;
//    def->type = parseType();
//    if (def->type.name.isEmpty())
//        return false;
//    Type tmpType = parseType();
//    if (tmpType.name.isEmpty())
//        return false;

//    if (test(SEMIC)||test(COMMA)) {
//        def->name = tmpType.name;
//        def->normalizedType = normalizeType(def->type.name);
//        return true;
//    }
//    return false;
}

// like parseFunction, but never aborts with an error
bool Moc::parseMaybeFunction(const ClassDef *cdef, FunctionDef *def)
{
    def->isVirtual = false;
    while (test(EXPLICIT) || test(INLINE) || test(STATIC) || test(VIRTUAL)
           || testFunctionAttribute(def)) {
        if (lookup() == EXPLICIT)
            def->isExplicit = true;
        if (lookup() == INLINE)
            def->isInline = true;
        if (lookup() == STATIC)
            def->isStatic = true;
        if (lookup() == VIRTUAL)
            def->isVirtual = true;
    }
    bool tilde = test(TILDE);
    def->type = parseType();
    if (def->type.name.isEmpty())
        return false;
    bool scopedFunctionName = false;
    if (test(LPAREN)) {
        def->name = def->type.name;
        scopedFunctionName = def->type.isScoped;
        if (def->name == cdef->classname) {
            def->isDestructor = tilde;
            def->isConstructor = !tilde;
            def->type = Type();
        } else {
            def->type = Type("int");
        }
    } else {
        Type tempType = parseType();;
        while (!tempType.name.isEmpty() && lookup() != LPAREN) {
            if (testFunctionAttribute(def->type.firstToken, def))
                ; // fine
            else if (def->type.name == "Q_SIGNAL")
                def->isSignal = true;
            else if (def->type.name == "Q_SLOT")
                def->isSlot = true;
            else {
                if (!def->tag.isEmpty())
                    def->tag += ' ';
                def->tag += def->type.name;
            }
            def->type = tempType;
            tempType = parseType();
        }
        if (!test(LPAREN))
            return false;
        def->name = tempType.name;
        scopedFunctionName = tempType.isScoped;
    }

    // we don't support references as return types, it's too dangerous
    if (def->type.referenceType == Type::Reference)
        def->type = Type("void");

    def->normalizedType = normalizeType(def->type.name);

    if (!test(RPAREN)) {
        parseFunctionArguments(def);
        if (!test(RPAREN))
            return false;
    }
    def->isConst = test(CONST);
    def->isAbstract = test(EQ);
    if (scopedFunctionName
        && (def->isSignal || def->isSlot || def->isInvokable)) {
        QByteArray msg("parsemaybe: Function declaration ");
        msg += def->name;
        msg += " contains extra qualification. Ignoring as signal or slot.";
        warning(msg.constData());
        return false;
    }
    return true;
}


void Moc::parse()
{
    QList<NamespaceDef> namespaceList;
    bool templateClass = false;
    while (hasNext()) {
        Token t = next();
        switch (t) {
            case NAMESPACE: {
                int rewind = index;
                if (test(IDENTIFIER)) {
                    if (test(EQ)) {
                        // namespace Foo = Bar::Baz;
                        until(SEMIC);
                    } else if (!test(SEMIC)) {
                        NamespaceDef def;
                        def.name = lexem();
                        next(LBRACE);
                        def.begin = index - 1;
                        until(RBRACE);
                        def.end = index;
                        index = def.begin + 1;
                        namespaceList += def;
                        index = rewind;
                    }
                }
                break;
            }
            case SEMIC:
            case RBRACE:
                templateClass = false;
                break;
            case TEMPLATE:
                templateClass = true;
                break;
            case MOC_INCLUDE_BEGIN:
                currentFilenames.push(symbol().unquotedLexem());
                break;
            case MOC_INCLUDE_END:
                currentFilenames.pop();
                break;
            case Q_DECLARE_INTERFACE_TOKEN:
                parseDeclareInterface();
                break;
            case Q_DECLARE_METATYPE_TOKEN:
                parseDeclareMetatype();
                break;
            case USING:
                if (test(NAMESPACE)) {
                    while (test(SCOPE) || test(IDENTIFIER))
                        ;
                    next(SEMIC);
                }
                break;
            case CLASS:
            case STRUCT: {
                if (currentFilenames.size() <= 1)
                    break;

                ClassDef def;
                if (!parseClassHead(&def))
                    continue;

                while (inClass(&def) && hasNext()) {
                    if (next() == Q_OBJECT_TOKEN) {
                        def.hasQObject = true;
                        break;
                    }
                }

//                if (!def.hasQObject)
//                    continue;

                for (int i = namespaceList.size() - 1; i >= 0; --i)
                    if (inNamespace(&namespaceList.at(i)))
                        def.qualified.prepend(namespaceList.at(i).name + "::");

                knownQObjectClasses.insert(def.classname);
                knownQObjectClasses.insert(def.qualified);

                continue; }
            default: break;
        }
        if ((t != CLASS && t != STRUCT)|| currentFilenames.size() > 1)
            continue;
        ClassDef def;
        if (parseClassHead(&def)) {
            FunctionDef::Access fAccess = FunctionDef::Private;
            AttributeDef::Access aAccess = AttributeDef::Private;
            for (int i = namespaceList.size() - 1; i >= 0; --i)
                if (inNamespace(&namespaceList.at(i)))
                    def.qualified.prepend(namespaceList.at(i).name + "::");
            while (inClass(&def) && hasNext()) {
                switch ((t = next())) {
                case PRIVATE:
                    fAccess = FunctionDef::Private;
                    aAccess = AttributeDef::Private;
                    if (test(Q_SIGNALS_TOKEN))
                        error("Signals cannot have access specifier");
                    break;
                case PROTECTED:
                    fAccess = FunctionDef::Protected;
                    aAccess = AttributeDef::Protected;
                    if (test(Q_SIGNALS_TOKEN))
                        error("Signals cannot have access specifier");
                    break;
                case PUBLIC:
                    fAccess = FunctionDef::Public;
                    aAccess = AttributeDef::Public;
                    if (test(Q_SIGNALS_TOKEN))
                        error("Signals cannot have access specifier");
                    break;
                case CLASS: {
                    ClassDef nestedDef;
                    if (parseClassHead(&nestedDef)) {
                        while (inClass(&nestedDef) && inClass(&def)) {
                            t = next();
                            if (t >= Q_META_TOKEN_BEGIN && t < Q_META_TOKEN_END)
                                error("Meta object features not supported for nested classes");
                        }
                    }
                }
                    break;
                case Q_SIGNALS_TOKEN:
                    parseSignals(&def);
                    break;
                case Q_SLOTS_TOKEN:
                    switch (lookup(-1)) {
                    case PUBLIC:
                    case PROTECTED:
                    case PRIVATE:
                        parseSlots(&def, fAccess);
                        break;
                    default:
                        error("Missing access specifier for slots");
                    }
                    break;
                case SERIALIZABLE:
                    switch (lookup(-1)) {
                    case PUBLIC:
                    case PROTECTED:
                    case PRIVATE:
                        parseSerializable(&def, aAccess);
                        def.hasSerializableAttributes = true;
                        if(!def.hasQSerializable)
                            error( "Class has \"serializable\" section but lacks of Q_SERIALIZABLE macro. ");
                        break;
                    default:
                        error("Missing access specifier for serializable attributes");
                    }
                    break;
                case Q_OBJECT_TOKEN:
                    def.hasQObject = true;
                    if (templateClass)
                        error("Template classes not supported by Q_OBJECT");
                    if (def.classname != "Qt" && def.classname != "QObject" && def.superclassList.isEmpty())
                        error("Class contains Q_OBJECT macro but does not inherit from QObject");
                    break;
                case Q_SERIALIZABLE_TOKEN:
                    def.hasQSerializable = true;
                    if (templateClass)
                        error("Template classes not supported by Q_SERIALIZABLE");
                    //search if a superclass is QSerializable
//                    QPair<QByteArray, FunctionDef::Access> mustFind = QPair<QByteArray, FunctionDef::Access>("QSerializable", FunctionDef::Public);
                    if ( !def.superclassList.contains(QPair<QByteArray, FunctionDef::Access>("QSerializable", FunctionDef::Public)))
                        error("Class contains Q_SERIALIZABLE macro but does not inherit from QSerializable");
                    break;
                case Q_GADGET_TOKEN:
                    def.hasQGadget = true;
                    if (templateClass)
                        error("Template classes not supported by Q_GADGET");
                    break;
                case Q_PROPERTY_TOKEN:
                    parseProperty(&def);
                    break;
                case Q_ENUMS_TOKEN:
                    parseEnumOrFlag(&def, false);
                    break;
                case Q_FLAGS_TOKEN:
                    parseEnumOrFlag(&def, true);
                    break;
                case Q_DECLARE_FLAGS_TOKEN:
                    parseFlag(&def);
                    break;
                case Q_CLASSINFO_TOKEN:
                    parseClassInfo(&def);
                    break;
                case Q_INTERFACES_TOKEN:
                    parseInterfaces(&def);
                    break;
                case Q_PRIVATE_SLOT_TOKEN:
                    parseSlotInPrivate(&def, fAccess);
                    break;
                case ENUM: {
                    EnumDef enumDef;
                    if (parseEnum(&enumDef))
                        def.enumList += enumDef;
                }
                    break;
                default:
                    {
                        FunctionDef funcDef;
                        funcDef.access = fAccess;
                        AttributeDef attrDef;
                        attrDef.access = (AttributeDef::Access)fAccess;
                        int rewind = index;
                        if (parseMaybeFunction(&def, &funcDef)) {
                            if(funcDef.isAbstract)
                                def.isAbstract = true;
                            if (funcDef.isConstructor) {
                                if ((fAccess == FunctionDef::Public) && funcDef.isInvokable) {
                                    def.constructorList += funcDef;
                                    while (funcDef.arguments.size() > 0 && funcDef.arguments.last().isDefault) {
                                        funcDef.wasCloned = true;
                                        funcDef.arguments.removeLast();
                                        def.constructorList += funcDef;
                                    }
                                }
                                if( funcDef.arguments.isEmpty() )
                                    def.hasDefaultConstructor = true;
                            } else if (funcDef.isDestructor) {
                                // don't care about destructors
                            } else {
                                switch(fAccess)
                                {
                                    case FunctionDef::Public:
                                        def.publicList += funcDef;
                                        break;
                                    case FunctionDef::Protected:
                                        def.protectedList += funcDef;
                                        break;
                                    case FunctionDef::Private:
                                        def.privateList += funcDef;
                                        break;
                                }
                                if (funcDef.isSlot) {
                                    def.slotList += funcDef;
                                    while (funcDef.arguments.size() > 0 && funcDef.arguments.last().isDefault) {
                                        funcDef.wasCloned = true;
                                        funcDef.arguments.removeLast();
                                        def.slotList += funcDef;
                                    }
                                } else if (funcDef.isSignal) {
                                    def.signalList += funcDef;
                                    while (funcDef.arguments.size() > 0 && funcDef.arguments.last().isDefault) {
                                        funcDef.wasCloned = true;
                                        funcDef.arguments.removeLast();
                                        def.signalList += funcDef;
                                    }
                                } else if (funcDef.isInvokable) {
                                    def.methodList += funcDef;
                                    while (funcDef.arguments.size() > 0 && funcDef.arguments.last().isDefault) {
                                        funcDef.wasCloned = true;
                                        funcDef.arguments.removeLast();
                                        def.methodList += funcDef;
                                    }
                                }
                            }
                        } else {
                            index = rewind;
                            if(parseMaybeAttribute(&attrDef))
                            {

                                index = rewind;
                                QList<AttributeDef>* list = NULL;
                                switch(fAccess)
                                {
                                    case FunctionDef::Public:
                                        list = &(def.publicAttrList);
                                        break;
                                    case FunctionDef::Protected:
                                        list = &(def.protectedAttrList);
                                        break;
                                    case FunctionDef::Private:
                                        list = &(def.privateAttrList);
                                        break;
                                }
                                if(list)
                                {
                                    bool doAdd = true;
                                    foreach(AttributeDef a, *list)
                                    {
                                        if(a.name == attrDef.name)
                                            doAdd = false;
                                    }
                                    if(doAdd)
                                        list->push_back(attrDef);
                                }
                            } else
                                index = rewind;
                        }
                    }
                }
            }

            next(RBRACE);

//            if (!def.hasQObject &&
//                !def.hasQGadget &&
//                !def.hasQSerializable &&
//                def.serializableList.isEmpty() &&
//                def.signalList.isEmpty() &&
//                def.slotList.isEmpty() &&
//                def.propertyList.isEmpty() &&
//                def.enumDeclarations.isEmpty())
//                continue; // no meta object code required


//            if (!def.hasQObject && !def.hasQGadget && !def.hasQSerializable)
//                error("Class declarations lacks Q_OBJECT or Q_SERIALIZABLE macro.");
            if( def.hasQSerializable && !def.hasDefaultConstructor )
            {
                QByteArray msg = "A QSerializable object must have a default constructor (even if it is empty). ";
                error(msg.constData());
            }
            checkSuperClasses(&def);
            
            classList += def;
            knownQObjectClasses.insert(def.classname);
            knownQObjectClasses.insert(def.qualified);
        }
    }
}

void Moc::generate(FILE *out)
{
    fprintf(out, "digraph {\n    //splines=ortho;\n");
    for (int i = 0; i < classList.size(); ++i) {
        ClassDef* cld = &classList[i];
        if(!cld->isGenerated)
        {
            generateClassDot(cld, &classList, out);
        }
    }
    fprintf(out, "}\n");
}

QString Moc::stringToHtml(QString in)
{
    QString res = in;
    res.replace("&", "&amp;");
    res.replace("<", "&lt;");
    res.replace(">", "&gt;");
    return res;
}

QString Moc::toString(const Type* t, bool toHtml)
{
    QString res;
    res += t->name;
//    if(t->referenceType == Type::Pointer)
//        res += "*";
//    else if(t->referenceType == Type::Reference)
//        res += "&";
    if(toHtml)
    {
        res = stringToHtml(res);
    }
    return res;
}

Moc::Moc()
    : noInclude(false), generatedCode(false)
{

}

QString Moc::toString(const AttributeDef* def, bool simple)
{
    QString res;
    if(simple)
    {
        if(def->isStatic)
            res += "static ";
        if(def->isConst)
            res += "const ";
        res += toString(&def->type, !simple);
    }
    else
        switch(def->access)
        {
        case AttributeDef::Public:
            res += "+";
            break;
        case AttributeDef::Protected:
            res += "#";
            break;
        case AttributeDef::Private:
            res += "-";
            break;
        }
    res += " " + def->name;
    if(!simple)
    {
        res += " : " + toString(&def->type, !simple);
        if(def->isStatic)
            res += stringToHtml(" << static >>");
        res += "<br/>";
    }

    return res;
}

QString Moc::toString(const FunctionDef* def, bool simple)
{
    QString res;
    if(simple)
    {
        if(def->isExplicit)
            res += "explicit ";
        if(def->isInline)
            res += "inline ";
        if(def->isStatic)
            res += "static ";
        res += toString(&def->type, !simple);
    }
    else
    {
        switch(def->access)
        {
        case FunctionDef::Public:
            res += "+";
            break;
        case FunctionDef::Protected:
            res += "#";
            break;
        case FunctionDef::Private:
            res += "-";
            break;
        }
        if(def->isAbstract)
            res += "<I>";
    }
    res += " " + def->name + "(";
    for(int i=0;i<def->arguments.size();i++)
    {
        ArgumentDef a = def->arguments.at(i);
        res += (i==0?" ":", ") + toString(&a.type, !simple);
        res += " " + a.name;
    }
    res += ")";
    if(def->isConst)
        res += " const";

    if(def->isAbstract)
        res += " = 0";
    else
        res += " ";
    if(!simple)
    {
        res += " : ";
    }

    if(!simple)
    {
        res += toString(&def->type, !simple);
        if(def->isAbstract)
                res += "</I>";
    }
    if(!simple)
        res += "<br/>";
    return res;
}

void Moc::alreadyPrintedClass(QByteArray name, FILE* out, QList<ClassDef>* classList)
{
    QByteArray mName = name.trimmed();
    mName = mName.trimmed();
    if(mName.endsWith("*") || mName.endsWith("&"))
        mName.resize(mName.size()-1);
    mName = mName.trimmed();
    ClassDef* cld = findClassDef(classList, mName);
    if(cld)
        generateClassDot(cld, classList, out);
    else
        printClassNode(mName, out, classList);
}

void Moc::printClassNode(QByteArray name, FILE* out, QList<ClassDef>* classList, ClassDef* cdef)
{
    QString label = "<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">";
    QString cellOpen = "<tr><td>";
    QString cellClose = "</td></tr>";
    label += cellOpen;

    if(cdef)
    {
        if(cdef->isAbstract)
            label += stringToHtml("<< Abstract >>") + "<br/><i>";
        label += name;
        if(cdef->isAbstract)
            label += "</i>";
        label += cellClose + cellOpen;

        QList< QList<AttributeDef>* > theList;
        theList.push_back(&cdef->publicAttrList);
        theList.push_back(&cdef->protectedAttrList);
        theList.push_back(&cdef->privateAttrList);

//        warning(cdef->classname.data());
        for(int i=0;i<theList.size();i++)
        {
            QList<AttributeDef>* list = theList.at(i);
            for(int i=0;i<list->size();i++)
            {
                const AttributeDef* attr = &(list->at(i));

                if(!attr->name.isEmpty() && !attr->type.name.isEmpty())
                {
//                    warning(attr->name.data());
//                    warning(attr->type.name.data());
                    if(attr->type.isContainer)
                    {//container...
                        if(attr->type.templateTypes.size() == 1 )
                        {
                            Type t = attr->type.templateTypes.first();
                            if(!t.name.isEmpty() && !t.isBaseType)
                            {
                                alreadyPrintedClass(t.name, out, classList);
                                QByteArray head = "normal";
                                if(t.referenceType == Type::Pointer)
                                    head = "diamond";
                                QString n = attr->normalizedType;
                                QString l = "<<table border=\"0\" cellborder=\"0\" cellspacing=\"0\">" + cellOpen + "&lt;&lt;" + stringToHtml(n.split("<", QString::SkipEmptyParts).first()) + "&gt;&gt;";
                                if(attr->isStatic)
                                    l+= " : static";
                                l += cellClose + "</table>>";
                                fprintf(out, "    %s -> %s [style=solid, arrowhead=%s, headlabel=\"%s *\", label=%s, arrowsize="arrowSize"];\n",
                                        toIdentifier(name).data(),
                                        toIdentifier(t.name).data(),
                                        head.data(),
                                        stringToHtml(attr->name).toStdString().c_str(),
                                        l.toStdString().c_str());
                            } else if(t.isBaseType)
                            {
                                label += toString(attr);
                            }
                        } else
                            warning("Multi-containers not yet implemented");
                    } else if( attr->type.templateTypes.size()>=1)
                    {//template association
                        if(attr->type.templateTypes.size() == 1 )
                        {
                            Type t = attr->type.templateTypes.first();
                            if(!t.name.isEmpty() && !t.isBaseType)
                            {
                                alreadyPrintedClass(t.name, out, classList);
                                QByteArray head = "normal";
                                if(t.referenceType == Type::Pointer)
                                    head = "diamond";
                                QString n = attr->normalizedType;
                                QString l = "<<table border=\"0\" cellborder=\"0\" cellspacing=\"0\">" + cellOpen + "&lt;&lt;" + stringToHtml(n.split("<", QString::SkipEmptyParts).first()) + "&gt;&gt;" + cellClose + "</table>>";
                                fprintf(out, "    %s -> %s [style=solid, arrowhead=%s, headlabel=\"%s 1\", label=%s, arrowsize="arrowSize"];\n",
                                        toIdentifier(name).data(),
                                        toIdentifier(t.name).data(),
                                        head.data(),
                                        stringToHtml(attr->name).toStdString().c_str(),
                                        l.toStdString().c_str());
                            } else if(t.isBaseType)
                            {
                                label += toString(attr);
                            }
                        } else
                            warning("Multi-containers not yet implemented");

                    } else if(!attr->isBaseType)
                    {//simple association
                        QByteArray head = "normal";
                        if(attr->type.referenceType == Type::Pointer)
                            head = "diamond";
                        alreadyPrintedClass(attr->type.name, out, classList);
                        fprintf(out, "    %s -> %s [style=solid, arrowhead=%s, headlabel=\"%s 1\", arrowsize="arrowSize"];\n",
                                toIdentifier(name).data(),
                                toIdentifier(attr->normalizedType).data(),
                                head.data(),
                                stringToHtml(attr->name).toStdString().c_str());
                    } else if(attr->isBaseType)
                    {
                        label += toString(attr);
                    }
                }
            }
        }

        label += cellClose + cellOpen;
        for(int i=0;i<cdef->publicList.size();i++)
            label += toString(&cdef->publicList.at(i));
        for(int i=0;i<cdef->protectedList.size();i++)
            label += toString(&cdef->protectedList.at(i));
        for(int i=0;i<cdef->privateList.size();i++)
            label += toString(&cdef->privateList.at(i));
        label += cellClose;
        label += "</table>>";
        fprintf(out, "    %s [shape=plaintext, label=%s];\n",
                toIdentifier(name).data(),
                label.toStdString().c_str());
    } else if(!m_alreadyPrinted.contains(label))
    {
        label += name;
        label += cellClose + cellOpen;
        label += cellClose + cellOpen;
        label += cellClose;
        label += "</table>>";
        m_alreadyPrinted.push_back(label);
        fprintf(out, "    %s [shape=plaintext, label=%s];\n",
                toIdentifier(name).data(),
                label.toStdString().c_str());
    }
}

QByteArray Moc::toIdentifier(const QByteArray name) const
{
    //Replaces all the unallowed characters
    QByteArray newName = name;
    newName.replace('(', "");
    newName.replace(')', "");
    newName.replace("->", "");
    newName.replace('.', "");
    newName.replace(':', "_");
    newName.replace('<', "");
    newName.replace('>', "");
    newName.replace(' ', "");
    newName.replace('*', "");
    return newName;
}

typedef QPair<QByteArray, FunctionDef::Access> tmpType;
typedef QList<FunctionDef> FuncList;
typedef QList<AttributeDef> AttrList;

QString accessToString(int a)
{
    QString res;
    switch(a)
    {
    case 2:
        res = "public ";
        break;
    case 1:
        res = "protected ";
        break;
    case 0:
        res = "private ";
        break;
    default:
        res = "";
        break;
    }
    return res;
}

void Moc::infoClass(ClassDef* cdef)
{
    QString res;
    res += cdef->classname + " ";
    if(!cdef->superclassList.isEmpty())
    {
        foreach(tmpType pair, cdef->superclassList)
        {
            res += ": ";
            res += accessToString(pair.second) + " ";
            res += pair.first;
        }
    }
    res += "{\n";
    QString indent = "    ";
    QList<FuncList*> Flist;
    Flist.push_back(&cdef->publicList);
    Flist.push_back(&cdef->protectedList);
    Flist.push_back(&cdef->privateList);
    foreach(FuncList* list, Flist)
    {
        if(!list->isEmpty())
        {
            res += indent + accessToString(list->first().access) + ":\n";
            foreach(FunctionDef f, *list)
                res += indent + indent + toString(&f, true) + ";\n";
        }
    }
    QList<AttrList*> Alist;
    Alist.push_back(&cdef->publicAttrList);
    Alist.push_back(&cdef->protectedAttrList);
    Alist.push_back(&cdef->privateAttrList);
    foreach(AttrList* list, Alist)
    {
        if(!list->isEmpty())
        {
            res += indent + accessToString(list->first().access) + ":\n";
            foreach(AttributeDef a, *list)
                res += indent + indent + toString(&a, true) + ";\n";
        }
    }
    res += "\n}\n";
    infoNoOut(res.toStdString().c_str());
}

void Moc::generateClassDot(ClassDef *classDef, QList<ClassDef>* classList, FILE *out)
{
    if(!classDef->isGenerated)
    {
        classDef->isGenerated = true;
        infoClass(classDef);
        printClassNode(classDef->classname, out, classList, classDef);
        for(int i=0;i<classDef->superclassList.size();i++)
        {
            QByteArray supName =  classDef->superclassList.at(i).first;
            alreadyPrintedClass(supName, out, classList);
//            QByteArray supName = classDef->superclassList.at(i).first;
//            ClassDef* cld = findClassDef(classList, supName);
//            if(cld)
//                generateClassDot(cld, classList, out);
//            else
//                printClassNode(supName, out, classList);
            fprintf(out, "    %s -> %s [style=solid, dir=back, arrowtail=empty, arrowsize="arrowSize"];\n",
                    toIdentifier(supName).data(),
                    toIdentifier(classDef->classname).data());
        }
    }
}

ClassDef* Moc::findClassDef(QList<ClassDef>* classList, QByteArray name)
{
    ClassDef* cld = NULL;
    for(int i=0;i<classList->size();i++)
    {
        if(QString(classList->at(i).classname) == QString(name))
            cld = const_cast<ClassDef*>(&classList->at(i));
    }
    return cld;
}

void Moc::parseSlots(ClassDef *def, FunctionDef::Access access)
{
    next(COLON);
    while (inClass(def) && hasNext()) {
        switch (next()) {
        case PUBLIC:
        case PROTECTED:
        case PRIVATE:
        case Q_SIGNALS_TOKEN:
        case Q_SLOTS_TOKEN:
            prev();
            return;
        case SEMIC:
            continue;
        case FRIEND:
            until(SEMIC);
            continue;
        case USING:
            error("'using' directive not supported in 'slots' section");
        default:
            prev();
        }

        FunctionDef funcDef;
        funcDef.access = access;
        if (!parseFunction(&funcDef))
            continue;
        def->slotList += funcDef;
        while (funcDef.arguments.size() > 0 && funcDef.arguments.last().isDefault) {
            funcDef.wasCloned = true;
            funcDef.arguments.removeLast();
            def->slotList += funcDef;
        }
    }
}

void Moc::parseSignals(ClassDef *def)
{
    next(COLON);
    while (inClass(def) && hasNext()) {
        switch (next()) {
        case PUBLIC:
        case PROTECTED:
        case PRIVATE:
        case Q_SIGNALS_TOKEN:
        case Q_SLOTS_TOKEN:
            prev();
            return;
        case SEMIC:
            continue;
        case FRIEND:
            until(SEMIC);
            continue;
        case USING:
            error("'using' directive not supported in 'signals' section");
        default:
            prev();
        }
        FunctionDef funcDef;
        funcDef.access = FunctionDef::Protected;
        parseFunction(&funcDef);
        if (funcDef.isVirtual)
            error("Signals cannot be declared virtual");
        if (funcDef.inlineCode)
            error("Not a signal declaration");
        def->signalList += funcDef;
        while (funcDef.arguments.size() > 0 && funcDef.arguments.last().isDefault) {
            funcDef.wasCloned = true;
            funcDef.arguments.removeLast();
            def->signalList += funcDef;
        }
    }
}


void Moc::parseProperty(ClassDef *def)
{
    next(LPAREN);
    PropertyDef propDef;
    QByteArray type = parseType().name;
    if (type.isEmpty())
        error();
    propDef.designable = propDef.scriptable = propDef.stored = "true";
    propDef.user = "false";
    /*
      The Q_PROPERTY construct cannot contain any commas, since
      commas separate macro arguments. We therefore expect users
      to type "QMap" instead of "QMap<QString, QVariant>". For
      coherence, we also expect the same for
      QValueList<QVariant>, the other template class supported by
      QVariant.
    */
    type = normalizeType(type);
    if (type == "QMap")
        type = "QMap<QString,QVariant>";
    else if (type == "QValueList")
        type = "QValueList<QVariant>";
    else if (type == "LongLong")
        type = "qlonglong";
    else if (type == "ULongLong")
        type = "qulonglong";
    propDef.type = type;

    next();
    propDef.name = lexem();
    while (test(IDENTIFIER)) {
        QByteArray l = lexem();
        QByteArray v, v2;
        if (test(LPAREN)) {
            v = lexemUntil(RPAREN);
        } else {
            while(test(IDENTIFIER));
//            next(IDENTIFIER);
            v = lexem();
            if (test(LPAREN))
                v2 = lexemUntil(RPAREN);
            else if (v != "true" && v != "false")
                v2 = "()";
        }
        switch (l[0]) {
        case 'R':
            if (l == "READ")
                propDef.read = v;
            else if (l == "RESET")
                propDef.reset = v + v2;
            else
                error(2);
            break;
        case 'S':
            if (l == "SCRIPTABLE")
                propDef.scriptable = v + v2;
            else if (l == "STORED")
                propDef.stored = v + v2;
            else
                error(2);
            break;
        case 'W': if (l != "WRITE") error(2);
            propDef.write = v;
            break;
        case 'D': if (l != "DESIGNABLE") error(2);
            propDef.designable = v + v2;
            break;
        case 'E': if (l != "EDITABLE") error(2);
            propDef.editable = v + v2;
            break;
        case 'N': if (l != "NOTIFY") error(2);
            propDef.notify = v;
            break;
        case 'U': if (l != "USER") error(2);
            propDef.user = v + v2;
            break;
        default:
//            error(2);
            break;
        }
    }
    next(RPAREN);
    if (propDef.read.isNull()) {
        QByteArray msg;
        msg += "Property declaration ";
        msg += propDef.name;
        msg += " has no READ accessor function. The property will be invalid.";
        warning(msg.constData());
    }
    if(!propDef.notify.isEmpty())
        def->notifyableProperties++;

    def->propertyList += propDef;
}

void Moc::parseEnumOrFlag(ClassDef *def, bool isFlag)
{
    next(LPAREN);
    QByteArray identifier;
    while (test(IDENTIFIER)) {
        identifier = lexem();
        while (test(SCOPE) && test(IDENTIFIER)) {
            identifier += "::";
            identifier += lexem();
        }
        def->enumDeclarations[identifier] = isFlag;
    }
    next(RPAREN);
}

void Moc::parseFlag(ClassDef *def)
{
    next(LPAREN);
    QByteArray flagName, enumName;
    while (test(IDENTIFIER)) {
        flagName = lexem();
        while (test(SCOPE) && test(IDENTIFIER)) {
            flagName += "::";
            flagName += lexem();
        }
    }
    next(COMMA);
    while (test(IDENTIFIER)) {
        enumName = lexem();
        while (test(SCOPE) && test(IDENTIFIER)) {
            enumName += "::";
            enumName += lexem();
        }
    }

    def->flagAliases.insert(enumName, flagName);
    next(RPAREN);
}

void Moc::parseClassInfo(ClassDef *def)
{
    next(LPAREN);
    ClassInfoDef infoDef;
    next(STRING_LITERAL);
    infoDef.name = symbol().unquotedLexem();
    next(COMMA);
    if (test(STRING_LITERAL)) {
        infoDef.value = symbol().unquotedLexem();
    } else {
        // support Q_CLASSINFO("help", QT_TR_NOOP("blah"))
        next(IDENTIFIER);
        next(LPAREN);
        next(STRING_LITERAL);
        infoDef.value = symbol().unquotedLexem();
        next(RPAREN);
    }
    next(RPAREN);
    def->classInfoList += infoDef;
}

void Moc::parseInterfaces(ClassDef *def)
{
    next(LPAREN);
    while (test(IDENTIFIER)) {
        QList<ClassDef::Interface> iface;
        iface += ClassDef::Interface(lexem());
        while (test(SCOPE)) {
            iface.last().className += lexem();
            next(IDENTIFIER);
            iface.last().className += lexem();
        }
        while (test(COLON)) {
            next(IDENTIFIER);
            iface += ClassDef::Interface(lexem());
            while (test(SCOPE)) {
                iface.last().className += lexem();
                next(IDENTIFIER);
                iface.last().className += lexem();
            }
        }
        // resolve from classnames to interface ids
        for (int i = 0; i < iface.count(); ++i) {
            const QByteArray iid = interface2IdMap.value(iface.at(i).className);
            if (iid.isEmpty())
                warning("Undefined interface");

            iface[i].interfaceId = iid;
        }
        def->interfaceList += iface;
    }
    next(RPAREN);
}

void Moc::parseDeclareInterface()
{
    next(LPAREN);
    QByteArray interface;
    next(IDENTIFIER);
    interface += lexem();
    while (test(SCOPE)) {
        interface += lexem();
        next(IDENTIFIER);
        interface += lexem();
    }
    next(COMMA);
    QByteArray iid;
    if (test(STRING_LITERAL)) {
        iid = lexem();
    } else {
        next(IDENTIFIER);
        iid = lexem();
    }
    interface2IdMap.insert(interface, iid);
    next(RPAREN);
}

void Moc::parseDeclareMetatype()
{
    next(LPAREN);
    QByteArray typeName = lexemUntil(RPAREN);
    typeName.remove(0, 1);
    typeName.chop(1);
    metaTypes.append(typeName);
}

void Moc::parseSlotInPrivate(ClassDef *def, FunctionDef::Access access)
{
    next(LPAREN);
    FunctionDef funcDef;
    next(IDENTIFIER);
    funcDef.inPrivateClass = lexem();
    // also allow void functions
    if (test(LPAREN)) {
        next(RPAREN);
        funcDef.inPrivateClass += "()";
    }
    next(COMMA);
    funcDef.access = access;
    parseFunction(&funcDef, true);
    def->slotList += funcDef;
    while (funcDef.arguments.size() > 0 && funcDef.arguments.last().isDefault) {
        funcDef.wasCloned = true;
        funcDef.arguments.removeLast();
        def->slotList += funcDef;
    }
}

QByteArray Moc::lexemUntil(Token target)
{
    int from = index;
    until(target);
    QByteArray s;
    while (from <= index) {
        QByteArray n = symbols.at(from++-1).lexem();
        if (s.size() && n.size()
            && is_ident_char(s.at(s.size()-1))
            && is_ident_char(n.at(0)))
            s += ' ';
        s += n;
    }
    return s;
}

bool Moc::until(Token target) {
    int braceCount = 0;
    int brackCount = 0;
    int parenCount = 0;
    int angleCount = 0;
    if (index) {
        switch(symbols.at(index-1).token) {
        case LBRACE: ++braceCount; break;
        case LBRACK: ++brackCount; break;
        case LPAREN: ++parenCount; break;
        case LANGLE: ++angleCount; break;
        default: break;
        }
    }
    while (index < symbols.size()) {
        Token t = symbols.at(index++).token;
        switch (t) {
        case LBRACE: ++braceCount; break;
        case RBRACE: --braceCount; break;
        case LBRACK: ++brackCount; break;
        case RBRACK: --brackCount; break;
        case LPAREN: ++parenCount; break;
        case RPAREN: --parenCount; break;
        case LANGLE: ++angleCount; break;
        case RANGLE: --angleCount; break;
        case GTGT: angleCount -= 2; t = RANGLE; break;
        default: break;
        }
        if (t == target
            && braceCount <= 0
            && brackCount <= 0
            && parenCount <= 0
            && (target != RANGLE || angleCount <= 0))
            return true;

        if (braceCount < 0 || brackCount < 0 || parenCount < 0
            || (target == RANGLE && angleCount < 0)) {
            --index;
            break;
        }
    }
    return false;
}

void Moc::checkSuperClasses(ClassDef *def)
{
    const QByteArray firstSuperclass = def->superclassList.value(0).first;

    if (!knownQObjectClasses.contains(firstSuperclass)) {
        // enable once we /require/ include paths
#if 0
        QByteArray msg;
        msg += "Class ";
        msg += def->className;
        msg += " contains the Q_OBJECT macro and inherits from ";
        msg += def->superclassList.value(0);
        msg += " but that is not a known QObject subclass. You may get compilation errors.";
        warning(msg.constData());
#endif
        return;
    }
    for (int i = 1; i < def->superclassList.count(); ++i) {
        const QByteArray superClass = def->superclassList.at(i).first;
        if (knownQObjectClasses.contains(superClass)) {
            QByteArray msg;
            msg += "Class ";
            msg += def->classname;
            msg += " inherits from two QObject subclasses ";
            msg += firstSuperclass;
            msg += " and ";
            msg += superClass;
            msg += ". This is not supported!";
            warning(msg.constData());
        }

        if (interface2IdMap.contains(superClass)) {
            bool registeredInterface = false;
            for (int i = 0; i < def->interfaceList.count(); ++i)
                if (def->interfaceList.at(i).first().className == superClass) {
                    registeredInterface = true;
                    break;
                }

            if (!registeredInterface) {
                QByteArray msg;
                msg += "Class ";
                msg += def->classname;
                msg += " implements the interface ";
                msg += superClass;
                msg += " but does not list it in Q_INTERFACES. qobject_cast to ";
                msg += superClass;
                msg += " will not work!";
                warning(msg.constData());
            }
        }
    }
}

/**************************************************************************************/
/*                                 Serialization stuff                                */
/**************************************************************************************/

QVector<QByteArray> Type::BaseSerializableTypeNames;

void Moc::parseSerializable(ClassDef *def, AttributeDef::Access access)
{
    next(COLON);
    while (inClass(def) && hasNext()) {
        switch (next()) {
        case PUBLIC:
        case PROTECTED:
        case PRIVATE:
        case SERIALIZABLE:
            prev();
            return;
        case SEMIC:
            continue;
        case USING:
            error("'using' directive not supported in 'serializable' section");
        default:
            prev();
        }

        AttributeDef attrDef;
        attrDef.access = access;
        if (!parseAttribute(&attrDef))
            continue;
        def->serializableList += attrDef;
    }
}

// returns false if the attribute should be ignored
bool Moc::parseAttribute(AttributeDef *def, bool /*inMacro*/)
{
    while (test(INLINE) || test(VIRTUAL) ) {
            error("Functions cannot be in serializable section (inline or virtual). ");
    }
    def->isStatic = false;
    while( test(STATIC) )
        def->isStatic = true;
    def->type = parseType();
    if (def->type.name.isEmpty()) {
            error("Empty attribute typename. ");
    }

    def->normalizedType = normalizeType(def->type.name);

    Type t = parseType();
    if ( test(SEMIC) )
        def->name = t.name;
    else 
    {
        QByteArray text = "Functions cannot be in serializable section. " + t.name;
        error(/*text.constData()*/);
    }
    if( def->isStatic ) {
        QByteArray msg = "Serializable attribute " + def->name + " is static. This could be an issue... Let's see later !";
        warning(msg);
    }
    //Verifying type
    def->isBaseType = isBaseSerializableAttribute(def->type);
    if( def->type.referenceType==Type::Pointer && !def->isBaseType ) {
        QByteArray msg = "Serializable attribute " + def->name + " is a pointer on a non-native serializable object. Make sure it is serializable too. Maybe could it be a solution to test it automatically ? ";
        warning(msg);
    }
//    def->isContainer = isContainer(def->type);
    def->isContainer = def->type.isContainer;

    if( def->type.templateTypes.size() > 1 )
        error("Complex containers are not yet implemented. ");
    return true;
}


// tells if the attribute is one of the base serializable types.
bool Moc::isBaseSerializableAttribute(Type& type)
{
     return isBaseSerializableAttribute(type.name);
}

// tells if the attribute is one of the base serializable types.
bool Moc::isBaseSerializableAttribute(QByteArray type)
{
    for( int i = 0; i < Type::BaseSerializableTypeNames.size(); i++)
    {
        QByteArray n = Type::BaseSerializableTypeNames.at(i);
        QByteArray shortType = type.split('<').first();
        if( shortType == n )
            return true;
        n += " *";
        if( type == n )
            return true;
    }
    return false;
}

// tells if the attribute is a container or not.
bool Moc::isContainer(Type& type)
{
    return isContainer(type.name);
}

bool Moc::isContainer(QByteArray type)
{
    for( int i = Type::BaseSerializableTypeNames.indexOf("QList"); i < Type::BaseSerializableTypeNames.size(); i++)
    {
        QByteArray n = Type::BaseSerializableTypeNames.at(i);
        QByteArray shortType = type.split('<').first();
        if( shortType == n )
            return true;
        if( shortType == n + " *" )
            return true;
        if(i >= Type::BaseSerializableTypeNames.indexOf("vector"))
            if( shortType == "std::" + n )
                return true;
    }
    return false;
}



