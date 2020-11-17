#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
symbolTable *createTable(nodeEntry *newNode) {
    symbolTable *newTable = malloc(sizeof(symbolTable));

    newTable->entry = newNode;
    newTable->left = NULL;
    newTable->right = NULL;

    return newTable;
}

int insert(symbolTable *symtb, nodeEntry *newNode) {
    //Return 0 if success, otherwise 1;

    //empty table
    if (!symtb) {
        symtb = createTable(newNode);
        return 0;
    }
    
    //insertion
    symbolTable *cur = symtb;
    while (1) {
        int cmp = strcmp(cur->entry->key, newNode->key);
        if (!cmp) return 1;

        if (cmp < 0) { // cur < key: key goes right
            if (cur->right) cur = cur->right; 
            else {
                cur->right = createTable(newNode);
                return 0;
            }
        }
        else  { // cur > key: key goes left
            if (cur->left) cur = cur->left;
            else {
                cur->left = createTable(newNode);
                return 0;
            }
        }
    }
}

nodeEntry *lookup(symbolTable *symtb, const char *key) {
    if (!symtb) return NULL; // empty table;

    symbolTable *cur = symtb;
    while (cur) {
        int cmp = strcmp(cur->entry->key, key);

        if (!cmp) return cur->entry;
        if (cmp < 0) cur = cur->right; // cur < key: cur goes right
        else cur = cur->left;
    }

    return NULL; // not found
}

void printTable(symbolTable *symtb, int level) {
    if (!symtb) return;

    for (int i = 0; i < level; i++) printf("  "); //indent

    printf("%s: %d\n", symtb->entry->key, symtb->entry->value);
    printTable(symtb->left, level + 1);
    printTable(symtb->right, level + 1);
}