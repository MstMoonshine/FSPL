#include <stdlib.h>
#include <string.h>
#include "include/binarySearchTree.h"


/*
Something about entryValue goes here...
*/
entryValue createEntryValue(int a) {
    entryValue newValue;
    newValue.a = a;
    return newValue;
}


/* nodeEntry */
nodeEntry *createNodeEntry(const char *key, entryValue value) {
    nodeEntry *newNode = malloc(sizeof(nodeEntry));

    strncpy(newNode->key, key, 33);
    newNode->value = value;

    return newNode;
}


/* binarySearchTree */
// int insert(symbolTable *symtb, nodeEntry *newNode) {
//     return 1;
// }

// nodeEntry *lookup(symbolTable *symtb, const char *key) {}