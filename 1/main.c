#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADS_COUNT 5
#define COMMON_RESOURCES 5

#define RANDOM_RANGE_MINIMUM 5
#define RANDOM_RANGE_MAXIMUM 20

pthread_mutex_t g_forks[COMMON_RESOURCES];
pthread_mutex_t g_table_lock;

/// @brief Thread is imitation of philosopher appear 
/// @param arg Identifier like philosopher name
/// @return
void* philosopher(void* arg)
{
  int id = *(int*)arg;
  int left_fork = id;
  int right_fork = (id + 1) % COMMON_RESOURCES;
  const int rand_delimiter = (RANDOM_RANGE_MAXIMUM - RANDOM_RANGE_MINIMUM + 1)
                           + RANDOM_RANGE_MINIMUM;

  while (1)
  {
    sleep(rand() % rand_delimiter);
    printf("Philosopher on chair %d\n", id);

    pthread_mutex_lock(&g_table_lock);
    pthread_mutex_lock(&g_forks[left_fork]);
    pthread_mutex_lock(&g_forks[right_fork]);
    pthread_mutex_unlock(&g_table_lock);

    printf("Philosopher on chair %d is eating by fork %d-%d\n", id,
            left_fork, right_fork);
    sleep(10);

    pthread_mutex_unlock(&g_forks[right_fork]);
    pthread_mutex_unlock(&g_forks[left_fork]);

    printf("Philosopher on chair %d finish eating by fork %d-%d\n", id,
            left_fork, right_fork);
  }

  return NULL;
}

int main(int argc, char *argv[])
{
  srand(time (NULL));

  pthread_t philosophers[THREADS_COUNT];
  int ids[THREADS_COUNT];

  for (int i = 0; i < COMMON_RESOURCES; i++)
  {
    pthread_mutex_init(&g_forks[i], NULL);
  }
  pthread_mutex_init(&g_table_lock, NULL);

  for (int i = 0; i < THREADS_COUNT; i++)
  {
    ids[i] = i;
    pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
  }

  for (int i = 0; i < THREADS_COUNT; i++)
  {
    pthread_join(philosophers[i], NULL);
  }

  return 0;
}
