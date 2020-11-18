#include "include/scopeStack.h"
#include <stdlib.h>
#include <stdio.h>

scopeStack *initStack(symbolTable *globalScope) {
    scopeStack *newStack = malloc(sizeof(scopeStack));
    linkedList *newList = initList(globalScope);

    newStack->stackTop = newList;

    return newStack;
}

symbolTable *getScope(scopeStack *stack) {
    if (!stack || !stack->stackTop) {
        return NULL;
    }
    return stack->stackTop->symbt;
}

entryValue *lookupGlobal(scopeStack *stack, const char *key) {
    if (!stack) return NULL;
    return lookupList(stack->stackTop, key);
}

entryValue *lookupLocal(scopeStack *stack, const char *key) {
    if (!stack) return NULL;
    return lookupLocalList(stack->stackTop, key);
}

void pushScope(scopeStack *stack, symbolTable *scope) {
    // freopen("log.txt", "a", stdout);
    // printf("Pushed...\n");
    // printf("Before:\n");
    // printList(stack->stackTop);

    //in case NULL reference
    if (!stack) return;

    stack->stackTop = insertAtHead(stack->stackTop, scope);

    // printf("After:\n");
    // printList(stack->stackTop);
    // freopen("/dev/tty", "w", stdout);
}

symbolTable *popScope(scopeStack *stack) {

    // freopen("log.txt", "a", stdout);
    // printf("Popping:************************************\n");
    // printf("Before:\n");
    // printf("---------------------\n");
    // printList(stack->stackTop);
    if (!stack) return NULL;
    symbolTable *ret = getScope(stack);
    // printf("After:\n");
    // printf("---------------------\n");
    stack->stackTop = removeAtHead(stack->stackTop);



    // printList(stack->stackTop);
    // freopen("/dev/tty", "w", stdout);
    return ret;
}


void printStack(scopeStack *stack) {
    if (!stack) return;
    printList(stack->stackTop);
}