// Contains 4 test cases for q.h


#include <stdio.h>
#include "q.h"

void QPrint(QItem head){
    if(isEmpty(head)){
        printf("\nEmpty Queue");
        return;
    }
    QItem node=head->next;
    while(node->next!=head){
        printf("%d ",node->load);
        node=node->next;
    }
    printf("%d ",node->load); //prints the last node
}

int main(){

    //create 3 queues
    Q q1=newQueue(); // contains the pointer to head of queue
    Q q2=newQueue(); 
    Q q3=newQueue();  
    QItem item;      
    
    //test case 1: push items to q1 (1,2,3)
    // and check whats in q1
    // o/p: 123
    printf("\n Test Case 1:\n");
    item=NewItem();
    item->load=1;
    AddQueue(q1,item);
    item=NewItem();
    item->load=2;
    AddQueue(q1,item);
    item=NewItem();
    item->load=3;
    AddQueue(q1,item);
    QPrint(q1);  
 
    // test case 2: push items to q1 and q2 alternatively and check contents
    // q1= 1235
    // q2= 09
    printf("\n Test Case 2:\n");
    item=NewItem();
    item->load=5;
    AddQueue(q1,item);
    item=NewItem();
    item->load=0;
    AddQueue(q2,item);
    item=NewItem();
    item->load=9;
    AddQueue(q2,item);
    QPrint(q1); 
    printf("\n");
    QPrint(q2);
    
    // Test case 3: delete 1 itemsfrom each q1 and q2 and print contents
    // o/p: q1=2345 q2=9
    printf("\n Test Case 3:\n");
    DelQueue(q1);
    DelQueue(q2);
    QPrint(q1); 
    printf("\n");
    QPrint(q2);
    
    //Test case 4: push null value into q2 and check contents
    // o/p: prints nothing
    printf("\n Test Case 4:\n");
    item=NewItem();
    item->load=NULL;
    AddQueue(q2,item);
    
}
