
#include "threads.h"

typedef struct semaphore_t {
	int count;
	QItem Q;
	//pthread_mutex_t mutex;
//	pthread_cond_t cond;
} semaphore_t;

semaphore_t * CreateSem(int InputValue)
{   
	//printf("\nSem creation");
    semaphore_t *sem = malloc(sizeof(semaphore_t));
    sem->count = InputValue;
    sem->Q = newQueue();
  //  pthread_mutex_init(&(s->mutex), NULL);
    //pthread_cond_init(&(s->cond), NULL);
    return sem;
}


/*
 * The P routine decrements the semaphore, and if the value is less than
 * zero then blocks the process 
 */
void P(semaphore_t *sem)
{   
  //  lock (&(sem->mutex)); 
	//printf("\nIn P\n");
    sem->count--;
    if (sem->count < 0) {
	ucontext_t cur_thread;
    	getcontext(&cur_thread);
	QItem q= NewItem();
	q->load->context=cur_thread;
	AddQueue(sem->Q, q);
	while(1);
	}
  //  unlock (&(sem->mutex)); 
}

/*
 * The V routine increments the semaphore, and if the value is 0 or
 * negative, wakes up a process and yields
 */

void V(semaphore_t * sem)
{   
   // lock (&(sem->mutex)); 
    sem->count++;
    if (sem->count <= 0) {
	Curr_Thread = DelQueue(sem->Q);
	AddQueue(ReadyQ, Curr_Thread); 
	while(1);
	//pthread_cond_signal(&(sem->cond));
    }
   // unlock (&(sem->mutex));
    yield();
}


