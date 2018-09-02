#include <ucontext.h>

typedef struct TCB_t *TCBPtr;
typedef struct TCB_t TCB_t;

struct TCB_t{
    int threadId;
    ucontext_t context;
    TCBPtr *next;
    TCBPtr *prev;
};

// arguments to init_TCB are
//1. pointer to the function, to be executed
//2. pointer to the thread stack
//3. size of the stack
void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
//	printf("\nIn TCB");
    memset(tcb,'\0',sizeof(TCB_t));  // wash, rinse
	//tcb= malloc(sizeof(TCB_t));
    stack_size*=sizeof(TCB_t);
    getcontext(&tcb->context);  // have to get parent context, else snow forms on hell
    tcb->context.uc_stack.ss_sp = malloc(8192);
    tcb->context.uc_stack.ss_size = 8192;
    makecontext(&tcb->context,function,0);// context is now cooked
}
