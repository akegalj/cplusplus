#ifndef PHILOSOPHER_H_GUARD
#define PHILOSOPHER_H_GUARD

#include <pthread.h>
#include <semaphore.h>

class Philosopher {
  public:
    Philosopher(bool* fork, pthread_mutex_t& mon, pthread_cond_t* cond, sem_t& var_i, int args);

    void create();
    void join();
  
  private:
    bool* fork;
    pthread_mutex_t& mon;
    pthread_cond_t* cond;
    pthread_t thr_id;
    sem_t& var_i;
    int id;
    
    static void* start(void*);
    void eat();
    void think();
    void take_fork();
    void put_fork();
};

#endif
