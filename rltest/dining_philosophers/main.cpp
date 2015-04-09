// Dining philosophers problem
//
//   compiled with g++ -lpthread
//
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "constants.h"
#include "philosopher.h"


int main() {
  srand(time(NULL));

  pthread_cond_t cond[N];
  pthread_mutex_t mon;
  sem_t var_i;
  bool fork[N];
  for(int i=0; i<N; i++) {
    fork[i] = true;
    pthread_cond_init(&cond[i], NULL);
  }

  pthread_mutex_init(&mon, NULL);
  pthread_cond_init(cond, NULL);
  sem_init(&var_i, 0, 0);

  Philosopher* phis[N];
  for(int i=0; i<N; i++){
    phis[i] = new Philosopher(fork, mon, cond, var_i, i);
    phis[i]->create();
  }

  for(int i=0; i<N; i++){
    phis[i]->join();
    delete phis[i];
  }
  return 0;
}
