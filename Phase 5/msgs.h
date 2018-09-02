#include "sem2.h"
typedef struct Message *message;
typedef struct port *Port;
typedef struct Message{
	int message;
	Port sender;
}Message;
struct port{
	Message msgs[10];
	//char * message; 
	//Port portServer;
	semaphore_t empty, full, mutex;
	int msgCount, msgcount;
	int portNum;
};
int portNo=0;

int j;
struct port Ports[100];
/*void initPorts(){
	printf("\n IN init port");
	int i=0;
	while(i<100){
		Ports[i].portNum= ++count;
		Ports[i].msgs= (int *) malloc(10*sizeof(int));
	}
	printf("\n out of init port");
}*/

void initPorts(){
	printf("\n IN init port");
	int i=0;
	for(i=0;i<100;i++){
		//Ports[i].count=0;
		//Ports[i].count1=0;
		Ports[i].empty=CreateSem(10);
		Ports[i].full=CreateSem(0);
		Ports[i].mutex=CreateSem(1);
		Ports[i].msgCount=0;
		//Ports[i].message= (char*) malloc(23*sizeof(char));
		Ports[i].msgcount=0;
		//Ports[i].portServer=(Port)malloc(sizeof(struct port));
		Ports[i].portNum= ++portNo;
		int j;
		for(j=0;j<10;j++){
			//Ports[i].msgs[j].message=(char*) malloc(23*sizeof(char));
			Ports[i].msgs[j].sender=(Port)malloc(sizeof(struct port));
		}
		//printf("\n%d\n",Ports[i].portNum);
	}
}

void send(Port receiverPort, message msg){
	P(receiverPort->empty);
	  P(receiverPort->mutex);
	     printf("\n In send. Receiver port: %d\t msg:%d\t SenderPort: %d", receiverPort->portNum, (msg->message), msg->sender->portNum);
	     receiverPort->msgs[receiverPort->msgCount]=*msg;
	     receiverPort->msgCount=(receiverPort->msgCount+1)%10;
	  V(receiverPort->mutex);
	V(receiverPort->full);
	
}

message receive(Port receiverPort){
	P(receiverPort->full);
	  P(receiverPort->mutex);
	     message mesg=(message) malloc(sizeof(struct Message));
		mesg=&(receiverPort->msgs[receiverPort->msgcount]);
	     receiverPort->msgcount=(receiverPort->msgcount+1)%10;
	     printf("\n In Reveiver. Receiver port: %d\t msg:%d\t SenderPort: %d", receiverPort->portNum, (mesg->message), mesg->sender->portNum);
	  V(receiverPort->mutex);
	V(receiverPort->empty);
	return mesg;
	
}
/*void send(Port receiverPort, char *msg, Port senderPort){
	P(receiverPort->empty);
		P(receiverPort->mutex);
		receiverPort->msgs [receiverPort->msgCount].message= msg;
		receiverPort->msgs [receiverPort->msgCount].sender=senderPort;
		//printf("\nSend Port:%d-----%d\n", receiverPort->msgs [receiverPort->msgcount], receiverPort->msgcount);
		receiverPort->msgCount=(receiverPort->msgCount+1)%10;
		printf("\n In send. Receiver port: %d\t msg:%s\t SenderPort: %d", receiverPort->portNum, msg, senderPort->portNum);
		V(receiverPort->mutex);
	V(receiverPort->full);
}

Message * receive(Port receiverPort){
	//if(receiverPort->empty->count<10){
	P(receiverPort->full);		
		P(receiverPort->mutex);
		Message * mesg=&(receiverPort->msgs [receiverPort->msgcount]);
		//printf("\nReceive Port:%d\n", receiverPort->msgs [receiverPort->msgcount]);
		receiverPort->message=(receiverPort->msgs [receiverPort->msgcount].message);
		receiverPort->portServer=(receiverPort->msgs [receiverPort->msgcount].sender);
		receiverPort->msgcount=(receiverPort->msgcount+1)%10;
		printf("\n In receive. Receiver port: %d\t msg:%s ", receiverPort->portNum, mesg->message);
		V(receiverPort->mutex);
	V(receiverPort->empty);
	return mesg;
}*/
