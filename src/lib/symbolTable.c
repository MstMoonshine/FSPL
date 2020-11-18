#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "include/symbolTable.h"
#include "include/debug.h"


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
symbolTable *initTable() {
    symbolTable *newTable = malloc(sizeof(symbolTable));

    newTable->entry = NULL;
    newTable->left = NULL;
    newTable->right = NULL;

    return newTable;
}

symbolTable *createTable(nodeEntry *newNode) {
    symbolTable *newTable = malloc(sizeof(symbolTable));

    newTable->entry = newNode;
    newTable->left = NULL;
    newTable->right = NULL;

    return newTable;
}

int insert(symbolTable *symbt, nodeEntry *newNode, int lineno) {
    //Return 0 if success, otherwise 1;
    debugPoint();
    if (!symbt) return 1;

    //empty table
    if (!symbt->entry) {
        symbt->entry = newNode;
        return 1;
    }
    
    //insertion
    symbolTable *cur = symbt;
    while (1) {
        int cmp = strcmp(cur->entry->key, newNode->key);
        if (!cmp) { fprintf(stderr, "Error: Identifier redefinition at line %d: %s\n", lineno, newNode->key); return 1; }

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

entryValue *lookup(symbolTable *symbt, const char *key) {
    if (!symbt->entry) return NULL; // empty table;

    symbolTable *cur = symbt;
    while (cur) {
        int cmp = strcmp(cur->entry->key, key);

        if (!cmp) return &cur->entry->value;
        if (cmp < 0) cur = cur->right; // cur < key: cur goes right
        else cur = cur->left;
    }

    return NULL; // not found
}

void clearTable(symbolTable *symbt) {
    if (!symbt) {
        return;
    } else if (!symbt->left && !symbt->right) {
        free(symbt);
        return;
    }

    clearTable(symbt->left);
    clearTable(symbt->right);
}

void printTable(symbolTable *symbt, int level) {
    if (!symbt) { return; printf("Empty table.\n"); }
    if (!symbt->entry) { printf("Empty entry.\n"); return; }

    for (int i = 0; i < level; i++) printf("  "); //indent

    printf("%s: %d\n", symbt->entry->key, symbt->entry->value.a);
    printTable(symbt->left, level + 1);
    printTable(symbt->right, level + 1);
}