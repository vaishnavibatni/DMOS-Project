#include<stdio.h>
#include "q.h"

QItem ReadyQ;
QItem Curr_Thread;
int count;

void initReadyQ(){
	ReadyQ=newQueue();
	count=0;
}


void start_thread(void (*function)(void)){
	printf("\nIn start_thread");
	Curr_Thread=NewItem();
	int *stack;
	TCBPtr tcb;
	tcb=malloc(sizeof(TCB_t));
	tcb->threadId=++count;
	printThread_Id(tcb);
	init_TCB(tcb, function, stack, 8192);
	Curr_Thread->load=tcb;
	AddQueue(ReadyQ,Curr_Thread);
}

void run()
{   // real code
    Curr_Thread = DelQueue(ReadyQ);
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(Curr_Thread->load->context));  // start the first thread
}
 

void yield() // similar to run
{  
	QItem Prev_Thread;
	AddQueue(ReadyQ, Curr_Thread); 
	Prev_Thread = Curr_Thread;
	Curr_Thread = DelQueue(ReadyQ);
	swapcontext(&(Prev_Thread->load->context),&(Curr_Thread->load->context));
   //swap the context, from Prev_Thread to the thread pointed to Curr_Thread
}

// Prints thread Id. Takes 1 argument - TCB node
void printThread_Id(TCB_t *tcb){
	printf("\nThread:: %d\n", tcb->threadId);
}
