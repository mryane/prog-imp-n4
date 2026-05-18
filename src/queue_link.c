#include "queue_link.h"
#include <stdlib.h>
#include <stdio.h>

struct node_Q *new_node_Q(link h) {
  struct node_Q *nq = malloc(sizeof(struct node_Q));
  nq->value = h;
  nq->next = NULL;
  return nq;
}

void delete_node_Q(struct node_Q **nq) {
  free(*nq);
  *nq = NULL;
}

struct queue *init_queue() {
  struct queue *q = malloc(sizeof(struct queue));
  q->first = NULL;
  q->last = NULL;
  return q;
}

void delete_queue(struct queue **q) {
  while (!is_empty_queue(*q)) {
    struct node_Q *nq = (*q)->first;
    (*q)->first = nq->next;
    delete_node_Q(&nq);
  }
  free(*q);
  *q = NULL;
}

int is_empty_queue(const struct queue *q) {
  return (NULL == q->first);
}

link dequeue(struct queue *q) {
  /* assumes q is not empty */
  struct node_Q *nq = q->first;
  link res = nq->value;
  q->first = nq->next;
  if (NULL == nq->next) {
    q->last = NULL;
  }
  delete_node_Q(&nq);
  return res;
}

void enqueue(struct queue *q, link h) {
  struct node_Q *nq = new_node_Q(h);
  if (is_empty_queue(q)) {
    q->first = nq;
  }
  else {
    q->last->next = nq;
  }
  q->last = nq;
}
