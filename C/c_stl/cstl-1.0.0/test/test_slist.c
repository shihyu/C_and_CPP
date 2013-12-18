/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     test
 *  Filename:   test_slist.c
 *
 *  The implementation of slist test.
 *
 *  2009-02-07 09:20:59
 * =============================================================================
 */

/** include section **/
#include <stdio.h>

#include "cslist.h"
#include "calgorithm.h"
#include "test_slist.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _print_int(const void* cpv_input, void* pv_output);
static void _print_slist(
    const slist_t* cpt_first, const slist_t* cpt_second,
    const slist_t* cpt_third, const slist_t* cpt_fourth);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_slist(void)
{
    {
        slist_t t_sl1 = create_slist(int);
        slist_t t_sl2 = create_slist(int);
        slist_t t_sl3 = create_slist(int);
        slist_t t_sl4 = create_slist(int);
        int i = 0;

        slist_init(&t_sl1);
        slist_init(&t_sl2);
        slist_init(&t_sl3);
        slist_init(&t_sl4);
        for(i = 0; i < 6; ++i)
        {
            slist_push_front(&t_sl1, i+1);
            slist_push_front(&t_sl2, -i-1);
            slist_push_front(&t_sl3, i+1);
            slist_push_front(&t_sl4, -i-1);
        }
        _print_slist(&t_sl1, &t_sl2, &t_sl3, &t_sl4);

        slist_splice_pos(
            &t_sl1,
            algo_find(slist_begin(&t_sl1), slist_end(&t_sl1), 3),
            &t_sl2,
            algo_find(slist_begin(&t_sl2), slist_end(&t_sl2), -3));
        slist_splice_after_pos(
            &t_sl3,
            algo_find(slist_begin(&t_sl3), slist_end(&t_sl3), 3),
            &t_sl4,
            algo_find(slist_begin(&t_sl4), slist_end(&t_sl4), -3));
        _print_slist(&t_sl1, &t_sl2, &t_sl3, &t_sl4);

        slist_destroy(&t_sl1);
        slist_destroy(&t_sl2);
        slist_destroy(&t_sl3);
        slist_destroy(&t_sl4);
    }
}

/** local function implementation section **/
static void _print_int(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%d ", *(int*)cpv_input);
}

static void _print_slist(
    const slist_t* cpt_first, const slist_t* cpt_second,
    const slist_t* cpt_third, const slist_t* cpt_fourth)
{
    printf("slist1: ");
    algo_for_each(slist_begin(cpt_first), slist_end(cpt_first), _print_int);
    printf("\n");
    printf("slist2: ");
    algo_for_each(slist_begin(cpt_second), slist_end(cpt_second), _print_int);
    printf("\n");
    printf("slist3: ");
    algo_for_each(slist_begin(cpt_third), slist_end(cpt_third), _print_int);
    printf("\n");
    printf("slist4: ");
    algo_for_each(slist_begin(cpt_fourth), slist_end(cpt_fourth), _print_int);
    printf("\n\n");
}

/** eof **/

