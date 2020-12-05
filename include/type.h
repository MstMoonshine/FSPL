#ifndef TYPE_H
#define TYPE_H

typedef struct Type
{
    char name[32]; // for struct only currently, unless `typedef` implemented;
    enum { PRIMITIVE, ARRAY, STRUCTURE, FUNCTION } category;
    union {
        enum { INT, FLOAT, CHAR } primitive;
        struct Array *array;
        struct FieldList *structure;
        struct Function *function;
    };
} Type;

typedef struct Array {
    struct Type *base;
    int size;
} Array;

typedef struct FieldList {
    char name[32]; //name of each variable
    struct Type *type;
    struct FieldList *next;
} FieldList;

typedef struct Function {
    struct Type **argTypeList;
    int argNum;
    struct Type *retType;
} Function;

#endif