/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     test
 *  Filename:   test_queue.c
 *
 *  The implementation of queue test.
 *
 *  2009-02-09 09:44:00
 * =============================================================================
 */

/** include section **/
#include <stdio.h>

#include "cqueue.h"
#include "test_queue.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_queue(void)
{
    {
        queue_t t_q = create_queue(int);

        queue_init(&t_q);
        printf("queue - size:%u, empty:%d\n", queue_size(&t_q), queue_empty(&t_q));

        queue_push(&t_q, 100);
        queue_push(&t_q, 200);
        queue_push(&t_q, 300);
        printf("queue - size:%u, empty:%d\n", queue_size(&t_q), queue_empty(&t_q));
        printf("front:%d, back:%d\n", *(int*)queue_front(&t_q), *(int*)queue_back(&t_q));
        *(int*)queue_front(&t_q) = 5000;
        *(int*)queue_back(&t_q) = -10000;
        printf("queue - size:%u, empty:%d\n", queue_size(&t_q), queue_empty(&t_q));
        printf("front:%d, back:%d\n", *(int*)queue_front(&t_q), *(int*)queue_back(&t_q));

        while(!queue_empty(&t_q))
        {
            printf("%d ", *(int*)queue_front(&t_q));
            queue_pop(&t_q);
        }
        printf("\n");

        queue_destroy(&t_q);
    }
}

void test_priority_queue(void)
{
    {
        priority_queue_t t_pq = create_priority_queue(int);
        size_t t_index = 0;
        vector_t t_v = create_vector(int);

        /*priority_queue_init(&t_pq, NULL, NULL);*/
        vector_init(&t_v);

        /*priority_queue_push(&t_pq, 3);*/
        /*priority_queue_push(&t_pq, 9);*/
        /*priority_queue_push(&t_pq, 4);*/
        /*priority_queue_push(&t_pq, 0);*/
        /*priority_queue_push(&t_pq, 6);*/
        /*priority_queue_push(&t_pq, 5);*/
        /*priority_queue_push(&t_pq, 7);*/
        /*priority_queue_push(&t_pq, 1);*/
        /*priority_queue_push(&t_pq, 2);*/
        /*priority_queue_push(&t_pq, 8);*/
        vector_push_back(&t_v, 5);
        vector_push_back(&t_v, 4);
        vector_push_back(&t_v, 7);
        vector_push_back(&t_v, 8);
        vector_push_back(&t_v, 0);
        vector_push_back(&t_v, 9);
        vector_push_back(&t_v, 2);
        vector_push_back(&t_v, 1);
        vector_push_back(&t_v, 3);
        vector_push_back(&t_v, 6);
        priority_queue_init_copy_range(&t_pq, vector_begin(&t_v), vector_end(&t_v));

        for(t_index = 0; t_index < priority_queue_size(&t_pq); ++t_index)
        {
            printf("%d, ", *(int*)priority_queue_top(&t_pq));
        }
        printf("\n");
        while(!priority_queue_empty(&t_pq))
        {
            printf("%d, ", *(int*)priority_queue_top(&t_pq));
            priority_queue_pop(&t_pq);
        }
        printf("\n");

        priority_queue_destroy(&t_pq);
    }
    {
        priority_queue_t t_pq = create_priority_queue(double);

        priority_queue_init(&t_pq);
        priority_queue_push(&t_pq, 66.6);
        priority_queue_push(&t_pq, 22.2);
        priority_queue_push(&t_pq, 44.4);

        printf("%f ", *(double*)priority_queue_top(&t_pq));
        priority_queue_pop(&t_pq);
        printf("%f ", *(double*)priority_queue_top(&t_pq));
        priority_queue_pop(&t_pq);
        printf("\n");

        priority_queue_push(&t_pq, 11.1);
        priority_queue_push(&t_pq, 55.5);
        priority_queue_push(&t_pq, 33.3);
        priority_queue_pop(&t_pq);

        while(!priority_queue_empty(&t_pq))
        {
            printf("%f ", *(double*)priority_queue_top(&t_pq));
            priority_queue_pop(&t_pq);
        }
        printf("\n");

        priority_queue_destroy(&t_pq);
    }
}

/** local function implementation section **/

/** eof **/

