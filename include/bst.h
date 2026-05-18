#pragma once
#include "BT.h"

/************************************************/
/*******  Maximal priority = least value ********/
/************************************************/

/** Searches a BST for a label and returns a pointer to a node with this label
 */
/* Returns NULL if there is no node with the required label */
/** Time complexity \Omega(n) in the worst case, where n is the size of the tree
 * **/
link search_BST(link tree, item value);

/** Inserts RECURSIVELY a node with a given label in a BST (as a new leaf) */
/* and returns a link to the updated BST */
/** Time complexity \Omega(n) in the worst case, where n is the size of the tree
 * **/
link insert_BST(link tree, item value);

/**********  LEAF-INSERTION ****************/
/** Inserts ITERATIVELY a node with a given label in a BST (as a new leaf)*/
/* and returns the updated BST */
/** N.B. The function does not use a stack */
/** Time complexity \Omega(n) in the worst case, where n is the size of the tree
 * **/
link insert_BST_it(link tree, item value);

/** Selects the kth label of a BST */
/* and returns a pointer to the corresponding node */
/* Returns NULL if the BST does not contain k labels */
/** Time complexity \Omega(n^2) in the worst case, where n is the size of the
 * tree **/
link select_BST(link tree, int k);

/*************     ROTATIONS        *************/

/** Applies a right rotation the root of a BST */
/** Time complexity \Theta(1) in the worst case **/
link rotate_right(link tree);

/** Applies a left rotation to the root of a BST */
link rotate_left(link tree);

/************   ROOT-INSERTION ****************/
/** Inserts RECURSIVELY a node with a given label at the root of BST */
/* and returns the updated BST */
/** Time complexity \Omega(n) in the worst case, where n is the size of the tree
 * **/
link insert_BST_root(link tree, item value);
link insert_BST_root_it(link tree, item value);
link partition_BST(link tree, int k);
link balence_BST(link tree);
link delete_node_BST(link tree, item value);
link join_BST(link treeH, link treeK);

link insert_LLRB(link tree, item value);
