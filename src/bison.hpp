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

#ifndef YY_YY_SRC_BISON_HPP_INCLUDED
# define YY_YY_SRC_BISON_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_FUNCTION = 258,
    TOK_RETURN = 259,
    TOK_IF = 260,
    TOK_ELSE = 261,
    TOK_FOR = 262,
    TOK_WHILE = 263,
    TOK_PRINT = 264,
    TOK_IN = 265,
    TOK_OUT = 266,
    TOK_STEPPER = 267,
    TOK_SERVO = 268,
    TOK_DELAY = 269,
    TOK_AND = 270,
    TOK_OR = 271,
    TOK_IDENTIFIER = 272,
    TOK_FLOAT = 273,
    TOK_INTEGER = 274,
    TOK_STRING = 275,
    TOK_QUANDO = 276,
    TOK_ESTA = 277,
    EQ_OP = 278,
    NE_OP = 279,
    GE_OP = 280,
    LE_OP = 281,
    GT_OP = 282,
    LT_OP = 283,
    IFX = 284
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 23 "src/Language.y" /* yacc.c:1909  */

	char *port;
	char *ident;
	char *str;
	int nint;
	float nfloat;
	Node *node;
	Stmts *stmt;

#line 94 "src/bison.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_BISON_HPP_INCLUDED  */
