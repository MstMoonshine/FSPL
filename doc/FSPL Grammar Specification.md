# FSPL Grammar Specification

## Syntax
```
Program: ExtDefList
       ;
ExtDefList: ExtDef ExtDefList
          | %empty
          ;
ExtDef: QualifiedSpecifier ExtDecList SEMI                                      *
      | QualifiedSpecifier SEMI                                                 *
      | QualifiedSpecifier FunDec CompSt                                        *
      ;
ExtDecList: VarDec
          | VarDec COMMA ExtDecList
          ;

QualifiedSpecifier: Specifier                                                   *
                  | CONST Specifier                                             *
Specifier: TYPE
         | StructSpecifier
         | FunctionSpecifier                                                    *
         ;
StructSpecifier: STRUCT ID LC DefList RC
               | STRUCT ID
               ;
FunctionSpecifier: FUNCTION LT QualifiedSpecifierList RA Specifier GT           *
                 ;
QualifiedSpecifierList: QualifiedSpecifier                                      *
                      | QualifiedSpecifier COMMA QualifiedSpecifierList         *
                      | %empty
                      ;

VarDec: ID
      | VarDec LB INT RB
      ;
FunDec: ID LP VarList RP
      | ID LP RP
      ;
VarList: ParamDec COMMA VarList
       | ParamDec
       ;
ParamDec: QualifiedSpecifier VarDec                                             *
        ;

CompSt: LC DefList StmtList RC
      ;
StmtList: Stmt StmtList
        | %empty
        ;
Stmt: Exp SEMI
    | CompSt
    | RETURN Exp SEMI
    | IF LP Exp RP Stmt
    | IF LP Exp RP Stmt ELSE Stmt
    | WHILE LP Exp RP Stmt
    ;

DefList: Def DefList
       | %empty
       ;
Def: QualifiedSpecifier DecList SEMI                                            *
   ;
DecList: Dec
       | Dec COMMA DecList
       ;
Dec: VarDec
   | VarDec ASSIGN Exp
   ;

LambdaExp: LAMBDA LT VarList RA QualifiedSpecifier GT CompSt                    *
         ;
Exp: Exp ASSIGN Exp
   | Exp AND Exp
   | Exp OR Exp
   | Exp LT Exp
   | Exp LE Exp
   | Exp GT Exp
   | Exp GE Exp
   | Exp NE Exp
   | Exp EQ Exp
   | Exp PLUS Exp
   | Exp MINUS Exp
   | Exp MUL Exp
   | Exp DIV Exp
   | Exp COMP Exp                                                               *
   | LP Exp RP
   | MINUS Exp
   | NOT Exp
   | Exp LP Args RP                                                             *
   | Exp LP RP                                                                  *
   | Exp LB Exp RB
   | Exp DOT ID
   | LambdaExp                                                                  *
   | ID
   | INT
   | FLOAT
   | CHAR
   ;
Args: Exp COMMA Args
    | Exp
    ;
```