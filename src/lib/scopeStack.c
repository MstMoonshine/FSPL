#include "include/scopeStack.h"
#include <stdlib.h>
#include <stdio.h>

scopeStack *initStack(symbolTable *globalScope) {
    scopeStack *newStack = malloc(sizeof(scopeStack));
    linkedList *newList = initList(globalScope);

    newStack->stackTop = newList;

    return newStack;
}

void pushScope(scopeStack *stack, symbolTable *scope) {
    stack->stackTop = insertAtHead(stack->stackTop, scope);
}

symbolTable *popScope(scopeStack *stack) {
    symbolTable *ret = stack->stackTop->symbt;

    stack->stackTop = removeAtHead(stack->stackTop);

    return ret;
}


void printStack(scopeStack stack) {
    printList(stack.stackTop);
}