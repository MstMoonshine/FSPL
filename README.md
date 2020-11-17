# SPL made Functional

A compiler project for Functional SUSTech Programming Language.

### Issues:
- Why is `Specifier SEMI` allowed?
- If GC for function environments are to be implemented, how to do it?
- `void` not allowed?
- Should composition be set to left or right associative?

### To Do List: (We are on stage 2: semantic analysis)
- [x] Build BSTs as symbol tables;
- Build scope stack consists of symbol tables to do scope checking;
- Typechecking (details to be determined);

### Addtional Features
- $Hom(Type A, Type B)$ type defined as a macro;
- Automatic parallel computation for indenpendent data;