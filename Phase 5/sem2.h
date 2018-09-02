#include "threads.h"
typedef struct Semaphore_t *semaphore_t;
struct Semaphore_t{
	int count;
	TCB_t tcbHead;
};
semaphore_t CreateSem(int InputValue){
	//printf("\nSemCreation");
	semaphore_t sem=(semaphore_t)malloc(1 * sizeof(semaphore_t));
	//printf("\nIn create Sem\tcount:%d\n",sem->count);
	sem->count=InputValue;
	//printf("\nIn create Sem\tcount:%d\n",sem->count);
	sem->tcbHead=newQueue();
	return sem;
}

void P(semaphore_t sem){
	//printf("\nIn P\tcount:%d\n",sem->count);
	sem->count--;
	//printf("\nIn P\tcount:%d\n",sem->count);
	if(sem->count<0){
		AddItem(Curr_Thread, sem->tcbHead);
		TCB_t Prev_Thread;
   		Prev_Thread = Curr_Thread;
   		Curr_Thread = DelQueue(ReadyQ);
   		swapcontext(&(Prev_Thread->context),&(Curr_Thread->context));
	}
}

void V(semaphore_t sem){
	//printf("\nIn V\tcount:%d",sem->count);
	sem->count++;
	if(sem->count<=0){
		TCB_t Prev_Thread;
   		Prev_Thread =DelQueue(sem->tcbHead);
		AddItem(Prev_Thread , ReadyQ);
		
	}
	yield();
	//printf("\nOutside V");
}
