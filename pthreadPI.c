//Name: Jonathan Allen
//Predicting PI using pthreads

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>

//Define max threads
#define NUM_THREADS 200
#define N 10

//Define Global Vars
int amount;

//Define thread run code
void *calcPI(void *id) {
  int i;
  double x,y;

  for (i = 0; i < N; i++) {
    // generate a random number between -1.0 and +1.0
    x = random()/ ((double)RAND_MAX + 1) * 2.0 - 1.0;
    y = random()/ ((double)RAND_MAX + 1) * 2.0 - 1.0;
  }
  
  printf("X: %lf, Y: %lf\n", x, y);
  
  //if in circle...
  if ( sqrt((x*x) + (y*y)) < 1.0 ){
    amount++;
  }

  pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
  amount = 0; //Set global to 0 in circle
  srand((unsigned)time(NULL));
  
  int rc;
  long i;

  pthread_t threads[NUM_THREADS];

  //create threads
  for(i=0; i < NUM_THREADS; i++){
    
    rc = pthread_create(&threads[i], NULL, calcPI, (void *)i);
    
    if(rc){
      printf("RC from pthread_create() is %d\n", rc);
      exit(-1);
    }    
  }

  //join threads
  for(i=0; i < NUM_THREADS; i++){
    rc = pthread_join(threads[i], NULL);

    if(rc){
      printf("RC from pthread_join() is %d\n", rc);
      exit(-1);
    }
  }

  //print results
  float picalc = (float)4.0*((float)amount/(float)NUM_THREADS);

  printf("\nNumber of threads: %d", NUM_THREADS );
  printf("\nNumber in circle: %d", amount );
  printf("\nNumber out of circle: %d", (NUM_THREADS-amount) );
  printf("\nPI Calc: %lf\n", picalc);


  return 0;
}
