# SPL made Functional

A compiler project for Functional SUSTech Programming Language.

### Issues:
- If GC for function environments are to be implemented, how to do it?
- Should composition be set to left or right associative?

## REMARKS
There are two significant kinds of data to be processed: Identifiers and Expressions.

The issues related to IDs are dissolved via generating symbol tables while the exprssion parts is to deal with an abstact syntax tree.

### Addtional Features
- $Hom(Type A, Type B)$ type defined as a macro;
- Automatic parallel computation for indenpendent data;