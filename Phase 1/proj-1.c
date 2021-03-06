/*
Authors:
Vaishnavi Batni 
Krithika Narayanan 

** Creates 3 threads and updates corresponding values in an array
*/

#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

// A is the array to update using the 3 children thread
int A[3]={0,0,0};

// semaphores to lock the values
// 2 levels of semaphores are used to prevent race condition
semaphore_t mutex, mutex_main, mutex_function1, mutex_2, mutex_3;
struct arg_struct {
    int count;
    semaphore_t sem1;
    
};

// This function does the increment operation
void increment(int *i, semaphore_t *sem1, semaphore_t *sem2){
	while(1){
		P(sem1);
			P(&mutex);
				*i+=1;
			V(&mutex);
		V(sem2);	

	}
}

// to increament A[0]
void function_1(int *i)
{
	increment (i, &mutex_function1, &mutex_2);
}    

//// to increament A[1]
void function_2(int *i)
{
	increment(i, &mutex_2, &mutex_3);
}    


// to increament A[2]
void function_3(int* i)
{
	increment(i, &mutex_3, &mutex_main);
}    

int main()
{
    //initialise all semaphores
    init_sem(&mutex, 1);
    init_sem(&mutex_function1, 0);
    init_sem(&mutex_2, 0);
    init_sem(&mutex_3, 0);
    init_sem(&mutex_main, 1);
    //create child threads
    start_thread(function_1, &A[0]);
    start_thread(function_2, &A[1]);
    start_thread(function_3, &A[2]);

    // print results of the operations by child thread
    while(1) {
	P(&mutex_main);
		P(&mutex);
			printf("\n\nA[0]=%d\tA[1]=%d\tA[2]=%d\n", A[0], A[1],A[2]);
		V(&mutex);
	V(&mutex_function1);
	}	
    return 0;
}
