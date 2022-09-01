#ifndef _FREELIST_H_
#define _FREELIST_H_

#define MALLOC(size,type)   (type *) malloc(size)
   
#define FREELIST_LIMIT  (4)       /* default size of the free list */

typedef struct FreeList FreeList;
typedef struct node node;

struct node{
  node *next;
  node *prev;
};

struct FreeList{
  node *head;
  u_int32_t num_alloc;             /* current number of nodes allocated */
  u_int32_t num_freelist;          /* number of nodes in free list */
  u_int32_t freelist_limit;        /* If num_freelist is no less than this
				      number, the newly unused node is freed
				      instead of returned to the freelist */
};


void InitFreeList(FreeList *frlist, int limit);

node *GetNode(FreeList *frlist, size_t itemsize, int *errp);

void FreeNode(FreeList *frlist, node *nd, int *errp);

int ReverseList(node **head, node **tail, int *errp);

int ReverseDoubleList(node **head, node **tail, int *errp);

#endif
