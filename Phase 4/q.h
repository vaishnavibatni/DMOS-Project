#include <stdio.h>
#include <stdlib.h>
#include "TCB.h"

//Insert into Queue
void insert_node(TCB_t **head, TCB_t *item) {
    if(*head == NULL) {
        *head = item;
        item->next = *head;
        item->prev = *head;
    } else {
        item->next = *head;
        item->prev = (*head)->prev;
        (*head)->prev->next = item;
        (*head)->prev = item;
    }
}

//Delete from Queue
TCB_t* delete_node(TCB_t **head) {
    TCB_t* item = NULL;
    if(*head == NULL) {
        item = NULL;
    } else {
        if((*head)->next == (*head)) {
            item = *head;
            *head = NULL;
        } else {
            item = *head;
            (*head) = (*head)->next;
            (*head)->prev = item->prev;
            item->prev->next = *head;
        }
    }
    return item;
}

