/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_USE_HOME_ALISSON_DOWNLOADS_ROBCMP_SVDS_AND_RP2040_BUILD_POINTER_TEST_LANGUAGEUSE_GEN_HPP_INCLUDED
# define YY_USE_HOME_ALISSON_DOWNLOADS_ROBCMP_SVDS_AND_RP2040_BUILD_POINTER_TEST_LANGUAGEUSE_GEN_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int USEdebug;
#endif
/* "%code requires" blocks.  */
#line 8 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"

  #include "BuildTypes.h"

#line 53 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_VOID = 258,                /* TOK_VOID  */
    TOK_RETURN = 259,              /* TOK_RETURN  */
    TOK_REGISTER = 260,            /* TOK_REGISTER  */
    TOK_AT = 261,                  /* TOK_AT  */
    TOK_VOLATILE = 262,            /* TOK_VOLATILE  */
    TOK_CONST = 263,               /* TOK_CONST  */
    TOK_ASM = 264,                 /* TOK_ASM  */
    TOK_IF = 265,                  /* TOK_IF  */
    TOK_ELSE = 266,                /* TOK_ELSE  */
    TOK_LOOP = 267,                /* TOK_LOOP  */
    TOK_WHILE = 268,               /* TOK_WHILE  */
    TOK_AND = 269,                 /* TOK_AND  */
    TOK_OR = 270,                  /* TOK_OR  */
    TOK_IDENTIFIER = 271,          /* TOK_IDENTIFIER  */
    TOK_USE_IDENTIFIER = 272,      /* TOK_USE_IDENTIFIER  */
    TOK_CHAR = 273,                /* TOK_CHAR  */
    TOK_UINTEGER = 274,            /* TOK_UINTEGER  */
    TOK_FLOAT = 275,               /* TOK_FLOAT  */
    TOK_DOUBLE = 276,              /* TOK_DOUBLE  */
    TOK_LDOUBLE = 277,             /* TOK_LDOUBLE  */
    TOK_INTEGER = 278,             /* TOK_INTEGER  */
    TOK_STRING = 279,              /* TOK_STRING  */
    TOK_TRUE = 280,                /* TOK_TRUE  */
    TOK_FALSE = 281,               /* TOK_FALSE  */
    TOK_FINT8 = 282,               /* TOK_FINT8  */
    TOK_FINT16 = 283,              /* TOK_FINT16  */
    TOK_FINT32 = 284,              /* TOK_FINT32  */
    TOK_FINT64 = 285,              /* TOK_FINT64  */
    TOK_FFLOAT = 286,              /* TOK_FFLOAT  */
    TOK_FDOUBLE = 287,             /* TOK_FDOUBLE  */
    TOK_FCHAR = 288,               /* TOK_FCHAR  */
    TOK_FLONG = 289,               /* TOK_FLONG  */
    TOK_FUNSIGNED = 290,           /* TOK_FUNSIGNED  */
    TOK_FBOOL = 291,               /* TOK_FBOOL  */
    TOK_TYPE = 292,                /* TOK_TYPE  */
    TOK_INTF = 293,                /* TOK_INTF  */
    TOK_IMPL = 294,                /* TOK_IMPL  */
    TOK_USE = 295,                 /* TOK_USE  */
    TOK_ENUM = 296,                /* TOK_ENUM  */
    TOK_BIND = 297,                /* TOK_BIND  */
    TOK_TO = 298,                  /* TOK_TO  */
    TOK_SINGLETON = 299,           /* TOK_SINGLETON  */
    TOK_TRANSIENT = 300,           /* TOK_TRANSIENT  */
    TOK_QUANDO = 301,              /* TOK_QUANDO  */
    TOK_ESTA = 302,                /* TOK_ESTA  */
    EQ_OP = 303,                   /* EQ_OP  */
    NE_OP = 304,                   /* NE_OP  */
    GE_OP = 305,                   /* GE_OP  */
    LE_OP = 306,                   /* LE_OP  */
    GT_OP = 307,                   /* GT_OP  */
    LT_OP = 308,                   /* LT_OP  */
    TOK_LSHIFT = 309,              /* TOK_LSHIFT  */
    TOK_RSHIFT = 310,              /* TOK_RSHIFT  */
    TOK_MUL_ASSIGN = 311,          /* TOK_MUL_ASSIGN  */
    TOK_INLINE = 312,              /* TOK_INLINE  */
    TOK_NOINLINE = 313,            /* TOK_NOINLINE  */
    TOK_WEAK = 314,                /* TOK_WEAK  */
    TOK_SECTION = 315,             /* TOK_SECTION  */
    TOK_NAKED = 316,               /* TOK_NAKED  */
    TOK_SIGNAL = 317,              /* TOK_SIGNAL  */
    TOK_DEBUGONLY = 318,           /* TOK_DEBUGONLY  */
    TOK_NOOPT = 319                /* TOK_NOOPT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 45 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"

	char *ident;
	char *str;
	char ch;
	int64_t nint;
	uint64_t unint;
	DataType dtype;
	float nfloat;
	double ndouble;
	long double nldouble;
	Node *node;
	ArrayElements *aes;
	MatrixElements *mes;
	FunctionParams *fps;
	FunctionAttributes *fattrs;
	FunctionAttribute *fattr;
	ParamsCall *pc;
	vector<Node*> *nodes;
	vector<string> *strings;
	ArrayElement *ae;
	MatrixElement *me;
	Variable *fp;
	LeftValueData *leftvd;

#line 159 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
typedef location_t YYLTYPE;




int USEparse (yyscan_t scanner);

/* "%code provides" blocks.  */
#line 19 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"

  #ifndef YYLTYPE
  #define YYLTYPE location_t
  #endif
  #include "FlexDependencies.h"
#line 79 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"

  #define YY_DECL int USElex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, yyscan_t yyscanner)
  YY_DECL;
  void yyerror(YYLTYPE *yyloc, yyscan_t yyscanner, const char *msg);

#line 188 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.hpp"

#endif /* !YY_USE_HOME_ALISSON_DOWNLOADS_ROBCMP_SVDS_AND_RP2040_BUILD_POINTER_TEST_LANGUAGEUSE_GEN_HPP_INCLUDED  */
