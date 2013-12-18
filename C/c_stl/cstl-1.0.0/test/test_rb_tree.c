/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     test
 *  Filename:   test_rb_tree.c
 *
 *  The implementation of rb tree test.
 *
 *  2009-02-11 16:54:26
 * =============================================================================
 */

/** include section **/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "cstl_types.h"
#include "cstl_alloc.h"
#include "cstl_iterator.h"

#include "cstl_rb_tree_iterator.h"
#include "cstl_rb_tree_private.h"

#include "test_rb_tree.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_rb_tree(void)
{
    rb_tree_t t_tree = _create_rb_tree(sizeof(int), "int");
    rb_tree_t t_tree2 = _create_rb_tree(sizeof(int), "int");
    int n_value = 90;

    _rb_tree_init(&t_tree, NULL, NULL);
    _rb_tree_insert_equal(&t_tree, &n_value);
    printf("rb tree1 - size:%u, max_size:%u, empty:%d\n",
        _rb_tree_size(&t_tree), _rb_tree_max_size(&t_tree), _rb_tree_empty(&t_tree));
    /*_rb_tree_init_copy_range(&t_tree2, _rb_tree_begin(&t_tree), _rb_tree_begin(&t_tree));*/
    /*printf("rb tree2 - size:%u, max_size:%u, empty:%d\n",*/
    /*_rb_tree_size(&t_tree2), _rb_tree_max_size(&t_tree2), _rb_tree_empty(&t_tree2));*/
    _rb_tree_init_copy_range_cmp(
        &t_tree2, _rb_tree_begin(&t_tree), _rb_tree_begin(&t_tree), NULL);
    printf("rb tree2 - size:%u, max_size:%u, empty:%d\n",
        _rb_tree_size(&t_tree2), _rb_tree_max_size(&t_tree2), _rb_tree_empty(&t_tree2));
    _rb_tree_insert_equal_range(
        &t_tree2, _rb_tree_begin(&t_tree), _rb_tree_begin(&t_tree));
    printf("rb tree2 - size:%u, max_size:%u, empty:%d\n",
        _rb_tree_size(&t_tree2), _rb_tree_max_size(&t_tree2), _rb_tree_empty(&t_tree2));
    _rb_tree_insert_unique_range(
        &t_tree2, _rb_tree_end(&t_tree), _rb_tree_end(&t_tree));
    printf("rb tree2 - size:%u, max_size:%u, empty:%d\n",
        _rb_tree_size(&t_tree2), _rb_tree_max_size(&t_tree2), _rb_tree_empty(&t_tree2));
    _rb_tree_erase_range(
        &t_tree2, _rb_tree_begin(&t_tree2), _rb_tree_begin(&t_tree2));
    printf("rb tree2 - size:%u, max_size:%u, empty:%d\n",
        _rb_tree_size(&t_tree2), _rb_tree_max_size(&t_tree2), _rb_tree_empty(&t_tree2));

    _rb_tree_destroy(&t_tree);
    _rb_tree_destroy(&t_tree2);
}

/** local function implementation section **/

/** eof **/

