#include "threads.h"

typedef struct semaphore_t{
    int count;
    TCB_t *Q;
} semaphore_t;

semaphore_t *CreateSem( int count ){
    semaphore_t *sem = ( semaphore_t * )malloc( sizeof( semaphore_t ) );
    if( sem == NULL )
        exit (0);
    sem->count  = count ;
    sem->Q = NULL;
    return sem;
}
void P( semaphore_t *sem ){
    TCB_t *wait_thread = NULL;
    TCB_t *temp = NULL;
    sem->count -= 1;
    //block thread
    if(sem->count < 0){
        wait_thread = delete_node(&ready_q);
        insert_node(&sem->Q, current_thread);
        temp = current_thread;
        current_thread = wait_thread;
        swapcontext(&(temp->context), &(wait_thread->context));
    }
}
void V( semaphore_t *sem ){
    TCB_t *current;
    sem->count += 1;
    //switch with waiting threads
    if(sem->count <= 0){
        current = delete_node( &( sem->Q ) );
        insert_node( &ready_q, current );
    }
    yield();
}


