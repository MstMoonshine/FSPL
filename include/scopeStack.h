#ifndef SCOPESTACK_H
#define SCOPESTACK_H

#include "include/symbolTable.h"
#include "include/linkedList.h"

typedef struct scopeStack
{
    linkedList *stackTop;
} scopeStack;

scopeStack *initStack(symbolTable *globalScope);
symbolTable *getScope(scopeStack *stack);
entryValue *lookupGlobal(scopeStack *stack, const char *key);
entryValue *lookupLocal(scopeStack *stack, const char *key);
void pushScope(scopeStack *stack, symbolTable *scope);
symbolTable *popScope(scopeStack *stack);

void printStack(scopeStack *stack);


#endif