/*
 *          main.c
 *
 */
#include        <stdio.h>
#include        <time.h>
#include        <sys/types.h>
#include        <string.h>
#include        <math.h>
#include        <stdlib.h>
#include        <gsl/gsl_rng.h>
#include        <gsl/gsl_randist.h>
#include        "sim.h"
#include        "input.h"
#include        "event.h"
#include        "packet.h"
#include        "packqueue.h"


u_int          RandomSeed = 0;   // random seed number
gsl_rng        *RandGen;      // global random number generator

int            NumRequests;   // num. of requests seen so far
int            NumFinished;   // num. of requests finished so far
int            NumInService;  // number of requests being serviced at the moment

// the following are used to compute the mean
Cumulative     C_NumInService;         // cumulative number in service
Cumulative     C_NumQueued;            // cumulative number in the queue

Cumulative     C_QueueingDelay;        // cumulative queueing in the queue
Cumulative     C_ResponseTime;         // cumulative reponse time

Event          *EventPQ;               // event priority queue
PacketQueue    PackQueue;              // FIFO packet queue

double         CurrentTime = 0;        // current time

// mean of the workload is caculated based on the RequestRate and SystemLoad
double         WorkloadMean;

// minimum of a Pareto random variable representing the workload size; 
// it is computed based on the input parameter Pareto_Alpha and WorkloadMean
double         Pareto_K;                

static	void	main_startup(char *info_file);
static	int	main_ending(void);
static	int	main_time(char *s);
static  int     random_init(void);
static  int     main_loop(void);
static  int     init_all(void);
static  double  get_workload(void);
static  double  get_request_interarrival_time(void);
static  void    end_of_service_event(Event *ev);
static  void    end_of_transmission_event(Event *ev);
static  void    request_arrival_event(Event *ev);


/*
 *	main routine
 */
int main( int argc, char *argv[] )
{

  if( argc != 3 ) {
    printf( "Usage : %s input_file seed_number\n", argv[0] );
    panic("main() : You'd better learn how to use this program");
  }
  
  sscanf( argv[2], "%u", &RandomSeed );

  main_startup(argv[1] );           // read input and initialize

  main_time( "Simulation Start");   // print time 
  
  main_loop();
   
  main_time( "Simulation End");
  
  main_ending();                    // print collected statistics 
  return (0);                       
}


/*
 *	startup procedure. Initialize different modules and 
 *      data collection variables
 */
static void main_startup( char *info_file )
{
  printf("\nInput file is: %s\n", info_file);  
  read_input(info_file);        // input parameters are read and printed

  // converting input parameters to more convenient variable
  WorkloadMean = SystemLoad / RequestRate;

  init_all();      // initialize everything associated with events and packets
  random_init();   // initialization for random number generation

    /* initialized book-keeping variables */
  NumInService = 0;  
  NumRequests = 0;
  NumFinished = 0;
  
  CurrentTime = 0;

  // initialize data collection
  C_NumInService.cumul = 0.0;
  C_NumInService.num_points = 0.0;
  C_NumQueued.cumul = 0.0;
  C_NumQueued.num_points = 0.0;
  C_ResponseTime.cumul = 0.0;
  C_ResponseTime.num_points = 0.0;
  C_QueueingDelay.cumul = 0.0;
  C_QueueingDelay.num_points = 0.0;

  printf("        Workload Mean: %g\n", WorkloadMean);   
  if (WorkloadDistribution == PARETO){
    printf("        Pareto Alpha: %g\n", Pareto_Alpha); 
    printf("        Pareto K: %g\n", Pareto_K);   
  }
  printf("        Random seed is %u\n", RandomSeed);

  return;
}


/*
 *
 */
static int main_loop()
{
  Event   *ev;
  Packet  *p;

  /* schedule the first event */
  if( (ev = get_event()) == NULL ) 
    panic("main_loop(): out of memory");
  if ( (p = get_packet()) == NULL ) 
    panic("main_loop(): out of memory");

  p->id = NumRequests + 1;
  p->next = p->prev = NULL;
  p->workload = get_workload();
  ev->key = CurrentTime;   // first request at time 0
  ev->pack_id = p->id;
  ev->packet = p;
  ev->func = request_arrival_event;
  event_enqueue(ev, &EventPQ);
  
  /* event loop; exit the loop when both conditions are satisfied */
  while (NumFinished < TotalRequests 
	 || CurrentTime < TotalTime) {

    if ((ev = event_dequeue(&EventPQ)) == NULL)
      panic("main_loop(): event queue empty");
    
    CurrentTime = ev->key;
    
    (*(ev->func))(ev);
  }
  
  return 1;
}
    

/*
 *    A request arrival event at the queue. 
 */
static void request_arrival_event(Event *ev)
{
  Packet *pack, *p;
  Event  *new_ev;

  pack = ev->packet;
  pack->request_time = CurrentTime;

  // update stats
  NumRequests++;
  NumInService++;       // the current request will be serviced
  C_NumInService.cumul += (double) NumInService;
  C_NumInService.num_points += 1.0;

  // send the request immediately to a server

  // create an end_of_service event. We assume an infinite number of servers.
  // The service time is proprotional to the workload or file size.
  // For the first stage, we effectively have an M/G/infinity queue.

  // reuse the event structure
  ev->key = CurrentTime + pack->workload/ServerRate;
  ev->func = end_of_service_event;
  event_enqueue(ev, &EventPQ);


  /* schedule a new request_arrival_event */
  if( (new_ev = get_event()) == NULL ) 
    panic("request_arrival_event(): out of memory");
  if ((p = get_packet()) == NULL ) 
    panic("request_arrival_event(): out of memory");

   p->id = NumRequests + 1;
   p->next = p->prev = NULL;
   p->workload = get_workload();
   // next request time
   double d = CurrentTime + get_request_interarrival_time(); 
   
   new_ev->pack_id = p->id;
   new_ev->packet = p;
   new_ev->func = request_arrival_event;

   new_ev->key = d;  
   event_enqueue(new_ev, &EventPQ);
  
   return;
}


/*
 *    end_of_service event: end of service by a server. Send the packet to
 *    the FIFO packet queue
 */
static void end_of_service_event(Event *ev)
{
  Packet *pack;
  int    ret;

  // collect data
  NumInService--;            // request is leaving the server
  
  // cumulating queue size seen by an arrival to the queue
  C_NumQueued.cumul += PackQueue.total_items; 
  C_NumQueued.num_points += 1.0;

  pack = ev->packet;
  pack->arr_time_to_queue = CurrentTime;
  
  ret = enqueue_packet(pack, &PackQueue);    // enqueue pack at the PackQueue
  if (ret == 0)
    panic("end_of_service_event(): packet should not be rejected.");

  // if pack is the only packet in the queue, schedule 
  // an end_of_transmission_event
  if (PackQueue.total_items == 1){
    // re-use ev
    ev->key = CurrentTime + pack->workload;
    ev->func = end_of_transmission_event;
    event_enqueue(ev, &EventPQ);
  }
  else{
    free_event(ev);
  }

  return;
}


/*
 *    end_of_transmission event: schedule the next end_of_transmission_event 
 *    if the queue is not empty
 */
static void end_of_transmission_event(Event *ev)
{
  double d;
  Packet *pack;

  pack = ev->packet;
  
  // dequeue pack
  dequeue_packet(pack, &PackQueue);

  // collect data   
  NumFinished++;
  d = CurrentTime - pack->request_time;
  C_ResponseTime.cumul += d;
  C_ResponseTime.num_points += 1.0;

  d = CurrentTime - pack->arr_time_to_queue;
  C_QueueingDelay.cumul += d;
  C_QueueingDelay.num_points += 1.0;

  free_packet(pack);

  if (PackQueue.total_items == 0){
    free_event(ev);
  }
  else{
    /* If the queue is not empty, schedule an end_of_transmission_event
       for the next packet. Re-use ev. */
    pack = PackQueue.head;
    ev->packet = pack;
    ev->pack_id = pack->id;
    ev->func = end_of_transmission_event;
    ev->key = CurrentTime + pack->workload;
    event_enqueue(ev, &EventPQ);
  }
  return;

}
	

// The requests follow a Poisson process.
// Return a sample of interarrival time for requests.
static double get_request_interarrival_time() {

  double d = gsl_ran_exponential (RandGen, 1.0/RequestRate);
  
  return d;

}


// Return a sample of the workload for a request.
// The workload is measured in seconds.
static double get_workload() {
  double d;

  switch (WorkloadDistribution) {
  case EXPONENTIAL:
    d = gsl_ran_exponential (RandGen, WorkloadMean);
    break;
  case PARETO:
    d = gsl_ran_pareto (RandGen, Pareto_Alpha, Pareto_K);

    break;
  }

  return d;

}


/*
 *	statistics printout.
 */
static int main_ending()
{
  double mean = 0;       
  
  printf("\n****************** Simulation Statistics *******************\n");

  printf("Total number of requests finished: %d\n", NumFinished);
  printf("Total simulated time: %g\n", CurrentTime);

  if (C_NumInService.num_points) {
    mean = C_NumInService.cumul / C_NumInService.num_points; 
    printf("Average number of requests in service: %g\n", mean);
  }

  if (C_NumQueued.num_points) {
    mean = C_NumQueued.cumul / C_NumQueued.num_points; 
    printf("Average number of requests in queue: %g\n", mean);
  }
   
  if (C_QueueingDelay.num_points) {
    mean = C_QueueingDelay.cumul / C_QueueingDelay.num_points; 
    printf("Average queueing delay: %1.10e\n", mean);
  }

  if (C_ResponseTime.num_points) {
    mean = C_ResponseTime.cumul / C_ResponseTime.num_points; 
    printf("Average response time: %1.10e\n", mean);
  }

  return (0);
}


/*
 *	print current time information
 */
static int main_time(char *msg )
{
    time_t	tloc;

    /* get current time and print it */
    time( &tloc );
    printf("%s : %s", msg, ctime( &tloc ));
    fflush( stdout );
    fflush( stderr );

    return (0);
}


/*
 *	panic routine
 */
void panic( char *s )
{
    printf("****** Simulator Panic ****** \n");
    printf("   Message : %s\n", s);
    exit(1);
}


/*
 *      Initialization of event freelist, event priority queue, 
 *      packet freelist and FIFO packet queue
 */
static int init_all()
{

  // initialize a free list of events
  event_freelist_init(EVENT_AREA_SIZE); 

  // initialize Event priority queue
  event_pq_init(EventPQ); 

  // initialize a free list of packets
  packet_init(PACK_AREA_SIZE);
  
  // initialize packet queue
  packqueue_init(&PackQueue);

  return (0);
}


/*
 *      Initializing random number generator and parameters for 
 *      distribution functions
 */
static int random_init()
{

  // intialize the random number generator in the gsl library
  gsl_rng_default_seed = RandomSeed;
  RandGen = gsl_rng_alloc (gsl_rng_default);

  switch (WorkloadDistribution) {
  case PARETO:
    /* Pareto CDF: F(x) = 1-(K/x)^alpha, for x >= K; mean = (alpha * K)/(alpha-1)
       Compute K, which is the minimum value of the Pareto random
       variable. We know alpha and the mean, which is equal to
       WorkloadMean */
    Pareto_K = (Pareto_Alpha-1.0)/Pareto_Alpha * WorkloadMean;
    break;
    
  default:
    break;
  }
  return (0);
}

