#ifndef _SIM_H_
#define _SIM_H_
/*
 *        structures and global variables shared by multiple source files
 *
 */
#include <sys/types.h>

#define    EVENT_AREA_SIZE (20)          /* size of the event free list */
#define    PACK_AREA_SIZE  (20)          /* size of the packet free list */

enum distribution_type {EXPONENTIAL=1, PARETO};

typedef struct Packet {
  struct Packet *next;
  struct Packet *prev;
  int  id;
  double request_time;          /* time of request */
  double arr_time_to_queue;     /* arrival time to the packet queue */
  double workload;              /* request workload */
} Packet;

typedef struct PacketQueue {
  Packet* head;
  Packet* tail;
  int     total_items;
  double  total_workload;
} PacketQueue;      

/*
 *      Event structure definition
 */
typedef struct Event_Struct {
  struct Event_Struct *next;          /* link events into list */
  struct Event_Struct *left;          /* Splay tree internals */
  struct Event_Struct *right;         /* Splay tree internals */
  struct Event_Struct *parent;        /* Splay tree internals */
  double              key;            /* timer value    */
  Packet *packet;                     /* an pointer to the packet 
					 in question */
  int                 pack_id;        /* packet id */
  void                (*func)(struct Event_Struct *);   /* procedure address 
							   for event  */
  int                 flag;           /* other information about the event */
} Event;       
      
// Cumulate a scalar measurement for computing the mean or variance
typedef struct Cumulative_Measurement {
  double  cumul;        // cumulated value
  double  num_points;   // number of data points
} Cumulative;


extern int      TotalRequests;
extern double   TotalTime;             
extern double   RequestRate;
extern double   SystemLoad;      
extern double   ServerRate;
extern int      WorkloadDistribution;  
extern double   Pareto_Alpha;


extern	void	panic(char *s);

#endif
