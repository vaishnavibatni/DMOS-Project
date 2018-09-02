#include <stdlib.h>
#include "TCB.h"

typedef struct qItem *qItemPtr;
typedef qItemPtr QItem;
typedef qItemPtr Q;

struct qItem{
    struct TCB_t * load;
    qItemPtr next;
    qItemPtr prev;
};

QItem newQueue(){
    QItem head;
    head=malloc(sizeof(struct qItem));
    head->next=head;
    head->prev=head;
    return head;    
}

QItem NewItem(){

    QItem node;
    node=malloc(sizeof(struct qItem));
    node->next=NULL;
    node->prev=NULL;
    return node;    
}

int isEmpty(QItem head){
    if(head->next==head && head->prev==head){
        return 1;
    }
    return 0;
}

void AddQueue(QItem head,QItem item){
    if(isEmpty(head)){
        head->next=item;
        head->prev=item;
        item->next=head;
        item->prev=head;
    }
    
    else{
        QItem temp=head->next;
        while(temp->next!=head)
            temp=temp->next;
        temp->next=item;
        item->prev=temp;
        item->next=head;   
    }
}

QItem DelQueue(QItem head){
    
    QItem node=head->next;
    if(node->next==head && head->prev==node){   //queue has only one node
        head->next=head;
        head->prev=head;    
    }
    head->next=head->next->next;
    head->next->next->prev=head;
    return node;
}
