/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     stack
 *  Filename:   cstl_stack.c
 *
 *  the implementation of stack.
 *
 *  2008-12-14 17:40:35
 * =============================================================================
 */

/** include section **/
#include "cdeque.h"
#include "clist.h"
#include "cvector.h"

#include "cstl_stack_private.h"
#include "cstl_stack.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* stack private function */
stack_t _create_stack(size_t t_typesize, const char* sz_typename)
{
    stack_t t_newstack;

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    *_GET_STACK_VECTOR_SEQUENCE(&t_newstack) =  
        _create_vector(t_typesize, sz_typename);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    *_GET_STACK_LIST_SEQUENCE(&t_newstack) = 
        _create_list(t_typesize, sz_typename);
#else
    *_GET_STACK_DEQUE_SEQUENCE(&t_newstack) = 
        _create_deque(t_typesize, sz_typename);
#endif

    return t_newstack;
}

/* stack function */
void stack_init(stack_t* pt_stack)
{
    assert(pt_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_init(_GET_STACK_VECTOR_SEQUENCE(pt_stack));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_init(_GET_STACK_LIST_SEQUENCE(pt_stack));
#else
    deque_init(_GET_STACK_DEQUE_SEQUENCE(pt_stack));
#endif
}

void stack_destroy(stack_t* pt_stack)
{
    assert(pt_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_destroy(_GET_STACK_VECTOR_SEQUENCE(pt_stack));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_destroy(_GET_STACK_LIST_SEQUENCE(pt_stack));
#else
    deque_destroy(_GET_STACK_DEQUE_SEQUENCE(pt_stack));
#endif
}

void stack_init_copy(stack_t* pt_stackdest, const stack_t* cpt_stacksrc)
{
    assert(pt_stackdest != NULL && cpt_stacksrc != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_init_copy(
        _GET_STACK_VECTOR_SEQUENCE(pt_stackdest),
        _GET_STACK_VECTOR_SEQUENCE(cpt_stacksrc));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_init_copy(
        _GET_STACK_LIST_SEQUENCE(pt_stackdest),
        _GET_STACK_LIST_SEQUENCE(cpt_stacksrc));
#else
    deque_init_copy(
        _GET_STACK_DEQUE_SEQUENCE(pt_stackdest),
        _GET_STACK_DEQUE_SEQUENCE(cpt_stacksrc));
#endif
}

void stack_assign(stack_t* pt_stackdest, const stack_t* cpt_stacksrc)
{
    assert(pt_stackdest != NULL && cpt_stacksrc != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_assign(
        _GET_STACK_VECTOR_SEQUENCE(pt_stackdest),
        _GET_STACK_VECTOR_SEQUENCE(cpt_stacksrc));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_assign(
        _GET_STACK_LIST_SEQUENCE(pt_stackdest),
        _GET_STACK_LIST_SEQUENCE(cpt_stacksrc));
#else
    deque_assign(
        _GET_STACK_DEQUE_SEQUENCE(pt_stackdest),
        _GET_STACK_DEQUE_SEQUENCE(cpt_stacksrc));
#endif
}

bool_t stack_empty(const stack_t* cpt_stack)
{
    assert(cpt_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_empty(_GET_STACK_VECTOR_SEQUENCE(cpt_stack));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_empty(_GET_STACK_LIST_SEQUENCE(cpt_stack));
#else
    return deque_empty(_GET_STACK_DEQUE_SEQUENCE(cpt_stack));
#endif
}

size_t stack_size(const stack_t* cpt_stack)
{
    assert(cpt_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_size(_GET_STACK_VECTOR_SEQUENCE(cpt_stack));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_size(_GET_STACK_LIST_SEQUENCE(cpt_stack));
#else
    return deque_size(_GET_STACK_DEQUE_SEQUENCE(cpt_stack));
#endif
}

void* stack_top(const stack_t* cpt_stack)
{
    assert(cpt_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_back(_GET_STACK_VECTOR_SEQUENCE(cpt_stack));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_back(_GET_STACK_LIST_SEQUENCE(cpt_stack));
#else
    return deque_back(_GET_STACK_DEQUE_SEQUENCE(cpt_stack));
#endif
}

void _stack_push(stack_t* pt_stack, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_stack);
    _stack_push_varg(pt_stack, val_elemlist);
}

void _stack_push_varg(stack_t* pt_stack, va_list val_elemlist)
{
    assert(pt_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    _vector_push_back_varg(_GET_STACK_VECTOR_SEQUENCE(pt_stack), val_elemlist);
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    _list_push_back_varg(_GET_STACK_LIST_SEQUENCE(pt_stack), val_elemlist);
#else
    _deque_push_back_varg(_GET_STACK_DEQUE_SEQUENCE(pt_stack), val_elemlist);
#endif
}

void stack_pop(stack_t* pt_stack)
{
    assert(pt_stack != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    vector_pop_back(_GET_STACK_VECTOR_SEQUENCE(pt_stack));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    list_pop_back(_GET_STACK_LIST_SEQUENCE(pt_stack));
#else
    deque_pop_back(_GET_STACK_DEQUE_SEQUENCE(pt_stack));
#endif
}

bool_t stack_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond)
{
    assert(cpt_stackfirst != NULL && cpt_stacksecond != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_equal(
        _GET_STACK_VECTOR_SEQUENCE(cpt_stackfirst),
        _GET_STACK_VECTOR_SEQUENCE(cpt_stacksecond));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_equal(
        _GET_STACK_LIST_SEQUENCE(cpt_stackfirst),
        _GET_STACK_LIST_SEQUENCE(cpt_stacksecond));
#else
    return deque_equal(
        _GET_STACK_DEQUE_SEQUENCE(cpt_stackfirst),
        _GET_STACK_DEQUE_SEQUENCE(cpt_stacksecond));
#endif
}

bool_t stack_not_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond)
{
    assert(cpt_stackfirst != NULL && cpt_stacksecond != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_not_equal(
        _GET_STACK_VECTOR_SEQUENCE(cpt_stackfirst),
        _GET_STACK_VECTOR_SEQUENCE(cpt_stacksecond));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_not_equal(
        _GET_STACK_LIST_SEQUENCE(cpt_stackfirst),
        _GET_STACK_LIST_SEQUENCE(cpt_stacksecond));
#else
    return deque_not_equal(
        _GET_STACK_DEQUE_SEQUENCE(cpt_stackfirst),
        _GET_STACK_DEQUE_SEQUENCE(cpt_stacksecond));
#endif
}

bool_t stack_less(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond)
{
    assert(cpt_stackfirst != NULL && cpt_stacksecond != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_less(
        _GET_STACK_VECTOR_SEQUENCE(cpt_stackfirst),
        _GET_STACK_VECTOR_SEQUENCE(cpt_stacksecond));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_less(
        _GET_STACK_LIST_SEQUENCE(cpt_stackfirst),
        _GET_STACK_LIST_SEQUENCE(cpt_stacksecond));
#else
    return deque_less(
        _GET_STACK_DEQUE_SEQUENCE(cpt_stackfirst),
        _GET_STACK_DEQUE_SEQUENCE(cpt_stacksecond));
#endif
}

bool_t stack_great(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond)
{
    assert(cpt_stackfirst != NULL && cpt_stacksecond != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_great(
        _GET_STACK_VECTOR_SEQUENCE(cpt_stackfirst),
        _GET_STACK_VECTOR_SEQUENCE(cpt_stacksecond));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_great(
        _GET_STACK_LIST_SEQUENCE(cpt_stackfirst),
        _GET_STACK_LIST_SEQUENCE(cpt_stacksecond));
#else
    return deque_great(
        _GET_STACK_DEQUE_SEQUENCE(cpt_stackfirst),
        _GET_STACK_DEQUE_SEQUENCE(cpt_stacksecond));
#endif
}

bool_t stack_less_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond)
{
    assert(cpt_stackfirst != NULL && cpt_stacksecond != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_less_equal(
        _GET_STACK_VECTOR_SEQUENCE(cpt_stackfirst),
        _GET_STACK_VECTOR_SEQUENCE(cpt_stacksecond));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_less_equal(
        _GET_STACK_LIST_SEQUENCE(cpt_stackfirst),
        _GET_STACK_LIST_SEQUENCE(cpt_stacksecond));
#else
    return deque_less_equal(
        _GET_STACK_DEQUE_SEQUENCE(cpt_stackfirst),
        _GET_STACK_DEQUE_SEQUENCE(cpt_stacksecond));
#endif
}

bool_t stack_great_equal(
    const stack_t* cpt_stackfirst, const stack_t* cpt_stacksecond)
{
    assert(cpt_stackfirst != NULL && cpt_stacksecond != NULL);

#if defined (CSTL_STACK_VECTOR_SEQUENCE)
    return vector_great_equal(
        _GET_STACK_VECTOR_SEQUENCE(cpt_stackfirst),
        _GET_STACK_VECTOR_SEQUENCE(cpt_stacksecond));
#elif defined (CSTL_STACK_LIST_SEQUENCE)
    return list_great_equal(
        _GET_STACK_LIST_SEQUENCE(cpt_stackfirst),
        _GET_STACK_LIST_SEQUENCE(cpt_stacksecond));
#else
    return deque_great_equal(
        _GET_STACK_DEQUE_SEQUENCE(cpt_stackfirst),
        _GET_STACK_DEQUE_SEQUENCE(cpt_stacksecond));
#endif
}

/** local function implementation section **/

/** eof **/

