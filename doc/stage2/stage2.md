# Stage 2: Semantic Analysis

Semantic analysis is a coherent combination of scope checking and type checking. Scope checking is the process during which we examinate whether there exist undefined IDs or conflictions caused by repeated IDs and generate a symbol table for each scope. While type checking is to check whether the types of variables in an expression are compatible.

## Scope Checking

#### Tasks:
- no undefined variables
- no conflict inside a single scope
- no out-reach reference in a lambda expression

## REMARKS
- There is a global scope correspondes to no CompSt;
- The scope of a function body should include its arguments;
- The CompSt of a lambda expression is not allowed to access variables (its environment) outside its own scope. Unless its environment has been made an attribute and GC is designed;

## Details
There are a lot troubles here. It took me long to realize that the key is that things in `VarDec` sometime belongs to the scope before it and other times belongs to the one after.

So make an individual scope for `VarList` and merge it into the `DefList` of the following `CompSt`:

For the function `CompSt`, make a global flag `shouldMerge`, which is set to 1 on reducing `VarList` and set back to 0 after merging. Create the new scope on recieving `LC` and merge on reducing `DefList`. Pop on reducing `RC`. For other `CompSt`, merging simply won't happen since the flag is always 0.

The left problem is about separation of struct declaration and implementation:
```
struct a;
float b;
struct a{
    int c;
}
```
I shall ignore this first.
Thus in the global scope, ID is pushed in the following rules:
```
VarDec -> ID
StructSpecifier -> STRUCT ID LC DefList RC
FunDec -> ID LP VarList RP
FunDec -> ID LP RP
```


## Type Checking

There are three primitive and three derived types in FSPL:  
- Primitive: `int`, `float` and `char`
- Derived: arrays, structures and functions

And there are three situations where type checking is necessary: assignments of variables, evaluations of expressions and return values of functions.



### To Do List: (We are on stage 2: semantic analysis)
- [x] Build BSTs as symbol tables;
- [x] Build scope stack consists of symbol tables;
- [x] Scope checking;
- [x] Implementation of types;
- Equivalence checking function for types, i.e. `sameType`;
- Type checking in expressions;
- Type checking in variable assignments;
- Type checking in returns of functions.