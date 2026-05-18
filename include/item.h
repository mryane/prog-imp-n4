#ifndef _ITEM_CHAR_H
#define _ITEM_CHAR_H

typedef char item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (!less(A, B) && !less(B, A))
#define exch(A, B) { char tmp = A; A = B; B = tmp; }
#define display(A) { printf("%c ", key(A)); }
#define destroy(A)

#endif
