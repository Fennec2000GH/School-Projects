/*
 *      Implement a free list to reduce the number of memory allocations
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "freelist.h"

/* initialize a free list */
void InitFreeList(FreeList *frlist, int limit)
{
  frlist->head = NULL;
  frlist->num_alloc = 0;
  frlist->num_freelist = 0;
  frlist->freelist_limit = limit;
  return;
}

/* Get one free node. First, try to get one from the free list. 
   If failed, get one by memory allocation */
node *GetNode(FreeList *frlist, size_t itemsize, int *errp)
{
  node *nd = NULL;
  
  *errp = 0;
  
  /* if the free list is not empty */
  if (frlist->head != NULL) {
    nd = frlist->head;
    frlist->head = nd->next;
    frlist->num_freelist--;
    
    return (nd);
  } else {
    
    /* try to allocate one more node */
    if ( (nd = MALLOC(itemsize, node)) == NULL) {
      *errp = ENOMEM;
      return (NULL);
    } else {
      frlist->num_alloc++;
      return (nd);
    } 
  }
}

/* Put back a node to the free list. Remove the memory allocation only if 
   the size of free list reached the maximum */
void FreeNode(FreeList *frlist, node *nd, int *errp)
{

  *errp = 0;
  
  if (frlist->num_freelist >= frlist->freelist_limit) {
    free (nd);
    frlist->num_alloc--;
  } else {
    nd->next =  frlist->head;
    frlist->head = nd;
    frlist->num_freelist++;
  }

  return;
}


/* reverse linked list. If reversing a segment of the list, this
   function will detach the segment from the original list.
   If *tail == NULL, reverse everything after *head */
int ReverseList(node **head, node **tail, int *errp)
{
  node* new_tail = NULL;
  node *prevnode, *curnode, *nextnode;
  
  *errp = 0;

  /* nothing to do */
  if (*head == NULL || *head == *tail){
    return (0);
  }

  new_tail = *head;
  prevnode = *head;
  curnode = (*head)->next;

  while (curnode != *tail){
    nextnode = curnode->next;
    curnode->next = prevnode;

    prevnode = curnode;
    curnode = nextnode;
  }

  /* last node */
  if (curnode != NULL) {
    *head = curnode;  
    (*head)->next = prevnode;
  }
  else {
    *head = prevnode;
  }

  *tail = new_tail;

  return (0);
}

/* reverse the doubly linked list.
   If *tail == NULL, reverse everything after *head */
int ReverseDoubleList(node **head, node **tail, int *errp)
{
  node* new_tail = NULL;
  node *prevnode, *curnode, *nextnode;
  
  *errp = 0;

  /* nothing to do */
  if (*head == NULL || *head == *tail){
    return (0);
  }

  new_tail = *head;
  prevnode = *head;
  curnode = (*head)->next;

  while (curnode != *tail){
    nextnode = curnode->next;
    curnode->next = prevnode;
    prevnode->prev = curnode;

    prevnode = curnode;
    curnode = nextnode;
  }

  *tail = new_tail;
  if (*tail != NULL) {
    *head = curnode;  
    (*head)->next = prevnode;
    prevnode->prev = *head;
  }
  else {
    *head = prevnode;
  }

  return (0);
}
