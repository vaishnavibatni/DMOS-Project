// (c) Partha Dasgupta 2009
// permission to use and distribute granted.

#include <stdio.h>
#include <stdlib.h>
#include "msgs.h"

char a[5][14];
semaphore_t sem, sem3;
char  clientName[99][16];
int firstTime[99];
Port serverPort;
int i=0;
void server(){
	printf("\nIn server");
	char  serverName[99][22];
	while(1){
		message rcvMsg= (message) malloc(sizeof(struct Message));
		message sendMsg= (message) malloc(sizeof(struct Message));
		sendMsg->sender=serverPort;
		rcvMsg=receive(serverPort);
		FILE *FP;
		//printf("\nfirstTime[rcvMsg->sender->portNum-1]:%d\t%d",firstTime[rcvMsg->sender->portNum-1],rcvMsg->sender->portNum-1);
		if(firstTime[rcvMsg->sender->portNum-1]==1){
			firstTime[rcvMsg->sender->portNum-1]=0;
			strcpy(serverName[rcvMsg->sender->portNum-1],clientName[rcvMsg->sender->portNum-1]);
			strcat(serverName[rcvMsg->sender->portNum-1], ".server");
			//printf("\n%s", serverName[rcvMsg->sender->portNum-1]);
			sendMsg->message=rcvMsg->sender->portNum-1;
			send(rcvMsg->sender,sendMsg);
			FP=fopen(serverName[rcvMsg->sender->portNum-1],"w");
			fclose(FP);
		}
		else{
			FP=fopen(serverName[rcvMsg->sender->portNum-1],"r+");
			int a=fgetc(FP);
			while(a!=EOF){
				a=fgetc(FP);
			}
			int c=rcvMsg->message;
			//char *m=c;
			fputc(c,FP);
			fclose(FP);
			sendMsg->message=-1;
			send(rcvMsg->sender,sendMsg);
		}
	}
	
}

void client(){
	P(sem3);
	printf("\nIn client");
	P(sem);
	Port clientPort= (Port)malloc(sizeof(struct port));
	clientPort= &Ports[i];
	firstTime[clientPort->portNum-1]=1;
	i++;
	V(sem);
	message sendMsg= (message) malloc(sizeof(struct Message));
	message rcvMsg= (message) malloc(sizeof(struct Message));
	sendMsg->message=clientPort->portNum-1;
	sendMsg->sender= clientPort;
	send(serverPort, sendMsg);
	rcvMsg=receive(clientPort);
	//if(rcvMsg->message==-1){
		FILE *FP;
		FP=fopen(clientName[clientPort->portNum-1], "r");
		int m=fgetc(FP);
		while(m!=EOF){
				sendMsg->message=m;
				send(serverPort, sendMsg);
				rcvMsg=receive(clientPort);
				m=fgetc(FP);
			}
	V(sem3);
	while(1){
		yield();
	}
	//if(ReadyQ->next!=ReadyQ){
	//	printf("\nReadyyy");
	//	sleep(10);
	//	yield();
	//}
	//i=(i+1)%5;
	//}
}
int main(int argc, char * argv[])
{   
  //  strcpy(a[0],argv[1]);
   // strcpy(a[1],argv[2]);
	sem=CreateSem(1);
	sem3= CreateSem(3);
   // strcpy(a[1], "sem.h");
   //strcpy(a[2], "sem.h");
    //strcpy(a[3], "sem.h");
    //strcpy(a[4], "sem.h");
    ReadyQ=newQueue();
    initPorts();
    serverPort=  &Ports[99];
	int j;
	for(j=0;j<argc-2;j++){
		if(strlen(argv[j+2])<=15){
		strcpy(clientName[j],argv[j+2]);
    		start_thread(client);
		}
		else
			{
			printf("\nNot copying %s because the size file name is big", argv[j+2]);
		
	}}
    printf("\nStart thread");
    //i=3;//, &id[0]);
   // start_thread(client);//, &id[1]);
   // start_thread(client_2);
    start_thread(server);
 //   start_thread(client);
    //start_thread(server);
    //start_thread(client);
    //start_thread(server);
    //start_thread(client2);
  //  start_thread(server);
    //start_thread(client_3);
    //start_thread(server);//, &id[1]);
    run();
   /* while (1) { scanf("%d %d", &prod_delay, &cons_delay); 
                printf ("\n\n\t\t\t\tP=%d C=%d\n\n\n", prod_delay, cons_delay);
    };*/
}



