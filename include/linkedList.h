#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "include/symbolTable.h"

typedef struct LinkedList {
    symbolTable *symbt;
    struct LinkedList *outerScope;
} linkedList;


linkedList *initList(symbolTable *globalScope);
linkedList *insertAtHead(linkedList *list, symbolTable *scope);
linkedList *removeAtHead(linkedList *list);

void printList(linkedList *list);

#endif