#ifndef SCOPESTACK_H
#define SCOPESTACK_H

#include "include/symbolTable.h"
#include "include/linkedList.h"

typedef struct scopeStack
{
    linkedList *stackTop;
} scopeStack;

scopeStack *initStack(symbolTable *globalScope);
void pushScope(scopeStack *stack, symbolTable *scope);
symbolTable *popScope(scopeStack *stack);

void printStack(scopeStack *stack);


#endif