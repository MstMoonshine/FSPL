#include "include/scopeStack.h"
#include <stdlib.h>
#include <stdio.h>

scopeStack *initStack(symbolTable *globalScope) {
    scopeStack *newStack = malloc(sizeof(scopeStack));
    linkedList *newList = initList(globalScope);

    newStack->stackTop = newList;

    printf("Initialized...\n");
    printList(newStack->stackTop);

    return newStack;
}

void pushScope(scopeStack *stack, symbolTable *scope) {
    stack->stackTop = insertAtHead(stack->stackTop, scope);

    printf("Pushed...\n");
    printList(stack->stackTop);
}

symbolTable *popScope(scopeStack *stack) {
    symbolTable *ret = stack->stackTop->symbt;

    stack->stackTop = removeAtHead(stack->stackTop);

    // freopen("log.txt", "a", stdout);
    printf("Popped...\n");
    printList(stack->stackTop);
    // freopen("/dev/tty", "w", stdout);

    return ret;
}


void printStack(scopeStack *stack) {
    printList(stack->stackTop);
}