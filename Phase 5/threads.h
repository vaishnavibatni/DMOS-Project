// (c) Partha Dasgupta 2009
// permission to use and distribute granted.

#include <pthread.h>
#include "q.h"
int count=0;
TCB_t ReadyQ, Curr_Thread;
void initReadyQ(){
	ReadyQ=newQueue();
}
/*pthread_t start_thread(void *func, int *arg)
  {
   pthread_t thread_id;
   int rc;
      printf("In main: creating thread\n");
      rc = pthread_create(&thread_id, NULL, func, arg);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
        }
    return(thread_id);
   }
*/

void start_thread(void (*function)(void))
{ // begin pseudo code
	printf("\nIn ST");
	int *stackP= (int *) malloc(8192* sizeof(int));
    // allocate a stack (via malloc) of a certain size (choose 8192)
	TCB_t tcb= (TCB_t) malloc(sizeof(struct TCB_T));
     //allocate a TCB (via malloc)
	init_TCB (tcb, function, stackP, 8192);
     //call init_TCB with appropriate arguments
	tcb->threadId=++count;
     //Add a thread_id (use a counter)
	AddItem(tcb, ReadyQ);
     //call addQ to add this TCB into the “ReadyQ” which is a global header pointer

  //end pseudo code
}

void run()

{   // real code

    Curr_Thread = DelQueue(ReadyQ);

    ucontext_t parent;     // get a place to store the main context, for faking

    getcontext(&parent);   // magic sauce
    
    swapcontext(&parent, &(Curr_Thread->context));  // start the first thread
    
}

 

void yield() // similar to run
{  TCB_t Prev_Thread;
   Prev_Thread = Curr_Thread;
   AddItem(Curr_Thread, ReadyQ);

   Curr_Thread = DelQueue(ReadyQ);
   swapcontext(&(Prev_Thread->context),&(Curr_Thread->context));
}
