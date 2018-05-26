/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "HCompiler.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "limite.c"


class Node;
class Stmts;

extern FILE *yyin;


#line 80 "sintatico.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "sintatico.h".  */
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
    TOK_WHILE = 258,
    TOK_IF = 259,
    TOK_ELSE = 260,
    TOK_OPENP = 261,
    TOK_CLOSEP = 262,
    TOK_INTEGER = 263,
    TOK_DOUBLE = 264,
    EQ_OP = 265,
    NE_OP = 266,
    LT_OP = 267,
    GT_OP = 268,
    LE_OP = 269,
    GE_OP = 270,
    TOK_AND = 271,
    TOK_OR = 272,
    TOK_IDENT = 273,
    TOK_INICIARCOORDS = 274,
    TOK_LINE = 275,
    TOK_ARC = 276,
    TOK_CIRCULO = 277,
    TOK_QUADRADO = 278,
    TOK_TRIANGULO = 279,
    TOK_RETANGULO = 280,
    TOK_PENTAGONO = 281,
    TOK_LOSANGO = 282,
    TOK_HEXAGONO = 283,
    TOK_TRAPEZIO = 284,
    IFX = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 35 "HCompiler.y" /* yacc.c:355  */

	int nint;
	float nfloat;
	char *ident;
	Node *node;
	Stmts *stmt;

#line 159 "sintatico.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SINTATICO_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 176 "sintatico.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  33
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   360

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  46
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  209

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      33,    34,    40,    38,    35,    39,     2,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
       2,    31,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    57,    57,    61,    62,    66,    67,    68,    69,    77,
      82,   102,   118,   137,   150,   164,   184,   227,   264,   280,
     281,   282,   283,   286,   287,   290,   293,   294,   298,   299,
     303,   304,   305,   306,   307,   308,   309,   313,   314,   315,
     318,   319,   320,   323,   324,   325,   326
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_WHILE", "TOK_IF", "TOK_ELSE",
  "TOK_OPENP", "TOK_CLOSEP", "TOK_INTEGER", "TOK_DOUBLE", "EQ_OP", "NE_OP",
  "LT_OP", "GT_OP", "LE_OP", "GE_OP", "TOK_AND", "TOK_OR", "TOK_IDENT",
  "TOK_INICIARCOORDS", "TOK_LINE", "TOK_ARC", "TOK_CIRCULO",
  "TOK_QUADRADO", "TOK_TRIANGULO", "TOK_RETANGULO", "TOK_PENTAGONO",
  "TOK_LOSANGO", "TOK_HEXAGONO", "TOK_TRAPEZIO", "IFX", "'='", "';'",
  "'('", "')'", "','", "'{'", "'}'", "'+'", "'-'", "'*'", "'/'", "$accept",
  "programa", "stmts", "stmt", "figura", "condblock", "elseblock",
  "whileblock", "logicexpr", "logicterm", "logicfactor", "expr", "term",
  "factor", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    61,    59,    40,    41,    44,   123,   125,    43,    45,
      42,    47
};
# endif

#define YYPACT_NINF -89

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-89)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     244,   -18,   -16,     9,    23,    39,    45,    47,    64,    65,
      70,    71,    75,    84,   118,   244,   -89,   -89,   -89,   -89,
      46,    46,    59,    36,    88,    97,   102,   104,   117,   123,
     132,   136,   138,   -89,   -89,   -89,   -89,   -89,    46,   -14,
     111,   -89,    -3,   -15,   -89,   -12,    59,    27,   110,    59,
      59,    59,    59,    59,    59,    59,    59,   143,   -11,    37,
      46,   115,    46,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,   190,   -20,   -89,   -89,    94,   274,   279,
     281,   286,   288,   293,   295,    59,   -89,   -89,   111,   244,
     -89,    -1,    -1,    -1,    -1,    -1,    -1,   -15,   -15,   -89,
     -89,   244,   174,    59,    59,    59,    59,    59,    59,    59,
      59,   300,    87,   135,   217,   -89,    19,    35,    55,   106,
     109,   139,   164,   167,    59,   -89,   174,   244,   -89,   149,
     160,   161,   162,   169,   172,   176,   187,   189,   -89,   163,
     166,    59,    59,   198,    59,    59,   199,    59,   203,   -89,
      59,   191,   216,    59,   302,   218,    59,   240,    59,   307,
     192,   201,   309,    59,   202,   314,   219,   242,    59,   -89,
     -89,    59,   248,   -89,    59,   -89,   214,   250,   256,   226,
     258,   227,   225,   230,   -89,   241,   228,   245,   252,   251,
      59,   -89,    59,   -89,   316,   321,    59,    59,   264,   266,
     273,   257,    59,   261,   272,   -89,   265,   269,   -89
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     4,     5,     6,     7,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     3,    45,    46,    44,     0,     0,
      27,    29,     0,    39,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     9,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    43,    26,     0,
      28,    31,    32,    35,    36,    33,    34,    37,    38,    40,
      41,     0,    19,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    25,    21,     0,    23,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    22,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    24,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
      10,     0,     0,    16,     0,    17,     0,     0,     0,     0,
       0,     0,     0,     0,    11,     0,     0,     0,     0,     0,
       0,    13,     0,    15,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,     0,     0,    12
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -89,   -89,   -88,   -13,   -89,   -89,   181,   -89,   -17,   255,
     260,   -22,    -8,    24
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    14,    15,    16,    17,    18,   115,    19,    39,    40,
      41,    42,    43,    44
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      47,   112,    34,    60,    45,    60,    60,    63,    64,    65,
      66,    67,    68,   113,    87,    20,    59,    21,    69,    70,
      61,    58,    73,    86,    74,    71,    72,    77,    78,    79,
      80,    81,    82,    83,    84,    69,    70,    69,    70,   139,
      22,    91,    92,    93,    94,    95,    96,    63,    64,    65,
      66,    67,    68,   129,    35,    36,    23,    69,    70,    75,
     102,    97,    98,   111,    37,    69,    70,    35,    36,   130,
      48,    87,    24,    69,    70,    69,    70,    37,    25,    38,
      26,   116,   117,   118,   119,   120,   121,   122,   123,   131,
       1,     2,    46,    69,    70,    99,   100,    27,    28,    34,
      34,   128,   137,    29,    30,     3,     4,     5,    31,     6,
       7,     8,     9,    10,    11,    12,    13,    32,    33,   151,
     152,    49,   154,   155,   125,   157,    34,    62,   159,   103,
      50,   162,    69,    70,   165,    51,   167,    52,     1,     2,
     132,   172,    76,   133,    69,    70,   177,    69,    70,   178,
      53,    89,   180,     3,     4,     5,    54,     6,     7,     8,
       9,    10,    11,    12,    13,    55,     1,     2,   194,    56,
     195,    57,   126,   134,   198,   199,    85,    69,    70,   114,
     204,     3,     4,     5,   140,     6,     7,     8,     9,    10,
      11,    12,    13,     1,     2,   141,   142,   143,   135,   150,
     149,   136,    69,    70,   144,    69,    70,   145,     3,     4,
       5,   146,     6,     7,     8,     9,    10,    11,    12,    13,
       1,     2,   147,   148,   169,   160,   101,    69,    70,    69,
      70,   153,   156,   170,   173,     3,     4,     5,   158,     6,
       7,     8,     9,    10,    11,    12,    13,     1,     2,   181,
     161,   175,   164,   127,    69,    70,    69,    70,   184,   187,
     186,   190,     3,     4,     5,   188,     6,     7,     8,     9,
      10,    11,    12,    13,   166,   189,   176,   191,    69,    70,
      69,    70,   179,   193,   182,   192,    69,    70,    69,    70,
     183,   203,   185,   205,    69,    70,    69,    70,   200,   207,
     201,   208,    69,    70,    69,    70,   206,   138,   202,   104,
      69,    70,    69,    70,   105,    88,   106,    69,    70,    69,
      70,   107,    90,   108,    69,    70,    69,    70,   109,     0,
     110,    69,    70,    69,    70,   124,     0,   163,    69,    70,
      69,    70,   168,     0,   171,    69,    70,    69,    70,   174,
       0,   196,    69,    70,    69,    70,   197,     0,     0,    69,
      70
};

static const yytype_int16 yycheck[] =
{
      22,    89,    15,    17,    21,    17,    17,    10,    11,    12,
      13,    14,    15,   101,    34,    33,    38,    33,    38,    39,
      34,    38,    34,    34,    46,    40,    41,    49,    50,    51,
      52,    53,    54,    55,    56,    38,    39,    38,    39,   127,
      31,    63,    64,    65,    66,    67,    68,    10,    11,    12,
      13,    14,    15,    34,     8,     9,    33,    38,    39,    32,
      73,    69,    70,    85,    18,    38,    39,     8,     9,    34,
      34,    34,    33,    38,    39,    38,    39,    18,    33,    33,
      33,   103,   104,   105,   106,   107,   108,   109,   110,    34,
       3,     4,    33,    38,    39,    71,    72,    33,    33,   112,
     113,   114,   124,    33,    33,    18,    19,    20,    33,    22,
      23,    24,    25,    26,    27,    28,    29,    33,     0,   141,
     142,    33,   144,   145,    37,   147,   139,    16,   150,    35,
      33,   153,    38,    39,   156,    33,   158,    33,     3,     4,
      34,   163,    32,    34,    38,    39,   168,    38,    39,   171,
      33,    36,   174,    18,    19,    20,    33,    22,    23,    24,
      25,    26,    27,    28,    29,    33,     3,     4,   190,    33,
     192,    33,    37,    34,   196,   197,    33,    38,    39,     5,
     202,    18,    19,    20,    35,    22,    23,    24,    25,    26,
      27,    28,    29,     3,     4,    35,    35,    35,    34,    33,
      37,    34,    38,    39,    35,    38,    39,    35,    18,    19,
      20,    35,    22,    23,    24,    25,    26,    27,    28,    29,
       3,     4,    35,    34,    32,    34,    36,    38,    39,    38,
      39,    33,    33,    32,    32,    18,    19,    20,    35,    22,
      23,    24,    25,    26,    27,    28,    29,     3,     4,    35,
      34,    32,    34,    36,    38,    39,    38,    39,    32,    34,
      33,    33,    18,    19,    20,    35,    22,    23,    24,    25,
      26,    27,    28,    29,    34,    34,    34,    32,    38,    39,
      38,    39,    34,    32,    34,    33,    38,    39,    38,    39,
      34,    34,    34,    32,    38,    39,    38,    39,    34,    34,
      34,    32,    38,    39,    38,    39,    34,   126,    35,    35,
      38,    39,    38,    39,    35,    60,    35,    38,    39,    38,
      39,    35,    62,    35,    38,    39,    38,    39,    35,    -1,
      35,    38,    39,    38,    39,    35,    -1,    35,    38,    39,
      38,    39,    35,    -1,    35,    38,    39,    38,    39,    35,
      -1,    35,    38,    39,    38,    39,    35,    -1,    -1,    38,
      39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    18,    19,    20,    22,    23,    24,    25,
      26,    27,    28,    29,    43,    44,    45,    46,    47,    49,
      33,    33,    31,    33,    33,    33,    33,    33,    33,    33,
      33,    33,    33,     0,    45,     8,     9,    18,    33,    50,
      51,    52,    53,    54,    55,    50,    33,    53,    34,    33,
      33,    33,    33,    33,    33,    33,    33,    33,    50,    53,
      17,    34,    16,    10,    11,    12,    13,    14,    15,    38,
      39,    40,    41,    34,    53,    32,    32,    53,    53,    53,
      53,    53,    53,    53,    53,    33,    34,    34,    51,    36,
      52,    53,    53,    53,    53,    53,    53,    54,    54,    55,
      55,    36,    45,    35,    35,    35,    35,    35,    35,    35,
      35,    53,    44,    44,     5,    48,    53,    53,    53,    53,
      53,    53,    53,    53,    35,    37,    37,    36,    45,    34,
      34,    34,    34,    34,    34,    34,    34,    53,    48,    44,
      35,    35,    35,    35,    35,    35,    35,    35,    34,    37,
      33,    53,    53,    33,    53,    53,    33,    53,    35,    53,
      34,    34,    53,    35,    34,    53,    34,    53,    35,    32,
      32,    35,    53,    32,    35,    32,    34,    53,    53,    34,
      53,    35,    34,    34,    32,    34,    33,    34,    35,    34,
      33,    32,    33,    32,    53,    53,    35,    35,    53,    53,
      34,    34,    35,    34,    53,    32,    34,    34,    32
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    45,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    47,
      47,    47,    47,    48,    48,    49,    50,    50,    51,    51,
      52,    52,    52,    52,    52,    52,    52,    53,    53,    53,
      54,    54,    54,    55,    55,    55,    55
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     4,     4,
      11,    13,    23,    15,    21,    15,    11,    11,    11,     5,
       6,     7,     8,     2,     4,     7,     3,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 57 "HCompiler.y" /* yacc.c:1646  */
    { Program p;
                      p.generate((yyvsp[0].stmt)); }
#line 1403 "sintatico.c" /* yacc.c:1646  */
    break;

  case 3:
#line 61 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.stmt)->append((yyvsp[0].node)); }
#line 1409 "sintatico.c" /* yacc.c:1646  */
    break;

  case 4:
#line 62 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Stmts((yyvsp[0].node)); }
#line 1415 "sintatico.c" /* yacc.c:1646  */
    break;

  case 5:
#line 66 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].stmt); }
#line 1421 "sintatico.c" /* yacc.c:1646  */
    break;

  case 6:
#line 67 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new Capsule((yyvsp[0].node)); }
#line 1427 "sintatico.c" /* yacc.c:1646  */
    break;

  case 7:
#line 68 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new Capsule((yyvsp[0].node)); }
#line 1433 "sintatico.c" /* yacc.c:1646  */
    break;

  case 8:
#line 69 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new Variable((yyvsp[-3].ident), (yyvsp[-1].node)); }
#line 1439 "sintatico.c" /* yacc.c:1646  */
    break;

  case 9:
#line 78 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Stmts(new Variable("x",new Float(0)));	
		  (yyval.stmt)->append(new Variable("y", new Float(0)));
		  (yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));}
#line 1447 "sintatico.c" /* yacc.c:1646  */
    break;

  case 10:
#line 84 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new Variable("x",(yyvsp[-7].node)));
		(yyval.stmt)->append(new Variable("y",(yyvsp[-5].node))); 
		(yyval.stmt)->append(new If(new CmpOp(new Load("x"), GT_OP, new Int16(4000)), ErroLimite() , NULL));

	

		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '+', (yyvsp[-2].node)), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'+',(yyvsp[-2].node))));
		(yyval.stmt)->append(new LinearMove(new Load("x"),new BinaryOp(new Load("y"), '+', (yyvsp[-2].node)), new Float(0)));
		(yyval.stmt)->append(new Variable("y",new BinaryOp(new Load("y"),'+',(yyvsp[-2].node))));
		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '-', (yyvsp[-2].node)), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'-',(yyvsp[-2].node))));
		(yyval.stmt)->append(new LinearMove(new Load("x"),new BinaryOp(new Load("y"), '-', (yyvsp[-2].node)), new Float(0)));
		(yyval.stmt)->append(new Variable("y",new BinaryOp(new Load("y"),'-',(yyvsp[-2].node)))); }
#line 1469 "sintatico.c" /* yacc.c:1646  */
    break;

  case 11:
#line 103 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new Variable("x",(yyvsp[-9].node)));
		(yyval.stmt)->append(new Variable("y",(yyvsp[-7].node)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '+', (yyvsp[-4].node)), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'+',(yyvsp[-4].node))));
		(yyval.stmt)->append(new LinearMove(new Load("x"),new BinaryOp(new Load("y"), '+', (yyvsp[-2].node)), new Float(0)));
		(yyval.stmt)->append(new Variable("y",new BinaryOp(new Load("y"),'+',(yyvsp[-2].node))));
		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '-', (yyvsp[-4].node)), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'-',(yyvsp[-4].node))));
		(yyval.stmt)->append(new LinearMove(new Load("x"),new BinaryOp(new Load("y"), '-', (yyvsp[-2].node)), new Float(0)));
		(yyval.stmt)->append(new Variable("y",new BinaryOp(new Load("y"),'-',(yyvsp[-2].node)))); }
#line 1487 "sintatico.c" /* yacc.c:1646  */
    break;

  case 12:
#line 119 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new Variable("x",(yyvsp[-18].node))); 
		(yyval.stmt)->append(new Variable("y",(yyvsp[-16].node))); 
		(yyval.stmt)->append(new Variable("x2",(yyvsp[-8].node))); 
		(yyval.stmt)->append(new Variable("y2",(yyvsp[-6].node)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '+', (yyvsp[-13].node)), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'+',(yyvsp[-13].node))));
		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x2"), '+', (yyvsp[-3].node)), new Load("y2"), new Float(0))); 
		(yyval.stmt)->append(new Variable("x2",new BinaryOp(new Load("x2"),'+',(yyvsp[-3].node))));
		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x2"),'-',(yyvsp[-3].node)), new Load("y2"), new Float(0))); 
		(yyval.stmt)->append(new Variable("x2",new BinaryOp(new Load("x2"),'-',(yyvsp[-3].node))));
		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '-', (yyvsp[-13].node)), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'-',(yyvsp[-13].node))));}
#line 1507 "sintatico.c" /* yacc.c:1646  */
    break;

  case 13:
#line 138 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new Variable("x",(yyvsp[-11].node))); 
		(yyval.stmt)->append(new Variable("y",(yyvsp[-9].node))); 
		(yyval.stmt)->append(new Variable("x2",(yyvsp[-5].node))); 
		(yyval.stmt)->append(new Variable("y2",(yyvsp[-3].node)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new LinearMove(new Load("x2"), new Load("y2"), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new Load("x2")));
		(yyval.stmt)->append(new Variable("y",new Load("y2")));}
#line 1522 "sintatico.c" /* yacc.c:1646  */
    break;

  case 14:
#line 151 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new Variable("x",(yyvsp[-17].node))); 
		(yyval.stmt)->append(new Variable("y",(yyvsp[-15].node))); 
		(yyval.stmt)->append(new Variable("x2",(yyvsp[-11].node))); 
		(yyval.stmt)->append(new Variable("y2",(yyvsp[-9].node)));
		(yyval.stmt)->append(new Variable("x3",(yyvsp[-5].node)));
		(yyval.stmt)->append(new Variable("y3",(yyvsp[-3].node)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new LinearMove(new Load("x2"), new Load("y2"), new Float(0)));
		(yyval.stmt)->append(new LinearMove(new Load("x3"), new Load("y3"), new Float(0)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("x"), new Float(0)));}
#line 1539 "sintatico.c" /* yacc.c:1646  */
    break;

  case 15:
#line 165 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new Variable("x",(yyvsp[-11].node))); 
		(yyval.stmt)->append(new Variable("y",(yyvsp[-9].node))); 
		(yyval.stmt)->append(new Variable("x2",(yyvsp[-5].node))); 
		(yyval.stmt)->append(new Variable("y2",(yyvsp[-3].node)));
		(yyval.stmt)->append(new Variable("XDiferenca",new BinaryOp((yyvsp[-5].node),'-',(yyvsp[-11].node))));
		(yyval.stmt)->append(new Variable("YDiferenca",new BinaryOp((yyvsp[-3].node),'-',(yyvsp[-9].node))));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new LinearMove(new Load("x2"), new Load("y2"), new Float(0)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new BinaryOp(new Load("y2"), '+', new Load("YDiferenca")), new Float(0))); 
		(yyval.stmt)->append(new Variable("y2",new BinaryOp(new Load("y2"),'+',new Load("YDiferenca"))));
		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"),'-',new Load("XDiferenca")), new BinaryOp(new Load("y2"), '-', new Load("YDiferenca")), new Float(0)));
		(yyval.stmt)->append(new Variable("y2",new BinaryOp(new Load("y2"),'-',new Load("YDiferenca"))));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x2"),'-',new Load("XDiferenca"))));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));}
#line 1560 "sintatico.c" /* yacc.c:1646  */
    break;

  case 16:
#line 186 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new Variable("x",(yyvsp[-7].node)));
		(yyval.stmt)->append(new Variable("y",(yyvsp[-5].node))); 
		(yyval.stmt)->append(new Variable("MetadeDoTamanho",new BinaryOp((yyvsp[-2].node),'/',new Float(2))));
		(yyval.stmt)->append(new Variable("OtantoPraVoltarPraMetade",new BinaryOp((yyvsp[-2].node),'+',new Load("MetadeDoTamanho"))));
		
		//$$->append(new Variable("LadoDeCima",new BinaryOp(new Load("x"),'+',new BinaryOp($9,'/',new Float(2)))));
		
		
		


		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));

		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '+', (yyvsp[-2].node)), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'+',(yyvsp[-2].node))));

		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '+', (yyvsp[-2].node)), new BinaryOp(new Load("y"), '+', (yyvsp[-2].node)), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'+',(yyvsp[-2].node))));
		(yyval.stmt)->append(new Variable("y",new BinaryOp(new Load("y"),'+',(yyvsp[-2].node))));

		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '-', new Load("OtantoPraVoltarPraMetade")), new BinaryOp(new Load("y"), '+', (yyvsp[-2].node)), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'-',new Load("OtantoPraVoltarPraMetade"))));
		(yyval.stmt)->append(new Variable("y",new BinaryOp(new Load("y"),'+',(yyvsp[-2].node))));




		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '-', new Load("OtantoPraVoltarPraMetade")), new BinaryOp(new Load("y"), '-', (yyvsp[-2].node)), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'-',new Load("OtantoPraVoltarPraMetade"))));
		(yyval.stmt)->append(new Variable("y",new BinaryOp(new Load("y"),'-',(yyvsp[-2].node))));

		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '+', (yyvsp[-2].node)), new BinaryOp(new Load("y"), '-', (yyvsp[-2].node)), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'+',(yyvsp[-2].node))));
		(yyval.stmt)->append(new Variable("y",new BinaryOp(new Load("y"),'-',(yyvsp[-2].node))));}
#line 1601 "sintatico.c" /* yacc.c:1646  */
    break;

  case 17:
#line 229 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new Variable("x",(yyvsp[-7].node)));
		(yyval.stmt)->append(new Variable("y",(yyvsp[-5].node))); 
		

	

		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		(yyval.stmt)->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));

		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '+', (yyvsp[-2].node)), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'+',(yyvsp[-2].node))));

		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '+', (yyvsp[-2].node)), new BinaryOp(new Load("y"), '+', (yyvsp[-2].node)), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'+',(yyvsp[-2].node))));
		(yyval.stmt)->append(new Variable("y",new BinaryOp(new Load("y"),'+',(yyvsp[-2].node))));

		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '-', (yyvsp[-2].node)), new BinaryOp(new Load("y"), '+', (yyvsp[-2].node)), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'-',(yyvsp[-2].node))));
		(yyval.stmt)->append(new Variable("y",new BinaryOp(new Load("y"),'+',(yyvsp[-2].node))));


		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '-', (yyvsp[-2].node)), new Load("y"), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'-',(yyvsp[-2].node))));

		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '-', (yyvsp[-2].node)), new BinaryOp(new Load("y"), '-', (yyvsp[-2].node)), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'-',(yyvsp[-2].node))));
		(yyval.stmt)->append(new Variable("y",new BinaryOp(new Load("y"),'-',(yyvsp[-2].node))));

		(yyval.stmt)->append(new LinearMove(new BinaryOp(new Load("x"), '+', (yyvsp[-2].node)), new BinaryOp(new Load("y"), '-', (yyvsp[-2].node)), new Float(0)));
		(yyval.stmt)->append(new Variable("x",new BinaryOp(new Load("x"),'+',(yyvsp[-2].node))));
		(yyval.stmt)->append(new Variable("y",new BinaryOp(new Load("y"),'-',(yyvsp[-2].node))));}
#line 1638 "sintatico.c" /* yacc.c:1646  */
    break;

  case 18:
#line 265 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1))); 
   (yyval.stmt)->append(new LinearMove((yyvsp[-7].node), (yyvsp[-5].node), new Float(1)));
   (yyval.stmt)->append(new LinearMove((yyvsp[-7].node), (yyvsp[-5].node), new Float(0)));
   (yyval.stmt)->append((new Variable("x",(yyvsp[-7].node))));
   (yyval.stmt)->append((new Variable("y",(yyvsp[-5].node))));
   (yyval.stmt)->append(new ArcMove((yyvsp[-7].node), (yyvsp[-5].node), new Float(0), new Float(0) , (yyvsp[-2].node)));
						 
}
#line 1651 "sintatico.c" /* yacc.c:1646  */
    break;

  case 19:
#line 280 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new If((yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1657 "sintatico.c" /* yacc.c:1646  */
    break;

  case 20:
#line 281 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new If((yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1663 "sintatico.c" /* yacc.c:1646  */
    break;

  case 21:
#line 282 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new If((yyvsp[-4].node), (yyvsp[-1].stmt), NULL); }
#line 1669 "sintatico.c" /* yacc.c:1646  */
    break;

  case 22:
#line 283 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new If((yyvsp[-5].node), (yyvsp[-2].stmt), (yyvsp[0].node)); }
#line 1675 "sintatico.c" /* yacc.c:1646  */
    break;

  case 23:
#line 286 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1681 "sintatico.c" /* yacc.c:1646  */
    break;

  case 24:
#line 287 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].stmt); }
#line 1687 "sintatico.c" /* yacc.c:1646  */
    break;

  case 25:
#line 290 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new While((yyvsp[-4].node), (yyvsp[-1].stmt)); }
#line 1693 "sintatico.c" /* yacc.c:1646  */
    break;

  case 26:
#line 293 "HCompiler.y" /* yacc.c:1646  */
    {		        }
#line 1699 "sintatico.c" /* yacc.c:1646  */
    break;

  case 27:
#line 294 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new Capsule((yyvsp[0].node)); }
#line 1705 "sintatico.c" /* yacc.c:1646  */
    break;

  case 28:
#line 298 "HCompiler.y" /* yacc.c:1646  */
    {		        }
#line 1711 "sintatico.c" /* yacc.c:1646  */
    break;

  case 29:
#line 299 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new Capsule((yyvsp[0].node)); }
#line 1717 "sintatico.c" /* yacc.c:1646  */
    break;

  case 30:
#line 303 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new Capsule((yyvsp[-1].node)); }
#line 1723 "sintatico.c" /* yacc.c:1646  */
    break;

  case 31:
#line 304 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new CmpOp((yyvsp[-2].node), EQ_OP, (yyvsp[0].node)); }
#line 1729 "sintatico.c" /* yacc.c:1646  */
    break;

  case 32:
#line 305 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new CmpOp((yyvsp[-2].node), NE_OP, (yyvsp[0].node)); }
#line 1735 "sintatico.c" /* yacc.c:1646  */
    break;

  case 33:
#line 306 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new CmpOp((yyvsp[-2].node), LE_OP, (yyvsp[0].node)); }
#line 1741 "sintatico.c" /* yacc.c:1646  */
    break;

  case 34:
#line 307 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new CmpOp((yyvsp[-2].node), GE_OP, (yyvsp[0].node)); }
#line 1747 "sintatico.c" /* yacc.c:1646  */
    break;

  case 35:
#line 308 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new CmpOp((yyvsp[-2].node), LT_OP, (yyvsp[0].node)); }
#line 1753 "sintatico.c" /* yacc.c:1646  */
    break;

  case 36:
#line 309 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new CmpOp((yyvsp[-2].node), GT_OP, (yyvsp[0].node)); }
#line 1759 "sintatico.c" /* yacc.c:1646  */
    break;

  case 37:
#line 313 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new BinaryOp((yyvsp[-2].node), '+', (yyvsp[0].node)); }
#line 1765 "sintatico.c" /* yacc.c:1646  */
    break;

  case 38:
#line 314 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new BinaryOp((yyvsp[-2].node), '-', (yyvsp[0].node)); }
#line 1771 "sintatico.c" /* yacc.c:1646  */
    break;

  case 39:
#line 315 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1777 "sintatico.c" /* yacc.c:1646  */
    break;

  case 40:
#line 318 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new BinaryOp((yyvsp[-2].node), '*', (yyvsp[0].node)); }
#line 1783 "sintatico.c" /* yacc.c:1646  */
    break;

  case 41:
#line 319 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new BinaryOp((yyvsp[-2].node), '/', (yyvsp[0].node)); }
#line 1789 "sintatico.c" /* yacc.c:1646  */
    break;

  case 42:
#line 320 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1795 "sintatico.c" /* yacc.c:1646  */
    break;

  case 43:
#line 323 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1801 "sintatico.c" /* yacc.c:1646  */
    break;

  case 44:
#line 324 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new Load((yyvsp[0].ident)); }
#line 1807 "sintatico.c" /* yacc.c:1646  */
    break;

  case 45:
#line 325 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new Float((yyvsp[0].nint)); }
#line 1813 "sintatico.c" /* yacc.c:1646  */
    break;

  case 46:
#line 326 "HCompiler.y" /* yacc.c:1646  */
    { (yyval.node) = new Float((yyvsp[0].nfloat)); }
#line 1819 "sintatico.c" /* yacc.c:1646  */
    break;


#line 1823 "sintatico.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 330 "HCompiler.y" /* yacc.c:1906  */


// codigo C 

extern int yylineno;
extern char *yytext;
extern char *build_filename;

int yyerror(const char *s)
{
	fprintf(stderr, "%s:%d: error: %s %s\n", 
		build_filename, yylineno, s, yytext);
	exit(1);
}

extern "C" int yywrap() {
	return 1;
}

/*
int main(int argc, char *argv[]) {
	if (argc > 1) {
		yyin = fopen(argv[1], "r");
	}
	yyparse();
	if (yyin)
		fclose(yyin);
}
*/
