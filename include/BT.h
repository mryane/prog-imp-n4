#ifndef _BT_H
#define _BT_H

#include "item.h"

#define BLACK 0
#define RED 1

typedef struct binary_tree {
  item label; /* label of the root */
  struct binary_tree *left; /* NULL if no left subtrees */
  struct binary_tree *right; /* NULL if no right subtree */
  int color;
} *link;

#endif
