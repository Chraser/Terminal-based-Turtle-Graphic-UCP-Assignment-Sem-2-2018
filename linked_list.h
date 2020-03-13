/*Forward declarations only. Comments for each individual function is at the definition of function*/
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
/*
Purpose: To hold the reference to the next node of the current node and 
         the data of the current node
*/
typedef struct LinkedListNode{
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

/*
Purpose: To hold reference to the starting node of a linked list and the
         number of nodes in the linked list
*/
typedef struct LinkedList{
    LinkedListNode* head;
    int count;
} LinkedList;

LinkedList* createLinkedList(void);
void insertLast(LinkedList* list, void* data);
void* removeFirst(LinkedList* list);
#endif