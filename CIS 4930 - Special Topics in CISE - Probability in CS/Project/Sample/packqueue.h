#ifndef _PACKQUEUE_H_
#define _PACKQUEUE_H_

void packqueue_init(PacketQueue *pq);

int enqueue_packet(Packet* pack, PacketQueue *pq);

int dequeue_packet(Packet* pack, PacketQueue *pq);

#endif
