# Stage 2: Semantic Analysis

Semantic analysis is a coherent combination of scope checking and type checking. Scope checking is the process during which we examinate whether there are conflictions caused by repeated IDs and at the same time we generate a symbol table for each scope. While type checking is to check whether the types of variables in an expression are compatible.

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
There are essentially three possibilities for a scope:
- global
- CompSt as a function body
- other CompSt

The first and the third cases are simple to handle. However, there are some subtlety in the second case: functions come along with parameters. To solve this issue, a IDBuffer is introduced, which is a global variable used as a templete for parameter IDs. The detailed algorithm is shown as follows:
- On receiving token `LC`, create a new symbol table, push buffer contents into it and clear the buffer;
- On reducing token `CompSt`, pop out the top scope; (note this is nearly the same as receiving `RC`. However, this is easier to pass values.)
- On reducing `Def` or `ExtDef`, clear the buffer;
- On reducing `VarDec` by `ID`, push `ID` into the buffer.
- Deal with normal IDs. (How?)

So there are two global data structure defined:
 the scope stack and the buffer, both defined in `lex.l` and referred in `syntax.y`.

### To Do List: (We are on stage 2: semantic analysis)
- [x] Build BSTs as symbol tables;
- Build scope stack consists of symbol tables;
- Scope checking;
- Typechecking (details to be determined);