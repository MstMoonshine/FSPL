#include "include/linkedList.h"
#include <stdlib.h>

linkedList *initList(symbolTable *globalScope) {
    linkedList *newList = malloc(sizeof(linkedList));

    newList->symbt = globalScope;
    newList->outerScope = NULL;

    return newList;
}

linkedList *insertAtHead(linkedList *list, symbolTable *scope) {
    linkedList *newHead = malloc(sizeof(linkedList));

    newHead->symbt = scope;
    newHead->outerScope = list;

    return newHead;
}

linkedList *removeAtHead(linkedList *list) {
    linkedList *ret = list->outerScope;
    free(list);
    return ret;
}



void printList(linkedList *list) {
    if (!list) return;

    for (linkedList *cur = list; cur; cur = cur->outerScope)
        printTable(cur->symbt, 0);
    
    return;
}