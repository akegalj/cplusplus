// Dining philosophers problem
//
//   compiled with g++ -lpthread
//
// Bugs: Deadlock when philosopher 0 is eating, and philosopher 1 (next to him)
//       wants to take forks. Then, philosopher 1 has taken mutex, and wont 
//       give it back untill philosopher 0 puts his forks down. Philosopher 0 
//       can't put his forks down because of taken mutex, so we have a deadlock.
//
//       Problem is Philosopher::take_fork, call for pthread_cond_wait(a,b)
//       isn't releasing mutex b. Can't figure out why :/
//       
#include <iostream>

#include "constants.h"
#include "philosopher.h"


int main() {
  pthread_cond_t cond[N];
  pthread_mutex_t mon;
  sem_t var_i;
  bool fork[N];
  for(int i=0; i<N; i++)
    fork[i] = true;

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
