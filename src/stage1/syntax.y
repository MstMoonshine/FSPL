%{
    #include "build/stage1/lex.yy.c"
    #include "include/io.h"
    #include "include/parsingTree.h"

    void yyerror(const char*);
    short syntaxErrorExists = 0;

    int lineno = 0;

    tree *parsingTree;
    
%}

%code requires { #include "include/parsingTree.h" }
%define api.value.type {tree *}

%token MYSTERIOUS_LEXEME
%token INVALID_ID

%token ID
%token LC RC

%right ASSIGN RA
%left OR
%left AND
%left LT LE GT GE EQ NE
%left PLUS MINUS
%left MUL DIV
%left COMP
%right NOT
%token DOT
%token LB RB
%token LP RP

%token IF ELSE WHILE RETURN
%token SEMI COMMA
%token LAMBDA
%token TYPE STRUCT FUNCTION
%token CONST
%token INT 
%token FLOAT
%token CHAR
%%

Program: ExtDefList { $$ = createNode("Program", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); parsingTree = $$; }
       ;
ExtDefList: ExtDef ExtDefList { $$ = createNode("ExtDefList", @$.first_line, NTERM, unionNULL()); insertChildren($$, 2, $1, $2); }
          | %empty { $$ = NULL; }
          ;
ExtDef: QualifiedSpecifier ExtDecList SEMI { $$ = createNode("ExtDef", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
      | QualifiedSpecifier SEMI { $$ = createNode("ExtDef", @$.first_line, NTERM, unionNULL()); insertChildren($$, 2, $1, $2); }
      | QualifiedSpecifier FunDec CompSt { $$ = createNode("ExtDef", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
      | QualifiedSpecifier FunDec error RC { fprintf(stderr, "Missing left brace\n"); }
      | QualifiedSpecifier FunDec LC error { fprintf(stderr, "Missing right brace\n"); } 
      ;
ExtDecList: VarDec { $$ = createNode("ExtDecList", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
          | VarDec COMMA ExtDecList { $$ = createNode("ExtDecList", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
          ;

QualifiedSpecifier: Specifier { $$ = createNode("QualifiedSpecifier", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
                  | CONST Specifier { $$ = createNode("QualifiedSpecifier", @$.first_line, NTERM, unionNULL()); insertChildren($$, 2, $1, $2); }
Specifier: TYPE { $$ = createNode("Specifier", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
         | StructSpecifier { $$ = createNode("Specifier", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
         | FunctionSpecifier { $$ = createNode("Specifier", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
         ;
StructSpecifier: STRUCT ID LC DefList RC { $$ = createNode("StructSpecifier", @$.first_line, NTERM, unionNULL()); insertChildren($$, 5, $1, $2, $3, $4, $5); }
               | STRUCT ID { $$ = createNode("StructSpecifier", @$.first_line, NTERM, unionNULL()); insertChildren($$, 2, $1, $2); }
               ;
FunctionSpecifier: FUNCTION LT SpecifierList RA Specifier GT { $$ = createNode("FunctionSpecifier", @$.first_line, NTERM, unionNULL()); insertChildren($$, 6, $1, $2, $3, $4, $5, $6); }
                 ;
SpecifierList: Specifier { $$ = createNode("SpecifierList", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
             | Specifier COMMA SpecifierList { $$ = createNode("SpecifierList", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
        | %empty { $$ = NULL; }
        ;

VarDec: ID { $$ = createNode("VarDec", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
      | VarDec LB INT RB { $$ = createNode("VarDec", @$.first_line, NTERM, unionNULL()); insertChildren($$, 4, $1, $2, $3, $4); }
      ;
FunDec: ID LP VarList RP { $$ = createNode("FunDec", @$.first_line, NTERM, unionNULL()); insertChildren($$, 4, $1, $2, $3, $4); }
      | ID LP RP { $$ = createNode("FunDec", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
      | ID LP error { fprintf(stderr, "Missing closing parenthesis \')\'\n"); }
      ;
VarList: ParamDec COMMA VarList { $$ = createNode("VarList", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
       | ParamDec { $$ = createNode("VarList", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
       ;
ParamDec: QualifiedSpecifier VarDec { $$ = createNode("ParamDec", @$.first_line, NTERM, unionNULL()); insertChildren($$, 2, $1, $2); }
        ;

CompSt: LC DefList StmtList RC { $$ = createNode("CompSt", @$.first_line, NTERM, unionNULL()); insertChildren($$, 4, $1, $2, $3, $4); }
      ;
StmtList: Stmt StmtList { $$ = createNode("StmtList", @$.first_line, NTERM, unionNULL()); insertChildren($$, 2, $1, $2); }
        | Stmt Def error StmtList { fprintf(stderr, "Missing specifier\n"); }
        | %empty { $$ = NULL; }
        ;
Stmt: Exp SEMI { $$ = createNode("Stmt", @$.first_line, NTERM, unionNULL()); insertChildren($$, 2, $1, $2); }
    | CompSt { $$ = createNode("Stmt", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
    | RETURN Exp SEMI { $$ = createNode("Stmt", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
    | IF LP Exp RP Stmt { $$ = createNode("Stmt", @$.first_line, NTERM, unionNULL()); insertChildren($$, 5, $1, $2, $3, $4, $5); }
    | IF LP Exp RP Stmt ELSE Stmt { $$ = createNode("Stmt", @$.first_line, NTERM, unionNULL()); insertChildren($$, 6, $1, $2, $3, $4, $5, $6); }
    | WHILE LP Exp RP Stmt { $$ = createNode("Stmt", @$.first_line, NTERM, unionNULL()); insertChildren($$, 5, $1, $2, $3, $4, $5); }
    | RETURN Exp error { fprintf(stderr, "Missing semicolon \';\'\n"); }
    ;

DefList: Def DefList { $$ = createNode("DefList", @$.first_line, NTERM, unionNULL()); insertChildren($$, 2, $1, $2); }
       | %empty { $$ = NULL; }
       ;
Def: QualifiedSpecifier DecList SEMI { $$ = createNode("Def", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | QualifiedSpecifier DecList error { fprintf(stderr, "Missing semicolon \';\'\n"); }
   ;
DecList: Dec { $$ = createNode("DecList", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
       | Dec COMMA DecList { $$ = createNode("DecList", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
       ;
Dec: VarDec { $$ = createNode("Dec", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
   | VarDec ASSIGN Exp { $$ = createNode("Dec", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   ;

LambdaExp: LAMBDA LT VarList RA Specifier GT CompSt { $$ = createNode("LambdaExp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 6, $1, $2, $3, $4, $5, $6); } 
         ;
Exp: Exp ASSIGN Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp AND Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp OR Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp MYSTERIOUS_LEXEME Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp LT Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp LE Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp GT Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp GE Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp NE Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp EQ Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp PLUS Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp MINUS Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp MUL Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp DIV Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp COMP Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | LP Exp RP { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | MINUS Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 2, $1, $2); }
   | NOT Exp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 2, $1, $2); }
   | Exp LP Args RP { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 4, $1, $2, $3, $4); }
   | Exp LP Args error { fprintf(stderr, "Missing closing parenthesis \')\'\n"); }
   | Exp LP RP { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | Exp LB Exp RB { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 4, $1, $2, $3, $4); }
   | Exp DOT ID { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
   | LambdaExp { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
   | ID { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
   | INT { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
   | FLOAT { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
   | CHAR { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
   | MysteriousLexemeList { $$ = createNode("Exp", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
   ;
MysteriousLexemeList: MYSTERIOUS_LEXEME { $$ = createNode("MysteriousLexemeList", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
                    | MYSTERIOUS_LEXEME MysteriousLexemeList { $$ = createNode("MysteriousLexemeList", @$.first_line, NTERM, unionNULL()); insertChildren($$, 2, $1, $2); }
                    ;
Args: Exp COMMA Args { $$ = createNode("Args", @$.first_line, NTERM, unionNULL()); insertChildren($$, 3, $1, $2, $3); }
    | Exp { $$ = createNode("Args", @$.first_line, NTERM, unionNULL()); insertChildren($$, 1, $1); }
    ;

%%

void yyerror(const char *s) {
    syntaxErrorExists = 1;
    fprintf(stderr, "Error Type B at Line %d: ", yylineno);
}

int main(int argc, char **argv) {

while (__AFL_LOOP(1000)) {
    
    if (!check_file_path_legal(argc, argv)) return 1;
    yyin = fopen(argv[1], "r");
    yyparse();
    printTree(parsingTree, 0);

    return 0;

} //End of AFL_LOOP

}
