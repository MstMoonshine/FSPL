%option yylineno
%option noyywrap

%{

    #include "build/stage1/syntax.tab.h"
    #include "include/parsingTree.h"
    #include "include/symbolTable.h"
    #include "include/scopeStack.h"
    #include <string.h>

    short lexicalErrorExists = 0;
    void lexErrorHandler();

    #undef YY_USER_ACTION
    int yycolno = 1;
    #define YY_USER_ACTION \
            yylloc.first_line = yylineno; \
            yylloc.first_column = yycolno; \
            yylloc.last_line = yylineno; \
            yylloc.last_column = yycolno + yyleng; \
            yycolno += yyleng;

    scopeStack *stack;
    int shouldMerge = 0;
%}

INT -?((0|[1-9][0-9]*)|(0(x|X)[1-9a-fA-F][0-9a-fA-F]*))
FLOAT {INT}\.[0-9][0-9]*
WRONG_HEXCHAR \'\\(x|X)[0-9a-zA-Z]*\'
HEXCHAR \'\\(x|X)[0-9a-fA-F]{2}\'
CHAR (\'.\')|{HEXCHAR}

ID (_|[a-zA-Z])(_|[0-9a-zA-Z])*

CONST const
TYPE (int)|(float)|(char)
LAMBDA lambda
STRUCT struct
FUNC function

IF if
ELSE else
WHILE while
RETURN return

DOT \.
SEMI ;
COMMA ,

RA ->
ASSIGN =

LT <
LE <=
GT >
GE >=
NE !=
EQ ==
PLUS \+
MINUS -
MUL \*
DIV \/
COMP @
AND &&
OR \|\|
NOT !

LP \(
RP \)
LB \[
RB \]
LC \{
RC \}

%%

{CONST} { yylval = createNode("CONST", yylineno, OTHERS, unionNULL()); return CONST; }
{TYPE} { yylval = createNode(yytext, yylineno, TYPE_TYPE, unionNULL()); return TYPE; }
{LAMBDA} { yylval = createNode("LAMBDA", yylineno, OTHERS, unionNULL()); return LAMBDA; }
{STRUCT} { yylval = createNode("STRUCT", yylineno, OTHERS, unionNULL()); return STRUCT; }
{FUNC} { yylval = createNode("FUNC", yylineno, OTHERS, unionNULL()); return FUNC; }
{IF} { yylval = createNode("IF", yylineno, OTHERS, unionNULL()); return IF; }
{ELSE} { yylval = createNode("ELSE", yylineno, OTHERS, unionNULL()); return ELSE; }
{WHILE} { yylval = createNode("WHILE", yylineno, OTHERS, unionNULL()); return WHILE; }
{RETURN} { yylval = createNode("RETURN", yylineno, OTHERS, unionNULL()); return RETURN; }
{DOT} { yylval = createNode("DOT", yylineno, OTHERS, unionNULL()); return DOT; }
{SEMI} { yylval = createNode("SEMI", yylineno, OTHERS, unionNULL()); return SEMI; }
{COMMA} { yylval = createNode("COMMA", yylineno, OTHERS, unionNULL()); return COMMA; }
{ASSIGN} { yylval = createNode("ASSIGN", yylineno, OTHERS, unionNULL()); return ASSIGN; }
{RA} { yylval = createNode("RA", yylineno, OTHERS, unionNULL()); return RA; }
{LT} { yylval = createNode("LT", yylineno, OTHERS, unionNULL()); return LT; }
{LE} { yylval = createNode("LE", yylineno, OTHERS, unionNULL()); return LE; }
{GT} { yylval = createNode("GT", yylineno, OTHERS, unionNULL()); return GT; }
{GE} { yylval = createNode("GE", yylineno, OTHERS, unionNULL()); return GE; }
{NE} { yylval = createNode("NE", yylineno, OTHERS, unionNULL()); return NE; }
{EQ} { yylval = createNode("EQ", yylineno, OTHERS, unionNULL()); return EQ; }
{PLUS} { yylval = createNode("PLUS", yylineno, OTHERS, unionNULL()); return PLUS; }
{MINUS} { yylval = createNode("MINUS", yylineno, OTHERS, unionNULL()); return MINUS; }
{MUL} { yylval = createNode("MUL", yylineno, OTHERS, unionNULL()); return MUL; }
{DIV} { yylval = createNode("DIV", yylineno, OTHERS, unionNULL()); return DIV; }
{COMP} { yylval = createNode("COMP", yylineno, OTHERS, unionNULL()); return COMP; }
{AND} { yylval = createNode("AND", yylineno, OTHERS, unionNULL()); return AND; }
{OR} { yylval = createNode("OR", yylineno, OTHERS, unionNULL()); return OR; }
{NOT} { yylval = createNode("NOT", yylineno, OTHERS, unionNULL()); return NOT; }
{LP} { yylval = createNode("LP", yylineno, OTHERS, unionNULL()); return LP; }
{RP} { yylval = createNode("RP", yylineno, OTHERS, unionNULL()); return RP; }
{LB} { yylval = createNode("LB", yylineno, OTHERS, unionNULL()); return LB; }
{RB} { yylval = createNode("RB", yylineno, OTHERS, unionNULL()); return RB; }

{LC} {
    if(!shouldMerge) pushScope(stack, initTable());

    yylval = createNode("LC", yylineno, OTHERS, unionNULL());
    return LC;
}
{RC} {
    popScope(stack);

    yylval = createNode("RC", yylineno, OTHERS, unionNULL());
    return RC;
}

{INT} { yylval = createNode("INT", yylineno, TYPE_INT, unionInt(atoi(yytext))); return INT; }
{FLOAT} { yylval = createNode("FLOAT", yylineno, TYPE_FLOAT, unionFloat(atof(yytext))); return FLOAT; }
{HEXCHAR} { yylval = createNode("CHAR", yylineno, TYPE_HEXCHAR, unionChar((char)strtol(yytext+3, NULL, 16))); return CHAR; }
{CHAR} { yylval = createNode("CHAR", yylineno, TYPE_CHAR, unionChar(yytext[1])); return CHAR; }
{ID} {
    if (strlen(yytext) > 32) {
        lexErrorHandler();
        fprintf(stderr, "Id name too long: %s\n", yytext);
    }
    char id[33];
    strncpy(id, yytext, 32);
    id[32] = '\x0';
    yylval = createNode(id, yylineno, TYPE_ID, unionNULL());
    return ID;
}

[ \t] {}
"\n" { yycolno = 1; }

{INT}{ID} { yylval = createNode("", yylineno, TYPE_ID, unionNULL()); lexErrorHandler(); fprintf(stderr, "unknown lexeme %s\n", yytext); return ID; }

.|{WRONG_HEXCHAR} { yylval = createNode("", yylineno, TYPE_ID, unionNULL()); lexErrorHandler(); fprintf(stderr, "unknown lexeme %s\n", yytext); return MYSTERIOUS_LEXEME; }

%%

void lexErrorHandler() {
    lexicalErrorExists = 1;
    fprintf(stderr, "Error type A at Line %d: ", yylineno);
}