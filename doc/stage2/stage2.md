# Stage 2: Semantic Analysis

Semantic analysis is a coherent combination of scope checking and type checking. Scope checking is the process during which we examinate whether there are conflictions caused by repeated IDs and at the same time we generate a symbol table for each scope. While type checking is to check whether the types of variables in an expression are compatible.

## Type Checking

#### Tasks:
- no undefined variables
- no conflict inside a single scope
- no out-reach reference in a lambda expression

## REMARKS
- There is a global scope correspondes to no CompSt;
- The scope of a function body should include its arguments;
- The CompSt of a lambda expression is not allowed to access variables (its environment) outside its own scope. Unless its environment has been made an attribute and GC is designed;