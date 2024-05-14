#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define NUM_THREADS 4
#define NUM_POINTS 1000000

int c_points = 0;
//pthread_mutex_t mutex;
sem_t mutex;

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
  //pthread_mutex_lock(&mutex);
  //c_points += cnt;
  //pthread_mutex_unlock(&mutex);
  sem_wait(&mutex);
  c_points += cnt;
  sem_post(&mutex);
  
  pthread_exit(NULL);
}

int pi_mc()
{
  pthread_t thread_adders[NUM_THREADS];
  //pthread_mutex_init(&s, NULL);
  sem_init(&mutex,0,1);
  
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
  //pthread_mutex_destroy(&mutex);
  sem_destroy(&mutex);
  
  return 0;
}
  
