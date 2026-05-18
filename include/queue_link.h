#ifndef QUEUE_LINK_H
#define QUEUE_LINK_H

#include "BT.h"

struct node_Q {
  link value; /* value of node */
  struct node_Q *next; /* pointer to next node */
};

struct queue {
  struct node_Q *first; /* pointer to first node of queue */
  struct node_Q *last; /* pointer to last node of queue */
};

/** Allocates memory for a new node of value h and returns its address */
struct node_Q *new_node_Q(link h);
/** Frees memory allocated to a node */
void delete_node_Q(struct node_Q **nq);
/** Allocates memory for an empty queue and return its address */
struct queue *init_queue();
/** Frees all memory allocated to a queue and all its nodes */
void delete_queue(struct queue **q);
/** Tests whether a queue is empty (returns 1) or not (returns 0) */
int is_empty_queue(const struct queue *q);
/** Dequeues a node from a queue and returns the dequeued node */
/** N.B. Requires that the queue be not empty */
link dequeue(struct queue *q);
/** Enqueues a node to a queue */
void enqueue(struct queue *q, link h);

#endif
