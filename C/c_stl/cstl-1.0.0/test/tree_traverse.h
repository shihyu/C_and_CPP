/*
 * =============================================================================
 *  Copyright (c) 2008 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     test
 *  Filename:   tree_traverse.h
 *
 *  file description ...
 *
 *  2008-12-27 10:00:34
 * =============================================================================
 */

#ifndef _TREE_TRAVERSE_H
#define _TREE_TRAVERSE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: test_travel_avl_tree
 *        Parameters: in) pt_root: avlnode_t*
 *                        the root.
 *                    in) pfun_op: void (*)(avlnode_t*)
 *           Returns: void
 *       Description: travel tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void test_travel_avl_tree(
    avlnode_t* pt_root, size_t t_indentsize, void (*pfun_op)(avlnode_t*));

extern void test_travel_rb_tree(
    rbnode_t* pt_root, size_t t_indentsize, void (*pfun_op)(rbnode_t*));

extern void show_avlnode_info(avlnode_t* pt_root);

extern void show_rbnode_info(rbnode_t* pt_root);
extern void show_map_rbnode_info(rbnode_t* pt_root);

extern void test_travel_hashtable(vector_t* pt_vector);
extern void test_travel_hashtable_pair(vector_t* pt_vector);
#ifdef __cplusplus
}
#endif

#endif /* _TREE_TRAVERSE_H */
/** eof **/

