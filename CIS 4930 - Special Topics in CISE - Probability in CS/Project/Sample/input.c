/*
 *             Read input file 
 *
 */
#include    <stdio.h>
#include    <sys/types.h>
#include    <string.h>
#include    <math.h>
#include    <stdlib.h>
#include    "sim.h"

// total number of requests to be simulated. This is the total number finished.
int         TotalRequests = 100000;   /* total number of requests to
					   be simulated. This is the
					   total number finished. */
double      TotalTime = 0;            /* total amount of time to be
					   simulated */
double      RequestRate = 1000.0;     /* per second */


// For stability, SystemLoad should be in (0, 1).
double      SystemLoad = 0.8;      

// Each server rate is relative to the FIFO queue transmission rate, with
// the transmission rate normlized to 1
double      ServerRate = 10.0;

// distribution types: 1 - EXPONENTIAL; 2 - PARETO
int         WorkloadDistribution = PARETO;  

double      Pareto_Alpha=2.0;           /* Pareto paramter alpha; must be > 1 */


u_int   Required_Input_Bitmap = 0;      /* bit map vector of the required
					   i nput parameters */
int     Total_Required_Inputs = 6;      /* total number of required inputs */

char    *Required_Inputs[] = {"Total Requests", "Total Time", "Request Rate",
			      "System Load",
			      "Server Rate", "Workload Distribution"};


/*
 *	function definition
 */

static  void    mask_required_inputs(char *s);
static  void    print_unmasked_inputs(void);  


/*
 *      This routine reads the input file
 */
int read_input(char *file )
{
  register FILE       *fd;
  static char         buf[BUFSIZ];
  double              d;
 
  /*  information file open  */
  fd = fopen( file, "r" );
  if( !fd ) {
    panic("read_input() : cannot open input file");
  }
 
  /*  print current parameters in output file */
  printf("---------- Input Information ----------\n");
  while( fgets( buf, BUFSIZ, fd ) != NULL ) {
    /* get the total number of requests to simulate */
    if( !strncmp( buf, "Total Requests", strlen("Total Requests") ) ) {
      sscanf( buf, "Total Requests: %lg", &d );
      TotalRequests = (int) d;
      if( TotalRequests < 0 ) {
        panic("read_input(): how many packets to simulate?");
      }
      printf("        Total Requests: %d\n", TotalRequests);
      mask_required_inputs("Total Requests");
 
      /* get the total amount of time to simulate */
    } else if( !strncmp( buf, "Total Time", strlen("Total Time") ) ) {
      sscanf( buf, "Total Time: %lg", &TotalTime );
      if( TotalTime < 0) {
        panic("read_input(): Total Time?");
      }
      printf("        Total Time: %g\n", TotalTime);                      
      mask_required_inputs("Total Time");

      /* get the request rate */
    } else if( !strncmp( buf, "Request Rate", strlen("Request Rate") ) ) {
      sscanf( buf, "Request Rate: %lg", &RequestRate );
      if( RequestRate < 0) {
        panic("read_input(): Request Rate?");
      }
      printf("        Request Rate: %g\n", RequestRate);                      
      mask_required_inputs("Request Rate");

      /* get system load */
    } else if ( !strncmp( buf, "System Load", strlen("System Load") ) ) {
      sscanf( buf, "System Load: %lg", &SystemLoad );
      if( SystemLoad <= 0) {
        panic("read_input(): System Load?");
      }
      printf("        System Load: %g\n", SystemLoad); 
      mask_required_inputs("System Load");

      /* get the server rate */
    } else if( !strncmp( buf, "Server Rate", strlen("Server Rate") ) ) {
      sscanf( buf, "Server Rate: %lg", &ServerRate );
      if( ServerRate < 0) {
        panic("read_input(): Server Rate?");
      }
      printf("        Server Rate: %g\n", ServerRate);                      
      mask_required_inputs("Server Rate");

      /* get workload distribution type */
    } else if ( !strncmp( buf, "Workload Distribution", strlen("Workload Distribution") ) ) {
      sscanf( buf, "Workload Distribution: %d", &WorkloadDistribution);
      if( WorkloadDistribution != EXPONENTIAL && WorkloadDistribution != PARETO) {
        panic("read_input(): Workload Distribution not supported?");
      }
      printf("        Workload Distribution: %d\n", WorkloadDistribution); 
      mask_required_inputs("Workload Distribution");

      /* get Pareto parameter alpha */
    } else if ( !strncmp( buf, "Pareto Alpha", strlen("Pareto Alpha") ) ) {
      sscanf( buf, "Pareto Alpha: %lg", &Pareto_Alpha);
      if( Pareto_Alpha <= 1) {
        panic("read_input(): Pareto Alpha needs to be greater than 1.");
      }
 
      /* comment line */
    } else if( !strncmp( buf, "#", strlen("#") ) ) {
      
      /* empty line */
    } else if( !strncmp( buf, "+", strlen("+") ) ) {
      
    } else { /* something unespected */
      fprintf(stderr, "Warning: unknown parameter : %s\n", buf);
    }
  }
  
  fclose( fd );
  
  /* print out required parameters that have not been given by
     the input file */
  print_unmasked_inputs();
 
  return (0);
}


/*
 *      mask the bit in the bit map vector Required_Inputs_Bitmap
 *      whose position is the same as s in the array Required_Inputs
 */
static void mask_required_inputs( char *s)
{
  register  int    i, j;
 
  for(i = 0; i < Total_Required_Inputs; i++){
    if(!strncmp(Required_Inputs[i], s, strlen(s))){
      j = 1 << i;
      Required_Input_Bitmap = Required_Input_Bitmap | j;
    }
  }
}

 
/*
 *      print required input parmaters that have not been provided
 */
static void print_unmasked_inputs()
{
  register  int     i;
  register  u_int   bit;
 
  for(i = 0; i < Total_Required_Inputs; i++){
    bit = (Required_Input_Bitmap >> i) & 1;
    if(bit == 0){
      fprintf(stderr, "Warning: %s is not provided.\n", Required_Inputs[i]);
    }
  }
}
