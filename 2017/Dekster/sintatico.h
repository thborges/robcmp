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

#ifndef YY_YY_SINTATICO_H_INCLUDED
# define YY_YY_SINTATICO_H_INCLUDED
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
    TOK_PLUS = 258,
    TOK_MINUS = 259,
    TOK_MULTPL = 260,
    TOK_DIVIDE = 261,
    TOK_OPENP = 262,
    TOK_CLOSEP = 263,
    TOK_INTEGER = 264,
    TOK_DOUBLE = 265,
    NE_OP = 266,
    EQ_OP = 267,
    LT_OP = 268,
    GT_OP = 269,
    LE_OP = 270,
    GE_OP = 271,
    TOK_AND = 272,
    TOK_OR = 273,
    TOK_ALTURA = 274,
    TOK_BASE = 275,
    TOK_RETANGULO = 276,
    TOK_CIRCULO = 277,
    TOK_RAIO = 278,
    TOK_DM = 279,
    TOK_dM = 280,
    TOK_ID = 281,
    TOK_LOSANGO = 282,
    TOK_LINHA = 283,
    TOK_IGUAL = 284
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "calculadora.y" /* yacc.c:1909  */

	int nint;
	float nfloat;
	Node *node;
	Stmts *stmt;

	Coord *coordenada;

#line 93 "sintatico.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SINTATICO_H_INCLUDED  */
