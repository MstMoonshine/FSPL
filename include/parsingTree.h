#ifndef PARSINGTREE_H
#define PARSINGTREE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "include/type.h"

typedef enum {
    /*
    TYPE_INT, TYPE_FLOAT, TYPE_CHAR, TYPE_HEXCHAR are types of primitive literals.
    */
    NTERM, TYPE_INT, TYPE_FLOAT, TYPE_CHAR, TYPE_HEXCHAR, TYPE_ID, TYPE_TYPE, OTHERS
} SymType;

union values {
    int intVal;
    float floatVal;
    char charVal;
};

struct treeStruct {
    char *name; //name of the nonterminal or token
    int lineno;
    SymType symType; //grammar symbol type
    union values value;
    Type *type;

    int numOfChildren; //0 by default.
    struct treeStruct **children;
};

typedef struct treeStruct tree;

union values unionNULL(); //use int value 0 as unionNULL
union values unionInt(int n);
union values unionFloat(float f);
union values unionChar(char c);

tree *createNode(char *name, int lineno, SymType type, union values value);
void setNode(tree *node, char *name, int lineno, SymType type, union values value);
void setNodeType(tree *node, Type *type);
void insertChildren(tree *self, int num, ...); //Note that children nodes must be inserted (or changed) all at once.

void printTree(tree *self, int depth);

#endif