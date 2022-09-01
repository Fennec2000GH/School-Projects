#ifndef _PACKET_H_
#define _PACKET_H_


void packet_init(int chunk);

Packet *get_packet(void);

void free_packet(Packet *p);
#endif



