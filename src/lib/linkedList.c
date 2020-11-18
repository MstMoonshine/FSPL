#include "include/linkedList.h"
#include <stdlib.h>
#include <stdio.h>

linkedList *initList(symbolTable *globalScope) {
    linkedList *newList = malloc(sizeof(linkedList));

    newList->symbt = globalScope;
    newList->outerScope = NULL;

    return newList;
}

entryValue *lookupList(linkedList *list, const char *key) {
    if (!list) return NULL;

    linkedList *cur;
    for (cur = list; cur; cur = cur->outerScope) {
        entryValue *res = lookup(cur->symbt, key);

        if (res) return res;
    }

    return NULL;
}

entryValue *lookupLocalList(linkedList *list, const char *key) {
    if (!list) return NULL;
    return lookup(list->symbt, key);
}

linkedList *insertAtHead(linkedList *list, symbolTable *scope) {
    linkedList *newHead = malloc(sizeof(linkedList));

    newHead->symbt = scope;
    newHead->outerScope = list;

    return newHead;
}

linkedList *removeAtHead(linkedList *list) {
    if (!list) return NULL;

    linkedList *ret = list->outerScope;
    free(list);
    return ret;
}



void printList(linkedList *list) {
    if (!list) return;

    int i = 0;
    for (linkedList *cur = list; cur; cur = cur->outerScope) {
        printf("*********\n");
        printf("Scope %d:\n", i++);
        printTable(cur->symbt, 0);
        printf("\n");
    }
    return;
}