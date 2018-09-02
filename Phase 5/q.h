#include<stdio.h>
#include <stdlib.h>
#include "TCB.h"
//typedef struct QItem *qItem;
//struct QItem{
 //   struct QItem *prev, *next;
//    int value;
//};

TCB_t NewItem(){
    TCB_t qElement;
    qElement= (TCB_t)malloc(sizeof(TCB_t));
    qElement->next=(TCB_t)malloc(sizeof(TCB_t));
    qElement->prev=(TCB_t)malloc(sizeof(TCB_t));
    qElement->threadId=0;
    return qElement;
}

TCB_t newQueue(){
    TCB_t head=NewItem();
    head->threadId= 0;
    head->prev=head;
    head->next=head;
    return head;
}

void AddItem(TCB_t item, TCB_t head){
    TCB_t temp=head->prev;
   // TCB_t item= NewItem();
   // item->threadId= element;
    head->prev=item;
    item->next=head;
    temp->next=item;
    item->prev=temp;
}

TCB_t DelQueue(TCB_t head){
    TCB_t prevElement= head->prev;
    TCB_t nextElement= head->next;
    if(prevElement==head && nextElement==head){
        return NULL;
     }
    TCB_t nextNextElement= nextElement->next;
    nextNextElement->prev=head;
    head->next=nextNextElement;
    return nextElement;
}
void FreeItem(TCB_t item){
    free(item);
}
