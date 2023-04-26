#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 5

pthread_mutex_t g_forks[NUM_FORKS];
pthread_mutex_t g_table_lock;

/// @brief Thread is imitation of philosopher appear 
/// @param arg Identifier like philosopher name
/// @return
void * philosopher (void *arg)
{
  int id = *(int *)arg;
  int left_fork = id;
  int right_fork = (id + 1) % NUM_FORKS;

  while (1)
    {
      sleep (rand () % 16 + 5);
      printf ("Philosopher on chair %d\n", id);

      pthread_mutex_lock (&g_table_lock);
      pthread_mutex_lock (&g_forks[left_fork]);
      pthread_mutex_lock (&g_forks[right_fork]);
      pthread_mutex_unlock (&g_table_lock);

      printf ("Philosopher on chair %d is eating by fork %d-%d\n", id,
              left_fork, right_fork);
      sleep (10);

      pthread_mutex_unlock (&g_forks[right_fork]);
      pthread_mutex_unlock (&g_forks[left_fork]);

      printf ("Philosopher on chair %d finish eating by fork %d-%d\n", id,
              left_fork, right_fork);
    }

  return NULL;
}

int main (int argc, char *argv[])
{
  srand (time (NULL));

  pthread_t philosophers[NUM_PHILOSOPHERS];
  int ids[NUM_PHILOSOPHERS];

  for (int i = 0; i < NUM_FORKS; i++)
    {
      pthread_mutex_init (&g_forks[i], NULL);
    }
  pthread_mutex_init (&g_table_lock, NULL);

  for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
      ids[i] = i;
      pthread_create (&philosophers[i], NULL, philosopher, &ids[i]);
    }

  for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
      pthread_join (philosophers[i], NULL);
    }

  return 0;
}
