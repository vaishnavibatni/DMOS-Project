//Vaishnavi Batni - 1213222502
//Krithika Narayanan - 1213134817
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "msgs.h"

void server0(){

    while(1){
        printf("\t\t\t\t\tServer-0 trying to recieve on port 0\n");
        msgPortPair m=receive(0);
        printf("\t\t\t\t\tServer-0's message recieved on port 0\n");
        printf("\t\t\t\t\tServer-0 sending message on port %d\n", m.client);
        send(m.client,m);
        printf("\t\t\t\t\tServer-0's message sent on port %d\n", m.client);
    }
}

/*void server1(){

    while(1){
        printf("Server-1 trying to recieve on port 1\n");
        msgPortPair m=receive(1);
        printf("Server-1's message recieved on port 1\n");
        printf("\t\t\tServer-1 sending message on port %d\n", m.client);
        send(m.client,m);
        printf("\t\t\tServer-1's message sent on port %d\n", m.client);
    }
}*/

int clientNo=0;
int clientPort=1;

void client(){
    int client=++clientNo;
    int clientPort=++clientPort;
    while(1){
        msgPortPair *m=malloc(sizeof(msgPortPair));
        m->client= clientPort;
        int i;
        for(i = 0; i< 10; i++)
        {
            m->content[i] = i;
        }
        printf("Client-%d trying to send on port 0\n",client);
        send(0, *m);
        printf("Client-%d's message sent on port 0\n",client);
        printf("Client-%d receiving from port %d\n",client,clientPort);
        msgPortPair m2=receive(clientPort);
        printf("Client-%d's message recieved on port %d\n",client,clientPort);
        sleep(1);
    }

}

int main(){
    createPorts();

    start_thread(&client);   //client 0
    start_thread(&client);   //client 1
    start_thread(&client);   //client 2
    start_thread(&client);   //client 3
    start_thread(&client);   //client 4


    start_thread(&server0);   //server 0
    //start_thread(&server1);   //server 1

    run();
    while(1)  sleep(1);
    return 0;
}