/*
 *
 *      Memory allocation and management for event data structure
 *      Event priority queue interface
 */
#include        <stdio.h>
#include        "sim.h"
#include        "splay.h"
#include        "freelist.h"
#include        "event.h"

static void event_queue_reset(Event **tr_ptr);

/*
 *      global variables definition
 */
FreeList      	EventArea;	/* Even free list */


/*
 *      initialize event priority queue
 */
void event_pq_init(Event *ev_pq)
{

  /* initialize event priority queue */
  event_queue_reset(&ev_pq);

  return;
}


/*
 *      initialization; chunk is the maximum number of events in the
 *      event free list
 */
void event_freelist_init(int chunk)
{

  // initialize event free list
  InitFreeList(& EventArea, chunk);

  return;
}


/*
 *	Reset event priority queue
 */
static void event_queue_reset(Event **tr_ptr)
{
    SInit((SplayTree *) tr_ptr);

    return;
}


/*
 *      enqueue one event in the right place in the splay tree priority queue
 *	The event must exist.
 */
void event_enqueue(event, tr_ptr)
register Event       	*event;
Event **tr_ptr;    /* pointer to event tree */
{
  SInsert((SplayNode *)event, (SplayTree *) tr_ptr);
  return;
}

/*
 *      dequeue an event at the top of the priority queue 
 */
Event *event_dequeue(Event **tr_ptr)
{
  Event    	*event;

  /* take an event off the tree */
  SDelete((SplayNode **) &event, (SplayTree *) tr_ptr);
  
  return(event);
}

/*
 *      get a free event
 */
Event *get_event()
{
  Event *ev;
  int   err = 0;

  ev = (Event *) GetNode(&EventArea, sizeof(Event), &err);
  return ev;
}

/*
 *      return an event to the freelist
 */
void free_event(Event *ev)
{
  int err = 0;

  ev->packet = NULL;
  ev->next = ev->left = ev->right = ev->parent = NULL;
  FreeNode(&EventArea, (node *) ev, &err);
  return;
}

