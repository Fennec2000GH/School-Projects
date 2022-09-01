/*
 *      Implement the FIFO packet queue
 *
 */
#include <stdio.h>
#include <math.h>
#include "sim.h"
#include "packet.h"


/*
 * initialize the FIFO packet queue
 */
void packqueue_init(PacketQueue *pq){
  pq->head = NULL; 
  pq->tail = NULL;
  pq->total_items = 0;
  pq->total_workload = 0.0;
  return;
}


/*
 * Add a newly arrived packet at the end of the packet queue.
 * Return 1.
 */
int enqueue_packet(Packet* pack, PacketQueue *pq){
  Packet *p;

  if (pq->total_items == 0) { /* if there is no packet in the queue */
    pq->head = pack;
    pq->tail = pack;
    pack->next = pack->prev = NULL;
  }
  else {
    /* The queue contains one or more packets */
    p = pq->tail;
    p->next = pack;
    pack->prev = p;
    pack->next = NULL;
    pq->tail = pack;
  }
  
  pq->total_workload += pack->workload;
  pq->total_items++;
  
  return 1;
}


/*
 * Dequeue pack from the head of the queue.
 * Return 1.
 */
int dequeue_packet(Packet* pack, PacketQueue *pq){
  Packet *p;

  if (pack == NULL) {
    panic("dequeue_packet(): nothing to dequeue.");
  }

  if (pq->total_items == 0) { /* if there is no packet in the queue */
    panic("dequeue_packet(): cannot dequeue a packet from empty queue.");
  }

  if (pq->head != pack){
    panic("dequeue_packet(): pack should be at the head.");
  }

  /* The queue contains one packets */
  if (pq->total_items == 1){
    pq->head = pq->tail = NULL;
  }
  else {
    p = pack->next;
    pq->head = p;
    p->prev = NULL;
  }

  pq->total_items--;
  pq->total_workload -= pack->workload;
  pack->prev = pack->next = NULL;
  
  return 1;

}
