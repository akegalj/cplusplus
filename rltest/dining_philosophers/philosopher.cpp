#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include "constants.h"
#include "philosopher.h"

Philosopher::Philosopher(bool* fork, pthread_mutex_t& mon, pthread_cond_t* cond, sem_t& var_i, int id) : fork(fork), mon(mon), cond(cond), var_i(var_i), id(id) {}

void Philosopher::create(){
  pthread_create(&thr_id, NULL, start, this);
}

void Philosopher::join(){
  pthread_join(thr_id, NULL);
  sem_wait(&var_i);
}

// Each philosopher is thinking and eating
void* Philosopher::start(void* i){
  Philosopher* p = (Philosopher*)i;
  sem_post(&p->var_i);
  while(1){
    p->think();
    p->eat();
  }
}


// Thinking
void Philosopher::think(){
  pthread_mutex_lock(&mon);
  std::cout << "Philosopher " << id << " is thinking" << std::endl;
  pthread_mutex_unlock(&mon);
  srand(time(NULL));
  sleep(rand()%3 + 1);
}

// Eating
void Philosopher::eat(){
  take_fork();
  sleep(2); // eating
  put_fork();
}

// Taking fork. If eather left or right fork is taken, wait.
void Philosopher::take_fork(){
  pthread_mutex_lock(&mon);
  std::cout << "Philosopher " << id << " is waiting on forks" << std::endl;
  while(!fork[id] || !fork[(id + 1)%N])
    pthread_cond_wait(cond + id, &mon);
  fork[id] = fork[(id + 1)%N] = false;
  std::cout << "Philosopher " << id << " is eating" << std::endl;
  pthread_mutex_unlock(&mon);
}

// Put forks down and tell philosophers left and right to check it.
void Philosopher::put_fork(){
  pthread_mutex_lock(&mon);
  fork[id] = fork[(id + 1)%N] = true;
  pthread_cond_signal(cond + (id-1)%N);
  pthread_cond_signal(cond + (id+1)%N);
  std::cout << "Philosopher " << id << " put forks down" << std::endl;
  pthread_mutex_unlock(&mon);
}
