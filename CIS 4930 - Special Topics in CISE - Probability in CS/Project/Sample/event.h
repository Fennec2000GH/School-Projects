#ifndef _EVENT_H_
#define _EVENT_H_

extern void event_freelist_init(int chunk);

extern void event_pq_init(Event *ev_pq);

extern void event_enqueue(register Event *event, Event **tr_ptr);

extern Event *event_dequeue(Event **tr_ptr);

extern Event *get_event(void);

extern void free_event(Event *ev);

#endif
