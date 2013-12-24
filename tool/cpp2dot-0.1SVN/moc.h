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

#ifndef CPP2DOT_H
#define CPP2DOT_H

#include "parser.h"
#include <QStringList>
#include <QMap>
#include <QPair>
#include <stdio.h>
#include <ctype.h>



struct QMetaObject;

struct Type
{
    enum ReferenceType { NoReference, Reference, Pointer };

    inline Type() : isVolatile(false),
                    isScoped(false),
                    firstToken(NOTOKEN),
                    isContainer(false),
                    isBaseType(false),
                    referenceType(NoReference),
                    m_id(UNKNOWNID){
        if( BaseSerializableTypeNames.isEmpty() )
        {
            BaseSerializableTypeNames.push_back("char");
            BaseSerializableTypeNames.push_back("unsigned char");
            BaseSerializableTypeNames.push_back("uchar");
            BaseSerializableTypeNames.push_back("short");
            BaseSerializableTypeNames.push_back("unsigned short");
            BaseSerializableTypeNames.push_back("ushort");
            BaseSerializableTypeNames.push_back("int");
            BaseSerializableTypeNames.push_back("unsigned int");
            BaseSerializableTypeNames.push_back("uint");
            BaseSerializableTypeNames.push_back("long");
            BaseSerializableTypeNames.push_back("unsigned long");
            BaseSerializableTypeNames.push_back("ulong");
            BaseSerializableTypeNames.push_back("float");
            BaseSerializableTypeNames.push_back("double");
            BaseSerializableTypeNames.push_back("long double");
            BaseSerializableTypeNames.push_back("QString");
            BaseSerializableTypeNames.push_back("QByteArray");
            //Qt containers
            BaseSerializableTypeNames.push_back("QList");
            BaseSerializableTypeNames.push_back("QLinkedList");
            BaseSerializableTypeNames.push_back("QVector");
            BaseSerializableTypeNames.push_back("QStack");
            BaseSerializableTypeNames.push_back("QQueue");
            BaseSerializableTypeNames.push_back("QSet");
            BaseSerializableTypeNames.push_back("QMap");
            BaseSerializableTypeNames.push_back("QMultiMap");
            BaseSerializableTypeNames.push_back("QHash");
            BaseSerializableTypeNames.push_back("QMultiHash");
            //stl containers
            BaseSerializableTypeNames.push_back("vector");
            BaseSerializableTypeNames.push_back("deque");
            BaseSerializableTypeNames.push_back("list");
            BaseSerializableTypeNames.push_back("stack");
            BaseSerializableTypeNames.push_back("queue");
            BaseSerializableTypeNames.push_back("priority_queue");
            BaseSerializableTypeNames.push_back("set");
            BaseSerializableTypeNames.push_back("multiset");
            BaseSerializableTypeNames.push_back("map");
            BaseSerializableTypeNames.push_back("multimap");
//            BaseSerializableTypeNames.push_back("bitset");
        }
    }
    enum TypeNameId {
        UNKNOWNID = -1,
        CHARID = 0,
        UCHARID,
        SHORTID,
        USHORTID,
        INTID,
        UINTID,
        LONGID,
        ULONGID,
        FLOATID,
        DOUBLEID,
        LDOUBLEID,
        QCHARACTERID,
        QSTRINGID = QCHARACTERID,
        QBYTEARRAYID,
        QCONTAINERID,
        QLISTID = QCONTAINERID,
        QVECTORID
    };
    inline explicit Type(const QByteArray &_name) : name(_name), isVolatile(false), isScoped(false), firstToken(NOTOKEN), referenceType(NoReference) {
    }
    inline void updateShortName()
    {
        shortName = name;
        if(shortName == "")
            return;
        QByteArray old;
        do {
            old = shortName;
            if( shortName.at(0) == ' ' || shortName.at(0) == '*' )
                shortName.remove(0, 1);
            int ind = shortName.size() -1;
            if( shortName.at(ind) == ' ' || shortName.at(ind) == '*' )
                shortName.remove(ind, 1);
        }while(old != shortName);
    }

    QByteArray name;
    QByteArray shortName;
    uint isVolatile : 1;
    uint isScoped : 1;
    Token firstToken;
    bool isContainer;
    bool isBaseType;
    QList<Type> templateTypes;
    ReferenceType referenceType;
    static QVector<QByteArray> BaseSerializableTypeNames;
    TypeNameId m_id;
};
#define arrowSize "2"
struct EnumDef
{
    QByteArray name;
    QList<QByteArray> values;
};

struct ArgumentDef
{
    ArgumentDef() : isDefault(false) {}
    Type type;
    QByteArray rightType, normalizedType, name;
    QByteArray typeNameForCast; // type name to be used in cast from void * in metacall
    bool isDefault;
};

struct AttributeDef
{
    AttributeDef(): access(Private), isConst(false), isBaseType(true),isContainer(false){}
    Type type;
    QByteArray normalizedType;
    QByteArray tag;
    QByteArray name;

    enum Access { Private, Protected, Public };
    Access access;
    bool isConst;
    bool isStatic;
    bool isBaseType;
    bool isContainer;
    QByteArray inPrivateClass;
};

struct FunctionDef
{
    FunctionDef(): returnTypeIsVolatile(false), access(Private), isExplicit(false), isInline(false), isStatic(false), isConst(false), isVirtual(false),
                   inlineCode(false), wasCloned(false), isCompat(false), isInvokable(false),
                   isScriptable(false), isSlot(false), isSignal(false),
                   isConstructor(false), isDestructor(false), isAbstract(false) {}
    Type type;
    QByteArray normalizedType;
    QByteArray tag;
    QByteArray name;
    bool returnTypeIsVolatile;

    QList<ArgumentDef> arguments;

    enum Access { Private, Protected, Public };
    Access access;
    bool isExplicit;
    bool isInline;
    bool isStatic;
    bool isConst;
    bool isVirtual;
    bool inlineCode;
    bool wasCloned;

    QByteArray inPrivateClass;
    bool isCompat;
    bool isInvokable;
    bool isScriptable;
    bool isSlot;
    bool isSignal;
    bool isConstructor;
    bool isDestructor;
    bool isAbstract;
};

struct PropertyDef
{
    PropertyDef():notifyId(-1), gspec(ValueSpec){}
    QByteArray name, type, read, write, reset, designable, scriptable, editable, stored, user, notify;
    int notifyId;
    enum Specification  { ValueSpec, ReferenceSpec, PointerSpec };
    Specification gspec;
    bool stdCppSet() const {
        QByteArray s("set");
        s += toupper(name[0]);
        s += name.mid(1);
        return (s == write);
    }
};


struct ClassInfoDef
{
    QByteArray name;
    QByteArray value;
};

struct ClassDef {
    ClassDef():
        isAbstract(false), hasQObject(false), hasQGadget(false), hasSerializableAttributes(false), hasQSerializable(false), hasDefaultConstructor(false), notifyableProperties(0), begin(0), end(0), isGenerated(false){}
    QByteArray classname;
    QByteArray qualified;
    QList<QPair<QByteArray, FunctionDef::Access> > superclassList;

    struct Interface
    {
        inline explicit Interface(const QByteArray &_className)
            : className(_className) {}
        QByteArray className;
        QByteArray interfaceId;
    };
    QList<QList<Interface> >interfaceList;

    bool isAbstract;

    bool hasQObject;
    bool hasQGadget;
    bool hasSerializableAttributes;
    bool hasQSerializable;
    bool hasDefaultConstructor;
    QList<FunctionDef> constructorList;
    QList<FunctionDef> signalList, slotList, methodList, publicList, protectedList, privateList;
    QList<AttributeDef> publicAttrList;
    QList<AttributeDef> protectedAttrList;
    QList<AttributeDef> privateAttrList;
    QList<AttributeDef> serializableList;
    int notifyableProperties;
    QList<PropertyDef> propertyList;
    QList<ClassInfoDef> classInfoList;
    QMap<QByteArray, bool> enumDeclarations;
    QList<EnumDef> enumList;
    QMap<QByteArray, QByteArray> flagAliases;

    int begin;
    int end;
    bool isGenerated;
};

struct NamespaceDef {
    QByteArray name;
    int begin;
    int end;
};

class Moc : public Parser
{
public:
    Moc();

    QByteArray filename;

    bool noInclude;
    bool generatedCode;
    QByteArray includePath;
    QList<QByteArray> includeFiles;
    QList<ClassDef> classList;
    QMap<QByteArray, QByteArray> interface2IdMap;
    QList<QByteArray> metaTypes;
    QSet<QByteArray> knownQObjectClasses;

    void parse();
    void generate(FILE *out);
    void generateClassDot(ClassDef *classDef, QList<ClassDef>* classList, FILE *outfile = 0);
protected:
    void infoClass(ClassDef* cdef);
    void alreadyPrintedClass(QByteArray name, FILE* out, QList<ClassDef>* classList);
    void printClassNode(QByteArray name, FILE* out, QList<ClassDef>* classList, ClassDef* cdef = 0);
    QString toString(const Type* t, bool toHtml = true);
    QString toString(const AttributeDef* def, bool simle = false);
    QString baseContainerToString(const AttributeDef* def);
    QString toString(const FunctionDef* def, bool simple = false);
    QByteArray toIdentifier(const QByteArray name) const;
    QString stringToHtml(QString in);
    ClassDef* findClassDef(QList<ClassDef>* classList, QByteArray name);
    QList<QString> m_alreadyPrinted;
public:

    bool parseClassHead(ClassDef *def);
    inline bool inClass(const ClassDef *def) const {
        return index > def->begin && index < def->end - 1;
    }

    inline bool inNamespace(const NamespaceDef *def) const {
        return index > def->begin && index < def->end - 1;
    }

    Type parseType(bool templateType = false);

    bool parseEnum(EnumDef *def);

    bool parseFunction(FunctionDef *def, bool inMacro = false);
    bool parseMaybeFunction(const ClassDef *cdef, FunctionDef *def);

    void parseSlots(ClassDef *def, FunctionDef::Access access);
    void parseSignals(ClassDef *def);
    void parseSerializable(ClassDef *def, AttributeDef::Access access);
    void parseProperty(ClassDef *def);
    void parseEnumOrFlag(ClassDef *def, bool isFlag);
    void parseFlag(ClassDef *def);
    void parseClassInfo(ClassDef *def);
    void parseInterfaces(ClassDef *def);
    void parseDeclareInterface();
    void parseDeclareMetatype();
    void parseSlotInPrivate(ClassDef *def, FunctionDef::Access access);

    void parseFunctionArguments(FunctionDef *def);

    QByteArray lexemUntil(Token);
    bool until(Token);

    // test for Q_INVOCABLE, Q_SCRIPTABLE, etc. and set the flags
    // in FunctionDef accordingly
    bool testFunctionAttribute(FunctionDef *def);
    bool testFunctionAttribute(Token tok, FunctionDef *def);

    void checkSuperClasses(ClassDef *def);
/**************************************************************************************/
/*                                 Serialization stuff                                */
/**************************************************************************************/
    bool parseAttribute(AttributeDef *def, bool inMacro = false);
    bool parseMaybeAttribute(AttributeDef *def);
    static bool isBaseSerializableAttribute(Type& type);
    static bool isBaseSerializableAttribute(QByteArray type);
    static bool isContainer(Type& type);
    static bool isContainer(QByteArray type);
    static Type::TypeNameId getTypeId(QByteArray name);
};

inline QByteArray noRef(const QByteArray &type)
{
    if (type.endsWith('&'))
        return type.left(type.length()-1);
    return type;
}



#endif // MOC_H
