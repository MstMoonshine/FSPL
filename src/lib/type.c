#include "include/type.h"
#include <string.h>
#include <stdlib.h>

Type *createPrimitiveType(const char *name, enum primitiveType primitive) {
    Type *newType = (Type *)malloc(sizeof(Type));

    if (!name || (strlen(name) > 32)) return NULL;
    strcpy(newType->name, name);
    newType->category = PRIMITIVE;
    newType->content.primitive = primitive;

    return newType;
}

Type *createDerivedType(const char *name, enum TypeCategory category, void *contentPointer) {
    Type *newType = (Type *)malloc(sizeof(Type));

    if (!name || (strlen(name) > 32)) return NULL;
    strcpy(newType->name, name);
    newType->category = category;

    if (category == ARRAY) newType->content.array = (Array *) contentPointer;
    else if (category = STRUCTURE) newType->content.structure = (FieldList *)contentPointer;
    else if (category = FUNCTION) newType->content.function = (Function *)contentPointer;
    else return NULL;

    return newType;
}


Array *createArray(Type *base, int size) {
    Array *newArray = (Array *)malloc(sizeof(Array));

    newArray->base = base;
    newArray->size = size;

    return newArray;
}


FieldList *createFieldList(const char *name, Type *type) {
    FieldList *newFieldList = (FieldList *)malloc(sizeof(FieldList));

    strcpy(newFieldList->name, name);
    newFieldList->type = type;
    newFieldList->next = NULL;

    return newFieldList;
}

int insertFieldList(FieldList *fieldList, const char *name, Type *type) {
    if (!fieldList) return 0;

    FieldList *newFieldList = createFieldList(name, type);
    fieldList->next = newFieldList;

    return 1;
}


Function *createFunction(FieldList *argList, Type *retType) {
    Function *newFun = (Function *)malloc(sizeof(Function));

    newFun->argList = argList;
    newFun->retType = retType;

    return newFun;
}


int sameType(Type *type1, Type *type2) {
    //...
    return 1;
}