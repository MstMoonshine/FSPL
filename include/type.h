#ifndef TYPE_H
#define TYPE_H

enum TypeCategory { PRIMITIVE, ARRAY, STRUCTURE, FUNCTION };
enum primitiveType { VAR_INT, VAR_FLOAT, VAR_CHAR };

union TypeContent {
    enum primitiveType primitive;
    struct Array *array;
    struct FieldList *structure;
    struct Function *function; 
};

typedef struct Type
{
    char name[32]; // for struct only currently, unless `typedef` implemented;
    enum TypeCategory category;
    union TypeContent content;
} Type;

typedef struct Array {
    struct Type *base;
    int size;
} Array;

typedef struct FieldList {
    /*
    Even if we are using name equivalence for structures, this list information is still necessary,
    since we will need size derivation for structures.
    */
    char name[32]; //name of each variable (identifier)
    struct Type *type;
    struct FieldList *next;
} FieldList;

typedef struct Function {
    struct FieldList *argList; // field list for function arguments
    struct Type *retType;
} Function;

//------------------------------
Type *createPrimitiveType(const char *name, enum primitiveType primitive);
Type *createDerivedType(const char *name, enum TypeCategory category, void *contentPointer);

Array *createArray(Type *base, int size);

FieldList *createFieldList(const char *name, Type *type); 
int insertFieldList(FieldList *fieldList, const char *name, Type *type);

Function *createFunction(FieldList *argList, Type *retType);

//name equivalence for structures. No equivalence for arrays. Structural equivalence for functions.
int sameType(Type *type1, Type *type2);
int structuralEqu(FieldList *fieldList1, FieldList *fieldList2);

#endif