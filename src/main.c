#include <bits/pthreadtypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "binary_tree.h"

link parse_expr(const char *expr);
int eval_tree(link tree);
char *tree_to_expr(link tree);
char *tree_to_expr_inf(link tree);

int main_td2(int numArgs, const char **args)
{
    if (numArgs < 4)
    {
        printf("Invalid number of arguments.\n");
        return EXIT_FAILURE;
    }

    int exprSize = (numArgs - 1);
    char *expr = (char *) malloc(sizeof(char) * exprSize + 1);

    expr[exprSize] = '\0';

    for (int i = 1; i < numArgs; i++)
    {
        printf(" current char: %c\n", args[i][0]);

        expr[i - 1] = args[i][0];
    }

    link tree;
    int value;
    char *expr2;
    char *expr3;

    printf("Expression: %s\n", expr);

    tree = parse_expr(expr);
    value = eval_tree(tree);
    expr2 = tree_to_expr(tree);
    expr3 = tree_to_expr_inf(tree);

    show_binary_tree(tree, 0);
    printf("Value: %d\n", value);
    printf("Expr from tree: %s. Match: %s\n", expr2, strcmp(expr, expr2) == 0 ? "true" : "false");
    printf("Inf expr from tree: %s\n", expr3);

    delete_binary_tree(&tree);
    free(expr);
    free(expr2);
    free(expr3);

    return EXIT_SUCCESS;
}

link parse_expr_rec(const char **expr)
{
    char currentChar = **expr;

    if (currentChar == '+' || currentChar == '*')
    {
        (*expr)++;

        return cons_binary_tree(
            currentChar,
            parse_expr_rec(expr),
            parse_expr_rec(expr));
    }
    else if (currentChar >= '0' && currentChar <= '9')
    {
        (*expr)++;

        return cons_binary_tree(
            currentChar,
            empty_tree(),
            empty_tree());
    }
    else
    {
        return NULL;
    }
}

link parse_expr(const char *expr)
{
    return parse_expr_rec(&expr);
}

int eval_tree(link tree)
{
    if (tree->label >= '0' && tree->label <= '9')
    {
        return tree->label - '0';
    }
    else if (tree->label == '+')
    {
        return eval_tree(tree->left) + eval_tree(tree->right);
    }
    else if (tree->label == '*')
    {
        return eval_tree(tree->left) * eval_tree(tree->right);
    }
    else
    {
        return 0;
    }
}

void tree_to_expr_rec(link tree, char **expr)
{
    (**expr) = tree->label;
    (*expr)++;

    if (tree->label == '+' || tree->label == '*')
    {
        tree_to_expr_rec(tree->left, expr);
        tree_to_expr_rec(tree->right, expr);
    }
}

void tree_to_expr_inf_rec(link tree, char **expr)
{
    if (tree->label == '+' || tree->label == '*')
    {
        tree_to_expr_inf_rec(tree->left, expr);

        (**expr) = tree->label;
        (*expr)++;

        tree_to_expr_inf_rec(tree->right, expr);
    }
    else
    {
        (**expr) = tree->label;
        (*expr)++;
    }
}

char *tree_to_expr(link tree)
{
    int exprSize = size_binary_tree(tree);
    char *expr = (char *) malloc(exprSize + 1);
    char *exprPtrCopy = expr;

    expr[exprSize] = '\0';

    tree_to_expr_rec(tree, &exprPtrCopy);

    return expr;
}

char *tree_to_expr_inf(link tree)
{
    int exprSize = size_binary_tree(tree);
    char *expr = (char *) malloc(exprSize + 1);
    char *exprPtrCopy = expr;

    expr[exprSize] = '\0';

    tree_to_expr_inf_rec(tree, &exprPtrCopy);

    return expr;
}

void print_arr(const int *arr, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int heap_get_left_child(int i)
{
    return i * 2 + 1;
}

int heap_get_right_child(int i)
{
    return i * 2 + 2;
}

void heap_swap(int *arr, int nodeA, int nodeB)
{
    int temp = arr[nodeA];
    arr[nodeA] = arr[nodeB];
    arr[nodeB] = temp;
}

void heap_build_max(int *arr, int n, int index)
{
    if (index >= n)
    {
        return;
    }

    int largest = index;
    int left = heap_get_left_child(index);
    int right = heap_get_right_child(index);

    if (left < n && arr[largest] < arr[left])
    {
        largest = left;
    }

    if (right < n && arr[largest] < arr[right])
    {
        largest = right;
    }

    if (largest != index)
    {
        heap_swap(arr, index, largest);
        heap_build_max(arr, n, largest);
    }
}

void heap_sort(int *t, int l, int r)
{
    int n = r - l + 1;
    t += l;

    /* Appel heap_build_max en partant du bas vers le haut */
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heap_build_max(t, n, i);
    }

    for (int i = n; i > 0; i--)
    {
        heap_swap(t, 0, i - 1);
        heap_build_max(t, i, 0);
    }
}

int main_td3(int numArgs, const char **args)
{
    if (numArgs != 2)
    {
        printf("Wrong number of arguments.\n");
        return EXIT_FAILURE;
    }

    int n = atoi(args[1]);
    int *t = (int *) malloc(sizeof(int) * n);

    srand(__rdtsc());

    for (int i = 0; i < n; i++)
    {
        t[i] = rand() % 100;
    }

    print_arr(t, 0, n);
    print_arr(t, 0, n / 3);
    print_arr(t, n - (n / 3), n);

    heap_sort(t, 0, n - 1);

    print_arr(t, 0, n);

    return EXIT_SUCCESS;
}

#include "bst.h"

int main_td4(int numArgs, const char **args)
{
    if (numArgs != 2)
    {
        printf("Wrong number of arguments.\n");
        return EXIT_FAILURE;
    }

    int n = atoi(args[1]);
    char *s = (char *) malloc(n + 1);

    s[n] = '\0';

    for (int i = 0; i < n; i++)
    {
        s[i] = (rand() % 26) + 'A';
    }

    link tree0 = empty_tree();
    link tree1 = empty_tree();

    for (int i = 0; i < n; i++)
    {
        tree0 = insert_BST(tree0, s[i]);
        tree1 = insert_BST_it(tree1, s[i]);
    }

    // show_binary_tree(tree0, 0);
    // printf("\n\n\n");
    // show_binary_tree(tree1, 0);

    delete_binary_tree(&tree0);
    delete_binary_tree(&tree1);

    for (int i = 0; i < n; i++)
    {
        tree0 = insert_BST_root(tree0, s[i]);
        tree1 = insert_BST_root_it(tree1, s[i]);
    }

    show_binary_tree(tree0, 0);
    printf("\n\n\n");
    show_binary_tree(tree1, 0);

    delete_binary_tree(&tree1);

    tree0 = delete_node_BST(tree0, select_BST(tree0, n / 2)->label);
    show_binary_tree(tree0, 0);

    tree0 = balence_BST(tree0);
    show_binary_tree(tree0, 0);

    delete_binary_tree(&tree0);

    return EXIT_SUCCESS;
}

void visit_llrb_inorder(link tree, int *i, int *arr)
{
    if (tree == NULL)
    {
        return;
    }
    
    visit_llrb_inorder(tree->left, i, arr);
    
    arr[*i] = tree->label;
    (*i)++;

    visit_llrb_inorder(tree->right, i, arr);
}

int main_td5(int numArgs, const char **args)
{
    if (numArgs != 2)
    {
        printf("Wrong number of arguments.\n");
        return EXIT_FAILURE;
    }

    int i = 0;
    int n = atoi(args[1]);
    int *t = (int *) malloc(sizeof(int) * n);
    link tree = empty_tree();

    for (int i = 0; i < n; i++)
    {
        t[i] = rand() % 100;
        tree = insert_LLRB(tree, t[i]);
    }

    print_arr(t, 0, n);
    visit_llrb_inorder(tree, &i, t);
    print_arr(t, 0, n);

    delete_binary_tree(&tree);
    free(t);
    return EXIT_SUCCESS;
}

int main(int numArgs, const char **args)
{
    return main_td5(numArgs, args);
}
