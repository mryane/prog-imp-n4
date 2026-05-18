#include "BT.h"
#include "binary_tree.h"
#include "stack_link.h"

#include <stdlib.h>
#include <stdio.h>

/************************************************/
/*******  Maximal priority = least value ********/
/************************************************/

/** Searches a BST for a label and returns a pointer to a node with this label
 */
/* Returns NULL if there is no node with the required label */
/** Time complexity \Omega(n) in the worst case, where n is the size of the tree
 * **/
link search_BST(link tree, item value)
{
    if (tree == NULL)
    {
        return NULL;
    }

    if (tree->label == value)
    {
        return tree;
    }

    if (value < tree->label)
    {
        return search_BST(tree->left, value);
    }
    else
    {
        return search_BST(tree->right, value);
    }
}

/** Inserts RECURSIVELY a node with a given label in a BST (as a new leaf) */
/* and returns a link to the updated BST */
/** Time complexity \Omega(n) in the worst case, where n is the size of the tree
 * **/
link insert_BST(link tree, item value)
{
    if (tree == NULL)
    {
        return cons_binary_tree(value, NULL, NULL);
    }

    if (value < tree->label)
    {
        tree->left = insert_BST(tree->left, value);
    }
    else
    {
        tree->right = insert_BST(tree->right, value);
    }

    return tree;
}

/**********  LEAF-INSERTION ****************/
/** Inserts ITERATIVELY a node with a given label in a BST (as a new leaf)*/
/* and returns the updated BST */
/** N.B. The function does not use a stack */
/** Time complexity \Omega(n) in the worst case, where n is the size of the tree
 * **/
link insert_BST_it(link tree, item value)
{
    if (tree == NULL)
    {
        return cons_binary_tree(value, NULL, NULL);
    }

    link currentNode = tree;
    link *newNode;

    while (currentNode != NULL)
    {
        if (value < currentNode->label)
        {
            newNode = &currentNode->left;
            currentNode = currentNode->left;
        }
        else
        {
            newNode = &currentNode->right;
            currentNode = currentNode->right;
        }
    }

    (*newNode) = cons_binary_tree(value, NULL, NULL);

    return tree;
}

/** Selects the kth label of a BST */
/* and returns a pointer to the corresponding node */
/* Returns NULL if the BST does not contain k labels */
/** Time complexity \Omega(n^2) in the worst case, where n is the size of the
 * tree **/
link select_BST(link tree, int k)
{
    if (tree == NULL)
    {
        return NULL;
    }

    int leftSize = size_binary_tree(tree->left);
    
    if (leftSize > k)
    {
        return select_BST(tree->left, k);
    }
      
    if (leftSize < k)
    {
        return select_BST(tree->right, k - leftSize - 1);
    }
      
    return tree;
}

/*************     ROTATIONS        *************/

/** Applies a right rotation the root of a BST */
/** Time complexity \Theta(1) in the worst case **/
link rotate_right(link tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    link newRoot = tree->left;
    link oldRootNewLeft = tree->left->right;

    newRoot->right = tree;
    tree->left = oldRootNewLeft;

    return newRoot;
}

/** Applies a left rotation to the root of a BST */
link rotate_left(link tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    link newRoot = tree->right;
    link oldRootNewRight = tree->right->left;

    newRoot->left = tree;
    tree->right = oldRootNewRight;

    return newRoot;
}

/************   ROOT-INSERTION ****************/
/** Inserts RECURSIVELY a node with a given label at the root of BST */
/* and returns the updated BST */
/** Time complexity \Omega(n) in the worst case, where n is the size of the tree
 * **/
link insert_BST_root(link tree, item value)
{
    if (tree == NULL)
    {
        return cons_binary_tree(value, NULL, NULL);
    }

    if (value < tree->label)
    {
        tree->left = insert_BST_root(tree->left, value);
        tree = rotate_right(tree);
    }
    else
    {
        tree->right = insert_BST_root(tree->right, value);
        tree = rotate_left(tree);
    }

    return tree;
}

link insert_BST_root_it(link tree, item value)
{
    if (tree == NULL)
    {
        return cons_binary_tree(value, NULL, NULL);
    }

    int treeSize = size_binary_tree(tree);
    int *directions = (int *) malloc(sizeof(int) * treeSize);
    int currentIndex = 0;
    struct stack *nodeStack = init_stack(treeSize);
    link currentNode = tree;
    link parentNode;

    while (currentNode != NULL)
    {
        push_stack(nodeStack, currentNode);
        parentNode = currentNode;

        if (value < currentNode->label)
        {
            currentNode = currentNode->left;
            directions[currentIndex] = 1;
        }
        else
        {
            currentNode = currentNode->right;
            directions[currentIndex] = 0;
        }

        currentIndex++;
    }

    link newNode = cons_binary_tree(value, NULL, NULL);

    if (directions[currentIndex - 1])
    {
        parentNode->left = newNode;
    }
    else
    {
        parentNode->right = newNode;
    }

    while (!is_empty_stack(nodeStack))
    {
        parentNode = pop_stack(nodeStack);
        
        if (directions[--currentIndex])
        {
            parentNode = rotate_right(parentNode);
        }
        else
        {
            parentNode = rotate_left(parentNode);
        }

        if (!is_empty_stack(nodeStack))
        {
            link grandParent = pop_stack(nodeStack);

            if (directions[currentIndex - 1])
            {
                grandParent->left = parentNode;
            }
            else
            {
                grandParent->right = parentNode;
            }

            push_stack(nodeStack, grandParent);
        }
    }

    delete_stack(&nodeStack);
    free(directions);

    return parentNode;
}

link partition_BST(link tree, int k)
{
    if (tree == NULL)
    {
        return NULL;
    }

    int leftSize = size_binary_tree(tree->left);
    
    if (k < leftSize)
    {
        link node = partition_BST(tree->left, k);

        if (node == NULL)
        {
            return NULL;
        }

        tree->left = node;
        tree = rotate_right(tree);

        return tree;
    }
    else if (k > leftSize)
    {
        link node = partition_BST(tree->right, k - leftSize - 1);

        if (node == NULL)
        {
            return NULL;
        }

        tree->right = node;
        tree = rotate_left(tree);

        return tree;
    }
    else
    {
        return tree;
    }
}

link balence_BST(link tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    int sizeTree = size_binary_tree(tree);
    int middleRank = sizeTree / 2;

    tree = partition_BST(tree, middleRank);

    tree->left = balence_BST(tree->left);
    tree->right = balence_BST(tree->right);

    return tree;
}

link delete_node_BST(link tree, item value)
{
    if (tree == NULL)
    {
        return NULL;
    }

    if (value == tree->label)
    {
        link left = tree->left;
        link right = tree->right;

        free(tree);

        if (left == NULL && right == NULL)
        {
            return NULL;
        }
        else if (left != NULL)
        {
            tree = partition_BST(left, 0);
        }
        else
        {
            tree = partition_BST(right, 0);
        }
    }
    else if (value < tree->label)
    {
        tree->left = delete_node_BST(tree->left, value);
    }
    else
    {
        tree->right = delete_node_BST(tree->right, value);
    }

    return tree;
}

link join_BST(link treeH, link treeK)
{
    if (treeH == NULL)
    {
        return treeK;
    }
    else if (treeK == NULL)
    {
        return treeH;
    }

    link newTree = insert_BST_root(treeK, treeH->label);

    newTree->left = join_BST(treeH->left, treeK->left);
    newTree->right = join_BST(treeH->right, treeK->right);

    free(treeH);

    return newTree;
}

int is_red(link tree)
{
    return tree != NULL && tree->color == RED;
}

int is_black(link tree)
{
    return tree == NULL || tree->color == BLACK;
}

void flip_color(link tree)
{
    tree->color = !tree->color;
}

link insert_LLRB(link tree, item value)
{
    if (tree == NULL)
    {
        return cons_binary_tree(value, NULL, NULL);
    }

    int changeColor;

    if (value < tree->label)
    {
        changeColor = tree->left == NULL;
        tree->left = insert_LLRB(tree->left, value);
        
        if (changeColor)
        {
            tree->left->color = RED;
        }
    }
    else
    {
        changeColor = tree->right == NULL;
        tree->right = insert_LLRB(tree->right, value);
        
        if (changeColor)
        {
            tree->right->color = RED;
        }
    }

    if (is_red(tree->right) && is_black(tree->left))
    {
        tree = rotate_left(tree);
    }

    if (is_red(tree->left) && is_red(tree->left->left))
    {
        tree = rotate_right(tree);
    }

    if (is_red(tree->left) && is_red(tree->right))
    {
        flip_color(tree);
        flip_color(tree->left);
        flip_color(tree->right);
    }

    return tree;
}
