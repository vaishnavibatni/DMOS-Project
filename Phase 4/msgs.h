#include "sem.h"

#define N 10
#define noOfPorts 10
typedef struct msgPortPair msgPortPair;
typedef struct port Port;

struct msgPortPair{
    int content[10];
    int client;
};

struct port{
    msgPortPair messages[N];
    semaphore_t *empty, *full, *mutex;
    int in;
    int out;
};

Port port[noOfPorts];

void createPorts(){
    int i=0;
    for (i=0;i<noOfPorts;i++){
        port[i].in=0;
        port[i].out=0;
        port[i].mutex=CreateSem(1);
        port[i].empty=CreateSem(N);
        port[i].full=CreateSem(0);
    }
}

Port getPort(int i){
    return port[i];
}

void send(int portNo, msgPortPair mesg){
    Port *temp=&port[portNo];
    P(temp->empty);
    P(temp->mutex);
    temp->messages[temp->in]=mesg;
    temp->in=(temp->in+1)%N;
    V(temp->mutex);
    V(temp->full);
}

msgPortPair receive(int portNo){
    Port *temp=&port[portNo];
    msgPortPair msg;
    P(temp->full);
    P(temp->mutex);
    if(temp->in==temp->out)
        printf("\nThere is no message to receive.");
    else
    {
        msg=temp->messages[temp->out];
        temp->out=(temp->out+1)%N;
    }
    V(temp->mutex);
    V(temp->empty);
    return msg;
}