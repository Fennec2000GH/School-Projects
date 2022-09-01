/*
 *           Memory allocation and management for packet data structure
 *
 */
#include        <stdio.h>
#include        "sim.h"
#include        "freelist.h"
#include        "packet.h"

/*
 *      global variables definition
 */
FreeList      	PacketArea;	/* Packet free list */

/*
 *      initialization; chunk is the maximum number of packets in the
 *      packet free list
 */
void packet_init(int chunk)
{
  InitFreeList(& PacketArea, chunk);
  return;
}                              


/*
 *      get a free Packet
 */
Packet *get_packet()
{
  Packet *p;
  int    err = 0;
 
  p = (Packet *) GetNode(&PacketArea, sizeof(Packet), &err);
  return p;      
}


/*
 *      return a packet to the free list
 */
void free_packet(Packet *p)
{

  int err = 0;
 
  p->next = p->prev = NULL;
  FreeNode(&PacketArea, (node *) p, &err);
  return;
}
