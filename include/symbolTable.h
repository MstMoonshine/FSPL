/**
* Symbol tables contains information about an identifier such as its character string (lexeme), its type, its position in storage and any other relevant information... 

-- the Dragon Book

Here we will be using a binary search tree as a symbol table in a scope.
*/


#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "include/type.h"

typedef struct entryValue
{
    Type *type;
} entryValue;

typedef struct nodeEntry
{
    char key[33]; //32 + 1, 1 for '\0'
    entryValue value;
} nodeEntry;

typedef struct binarySearchTree
{
    nodeEntry *entry;
    struct binarySearchTree *left, *right;
} symbolTable;


/*
Something about entryValue goes here...
The entryvalue mainly consists of the type of the symbol at the moment.
*/
entryValue createEntryValue(Type *type);

/* nodeEntry */
nodeEntry *createNodeEntry(const char *key, entryValue value);

/* binarySearchTree */
symbolTable *initTable();
symbolTable *createTable(nodeEntry *newNode);
int insert(symbolTable *symtb, nodeEntry *newNode, int lineno); //Return 0 if success, otherwise 1;
entryValue *lookup(symbolTable *symtb, const char *key);
void clearTable(symbolTable *symtb);

void printTable(symbolTable *symtb, int level); //level is for recursion. set to 0 if used;



#endif