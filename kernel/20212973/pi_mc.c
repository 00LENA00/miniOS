#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 40
#define NUM_POINTS 1000000

int c_points = 0;
pthread_mutex_t mutex;

void *monte_carlo()
{
  int cnt = 0;
  double x,y;
  unsigned int seed = time(NULL)+pthread_self();
  
  for (int i=0; i < NUM_POINTS/NUM_THREADS; i++) {
    x=((double)rand_r(&seed) / RAND_MAX*2-1);
    y=((double)rand_r(&seed) / RAND_MAX*2-1);
    if (x*x+y*y<=1)
    {
      cnt++;
    }
  }
  pthread_mutex_lock(&mutex);
  c_points += cnt;
  pthread_mutex_unlock(&mutex);
  
  pthread_exit(NULL);
}

int pi_mc()
{
  pthread_t thread_adders[NUM_THREADS];
  pthread_mutex_init(&mutex, NULL);
  
  for (int i=0; i<NUM_THREADS; i++)
  {
    pthread_create(&thread_adders[i], NULL, monte_carlo, NULL);
  }
  for (int i=0; i<NUM_THREADS; i++)
  {
    pthread_join(thread_adders[i], NULL);
  }
  double estimated_pi=4.0 * c_points / NUM_POINTS;
  printf("Estimated value of PI: %f\n", estimated_pi);
  
  c_points=0;
  pthread_mutex_destroy(&mutex);
  
  return 0;
}
  
