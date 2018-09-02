#include "q.h"

TCB_t *current_thread;
TCB_t *ready_q;

int threadCounter = 0;
void start_thread(void(*function)(void)) {
    int stackSize  = 8192;
    void *stack    = (void *) malloc(stackSize);
    TCB_t *tcb     = (TCB_t *) malloc(sizeof(TCB_t));
    init_TCB(tcb, function, stack, stackSize);
    tcb->thread_id = threadCounter++;
    insert_node(&ready_q, tcb);
}

void run() {
    current_thread = delete_node( &ready_q );
    ucontext_t parent;
    getcontext(&parent);
    swapcontext(&parent, &(current_thread->context));
}
void yield() {
    TCB_t *Prev_Thread;
    insert_node( &ready_q, current_thread );
    Prev_Thread    = current_thread;
    current_thread = delete_node( &ready_q );
    swapcontext( &(Prev_Thread->context), &(current_thread->context) );
}
