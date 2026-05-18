#include "binary_tree.h"
#include "BT.h"

#include "stack_link.h"
#include "queue_link.h"

#include <stdlib.h>
#include <stdio.h>

/** "Creates" an empty tree and returns its address */
link empty_tree()
{
    return NULL;
}

/* Constructs a binary tree from a label and two binary trees */
/* (allocates memory and returns the allocated block's address) */
link cons_binary_tree(item _label, const link _left, const link _right)
{
    link tree = malloc(sizeof(struct binary_tree));

    tree->label = _label;
    tree->left = _left;
    tree->right = _right;
    tree->color = BLACK;

    return tree;
}

/* Frees all memory allocated to a tree and its subtrees */
void delete_binary_tree(link *tree)
{
    if (*tree == NULL)
    {
        return;
    }

    delete_binary_tree(&(*tree)->left);
    delete_binary_tree(&(*tree)->right);

    free(*tree);
    *tree = NULL;
}

/** Returns the left subtree of a tree */
/* (requires that the tree be non-empty) */
link left(const link tree)
{
    return tree->left;
}

/** Returns the right subtree of a tree */
/* (requires that the tree be non-empty) */
link right(const link tree)
{
    return tree->right;
}

/** Returns the label of the root of a tree */
/* (requires that the tree be non-empty) */
item get_binary_tree_root(const link tree)
{
    return tree->label;
}

/** Tests a tree for emptyness */
int is_empty_binary_tree(const link tree)
{
    return tree == empty_tree();
}

/** Computes recursively and returns the size of a tree */
int size_binary_tree(const link tree)
{
    if (tree == NULL)
    {
        return 0;
    }

    return 1 + size_binary_tree(tree->left) + size_binary_tree(tree->right);
}

/** Computes recursively and returns the height of a tree */
/* N.B. height(empty tree) = -1, height(one-node tree) = 0 */
int height_binary_tree(const link tree)
{
    if (is_empty_binary_tree(tree))
    {
        return -1;
    }

    int leftSize = height_binary_tree(tree->left);
    int rightSize = height_binary_tree(tree->right);
    int max = leftSize > rightSize ? leftSize : rightSize;

    return max + 1;
}

/** Displays information attached to the root */
void print_label(const link tree)
{
    printf("%c", tree->label);
}

/** Prints a tree (rotated by -\pi/2) */
void show_binary_tree(const link tree, int depth)
{
    if (is_empty_binary_tree(tree))
    {
        return;
    }

    show_binary_tree(tree->right, depth + 1);

    for (int i = 0; i < depth; i++)
    {
        printf("    ");
    }

    printf("%c\n", tree->label);

    show_binary_tree(tree->left, depth + 1);
}

/** Traverses recursively a tree according to inorder */
void traverse_inorder_binary_tree(link tree, void (*visitor)(link))
{
    if (is_empty_binary_tree(tree))
    {
        return;
    }

    traverse_inorder_binary_tree(tree->left, visitor);
    visitor(tree);
    traverse_inorder_binary_tree(tree->right, visitor);
}

/** Traverses recursively a tree according to preorder */
void traverse_preorder_binary_tree(link tree, void (*visitor)(link))
{
    if (is_empty_binary_tree(tree))
    {
        return;
    }

    visitor(tree);
    traverse_inorder_binary_tree(tree->left, visitor);
    traverse_inorder_binary_tree(tree->right, visitor);
}

/** Traverses recursively a tree according to postorder */
void traverse_postorder_binary_tree(link tree, void (*visitor)(link))
{
    if (is_empty_binary_tree(tree))
    {
        return;
    }

    traverse_inorder_binary_tree(tree->left, visitor);
    traverse_inorder_binary_tree(tree->right, visitor);
    visitor(tree);
}

/** Traverses iteratively a tree according to preorder (using a stack) */
void traverse_preorder_it_BT(link tree, void (*visitor)(link))
{
    if (tree == NULL)
    {
        return;
    }

    struct stack *nodeStack = init_stack(size_binary_tree(tree));
    push_stack(nodeStack, tree);

    while (! is_empty_stack(nodeStack))
    {
        link currentNode = pop_stack(nodeStack);

        if (currentNode == NULL)
        {
            continue;
        }

        visitor(currentNode);
        push_stack(nodeStack, currentNode->right);
        push_stack(nodeStack, currentNode->left);
    }

    delete_stack(&nodeStack);
}

/** Traverses iteratively a tree according to inorder (using a stack) */
void traverse_inorder_it_BT(link tree, void (*visitor)(link))
{
    if (tree == NULL)
    {
        return;
    }

    struct stack *nodeStack = init_stack(size_binary_tree(tree));
    push_stack(nodeStack, tree);

    while (! is_empty_stack(nodeStack))
    {
        link currentNode = pop_stack(nodeStack);

        /* Si on a atteint une feuille */
        if (currentNode == NULL)
        {
            /* Récupère le parent */
            currentNode = pop_stack(nodeStack);
            visitor(currentNode);

            push_stack(nodeStack, currentNode->right);
        }
        else
        {
            push_stack(nodeStack, currentNode);
            push_stack(nodeStack, currentNode->left); /* Permet de d'abord visiter l'enfant de gauche */
        }
    }

    delete_stack(&nodeStack);
}

/** Traverses iteratively a tree according to level-order (using a queue) */
void traverse_level_BT(link tree, void (*visitor)(link))
{
    if (tree == NULL)
    {
        return;
    }

    struct queue *nodeQueue = init_queue();
    enqueue(nodeQueue, tree);

    while (!is_empty_queue(nodeQueue))
    {
        link currentNode = dequeue(nodeQueue);

        visitor(currentNode);

        if (currentNode->left) enqueue(nodeQueue, currentNode->left);
        if (currentNode->right) enqueue(nodeQueue, currentNode->right);
    }

    delete_queue(&nodeQueue);
}
