// Krithika Narayanan - 1213134817
// Vaishnavi Batni - 1213222502

#include<stdio.h>
#include "threads.h"

int globalCount=1;

//thread 1 runs function 1
void func1(){
	int val=0;
	while(1){
		printf("Global 1=%d\n", globalCount++);
		printf("Local 1=%d\n", val++);
		yield();
		
	}
}

//thread 2 runs function 2
void func2(){
	int val=0;
	while(1){
		printf("Global 2=%d\n", globalCount++);
		printf("Local 2=%d\n", val++);
		yield();
	}
}

//thread 3 runs function 3
void func3(){
	int val=0;
	while(1){
		printf("Global 3=%d\n", globalCount++);
		printf("Local 3=%d\n", val++);
		yield();
	}
}

void main(){
	initReadyQ();
	start_thread(func1);
	start_thread(func2);
	start_thread(func3);
	run();
}
