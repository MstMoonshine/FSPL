#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

typedef struct entryValue
{
    int a;
} entryValue;

typedef struct nodeEntry
{
    char key[33]; //32 + 1 for security concern;
    entryValue value;
} nodeEntry;

typedef struct binarySearchTree
{
    nodeEntry *entry;
    struct binarySearchTree *left, *right;
} symbolTable;


/*
Something about entryValue goes here...
*/
entryValue createEntryValue(int a);

/* nodeEntry */
nodeEntry *createNodeEntry(const char *key, entryValue value);

/* binarySearchTree */
symbolTable *createTable(nodeEntry *newNode);
int insert(symbolTable *symtb, nodeEntry *newNode); //Return 0 if success, otherwise 1;
nodeEntry *lookup(symbolTable *symtb, const char *key);
void printTable(symbolTable *symtb, int level); //level is for recursion. set to 0 if used;



#endif