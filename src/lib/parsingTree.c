#include "include/parsingTree.h"

union values unionNULL() {
    union values value;
    value.charVal = 0; 
    return value;
}

union values unionInt(int n) {
    union values value;
    value.intVal = n; 
    return value;
}

union values unionFloat(float f) {
    union values value;
    value.floatVal = f; 
    return value;
}

union values unionChar(char c) {
    union values value;
    value.charVal = c; 
    return value;
}


tree *createNode(char *name, int lineno, SymType symType, union values value) {
    tree *newNode = (tree *)malloc(sizeof(tree));

    newNode->name = (char *)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(newNode->name, name);
    newNode->name[strlen(name)] = 0;
    newNode->lineno = lineno;
    newNode->symType = symType;
    newNode->value = value;
    newNode->type = NULL;

    newNode->numOfChildren = 0;
    newNode->children = NULL;

    return newNode;
}

void setNode(tree *node, char *name, int lineno, SymType symType, union values value) {
    if (!node) return;

    node->name = name;
    node->lineno = lineno;
    node->symType = symType;
    node->value = value;
}

void setNodeType(tree *node, Type *type) {
    if (!node) return;

    node->type = type;
}

void insertChildren(tree *self, int num, ...) {
    if (!self) return;

    tree **childrenArray = (tree **)malloc(num * sizeof(tree *));

    va_list children;
    va_start(children, num);

    for (int i = 0; i < num; i++) {
        childrenArray[i] = va_arg(children, tree *);
    }

    va_end(children);

    self->children = childrenArray;
    self->numOfChildren = num;

    return;
}


void printTree(tree *self, int depth) {
    if (!self) return;

    for (int i = 0; i < depth; i++) printf("  ");

    if (self->symType == NTERM) {
        printf("%s (%d)\n", self->name, self->lineno);
    } else if (self->symType == TYPE_INT) {
        printf("INT: %d\n", self->value.intVal);
    } else if (self->symType == TYPE_FLOAT) {
        printf("FLOAT: %g\n", self->value.floatVal);
    } else if (self->symType == TYPE_CHAR) {
        printf("CHAR: \'%c\'\n", self->value.charVal);
    } else if (self->symType == TYPE_HEXCHAR) {
        printf("CHAR: \'\\x%02hhx\'\n", self->value.charVal);
    } else if (self->symType == TYPE_ID) {
        printf("ID: %s\n", self->name);
    } else if (self->symType == TYPE_TYPE) {
        printf("TYPE: %s\n", self->name);
    } else if (self->symType == OTHERS) {
        printf("%s\n", self->name);
    }

    for (int i = 0; i < self->numOfChildren; i++) {
        printTree(self->children[i], depth + 1);
    }
}