/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     test
 *  Filename:   test_deque.c
 *
 *  The implementation of deque test.
 *
 *  2009-02-06 16:01:53
 * =============================================================================
 */

/** include section **/
#include <stdio.h>

#include "cdeque.h"
#include "calgorithm.h"
#include "test_deque.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
static void _print_int(const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_deque(void)
{
    {
        size_t i = 0;
        deque_t t_dq = create_deque(double);

        deque_init(&t_dq);
        for(i = 0; i < 6; ++i)
        {
            deque_push_front(&t_dq, (i + 1) * 1.1);
        }
        for(i = 0; i < deque_size(&t_dq); ++i)
        {
            printf("%f, ", *(double*)deque_at(&t_dq, i));
        }
        printf("\n");

        deque_destroy(&t_dq);
    }
    {
        deque_t t_dq = create_deque(int);
        size_t i = 0;

        deque_init(&t_dq);
        deque_assign_elem(&t_dq, 3, 300);
        deque_push_back(&t_dq, 500);
        deque_push_front(&t_dq, 100);

        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print_int);
        printf("\n");

        deque_pop_front(&t_dq);
        deque_pop_back(&t_dq);
        for(i = 1; i < deque_size(&t_dq); ++i)
        {
            *(int*)deque_at(&t_dq, i) += 50;
        }

        deque_resize_elem(&t_dq, 5, -300);

        algo_for_each(deque_begin(&t_dq), deque_end(&t_dq), _print_int);
        printf("\n");

        deque_destroy(&t_dq);
    }
}

/** local function implementation section **/
static void _print_int(const void* cpv_input, void* pv_output)
{
    pv_output = NULL;
    printf("%d ", *(int*)cpv_input);
}

/** eof **/

