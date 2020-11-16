/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_HOME_STUDENT_FSPL_BUILD_STAGE1_SYNTAX_TAB_H_INCLUDED
# define YY_YY_HOME_STUDENT_FSPL_BUILD_STAGE1_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 15 "/home/student/FSPL/src/stage1/syntax.y" /* yacc.c:1909  */
 #include "include/parsingTree.h" 

#line 47 "/home/student/FSPL/build/stage1/syntax.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MYSTERIOUS_LEXEME = 258,
    INVALID_ID = 259,
    ID = 260,
    LC = 261,
    RC = 262,
    ASSIGN = 263,
    RA = 264,
    OR = 265,
    AND = 266,
    LT = 267,
    LE = 268,
    GT = 269,
    GE = 270,
    EQ = 271,
    NE = 272,
    PLUS = 273,
    MINUS = 274,
    MUL = 275,
    DIV = 276,
    COMP = 277,
    NOT = 278,
    DOT = 279,
    LB = 280,
    RB = 281,
    LP = 282,
    RP = 283,
    IF = 284,
    ELSE = 285,
    WHILE = 286,
    RETURN = 287,
    SEMI = 288,
    COMMA = 289,
    LAMBDA = 290,
    TYPE = 291,
    STRUCT = 292,
    FUNCTION = 293,
    CONST = 294,
    INT = 295,
    FLOAT = 296,
    CHAR = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef tree * YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_HOME_STUDENT_FSPL_BUILD_STAGE1_SYNTAX_TAB_H_INCLUDED  */
