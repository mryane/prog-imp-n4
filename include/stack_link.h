#ifndef STACK_LINK_H
#define STACK_LINK_H

#include "BT.h"

struct stack {
  int top; /* height of the stack */
  link *contents; /* contents of the stack */
};

/** Allocates memory for a stack of maximal height maxTop */
struct stack *init_stack(int maxTop);
/** Frees the memory allocated to a stack */
void delete_stack(struct stack **s);
/** Tests whether a stack is empty (returns 1) or not (returns 0) */
int is_empty_stack(const struct stack *s);
/** Adds a new element on the top of a stack */
void push_stack(struct stack *s, link val);
/** Removes an element from the top of a stack and returns it */
/** N.B. Requires that the stack be non-empty */
link pop_stack(struct stack *s);

#endif
