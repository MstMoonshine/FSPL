#include "include/type.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const Type PRI_INT = { .name = "", .category = PRIMITIVE, .content.primitive = VAR_INT };
const Type PRI_FLOAT = { .name = "", .category = PRIMITIVE, .content.primitive = VAR_FLOAT };
const Type PRI_CHAR = { .name = "", .category = PRIMITIVE, .content.primitive = VAR_CHAR };

Type *primitive_int = (Type *)&PRI_INT;
Type *primitive_float = (Type *)&PRI_FLOAT;
Type *primitive_char = (Type *)&PRI_CHAR;

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
    if (type1->category != type2->category) return 0;

    if (type1->category == PRIMITIVE)
        if (type1->content.primitive == type2->content.primitive)
            return 1;

    if (type1->category == STRUCTURE)
        if (!strcmp(type1->name, type2->name)) //name equivalence
            return 1;

    if (type1->category == FUNCTION)
        if (sameType(type1->content.function->retType, 
                     type2->content.function->retType) &&
            structuralEqu(type1->content.function->argList,
                          type2->content.function->argList))
            return 1;
    
    return 0;

}

int structuralEqu(FieldList *fieldList1, FieldList *fieldList2) {
    if (!fieldList1 || !fieldList2) return 0;

    FieldList *cur1 = fieldList1, *cur2 = fieldList2;
    while (cur1 && cur2) {
        if (!sameType(cur1->type, cur2->type)) return 0;
        cur1 = cur1->next; cur2 = cur2->next;
    }

    if (cur1 || cur2) return 0; //one list is longer than the other

    return 1;
}


void printType(Type *type) {
    printf("Type: ");
    if (!type) return;

    if (type->category == PRIMITIVE) {
        if (type->content.primitive == VAR_INT)
            printf("INT");
        else if (type->content.primitive == VAR_FLOAT)
            printf("FLOAT");
        else if (type->content.primitive == VAR_CHAR)
            printf("CHAR");
    } else if (type->category == ARRAY) {
        printf("ARRAY");
    } else if (type->category == STRUCTURE) {
        printf("STRUCTURE");
    } else if (type->category == FUNCTION) {
        printf("FUNCTION");
    }

    return;
}