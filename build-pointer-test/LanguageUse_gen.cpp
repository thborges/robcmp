/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 12 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"

  #include <stdlib.h>
  #include <limits.h>
  #define SCANNER_OR_VISITOR
  #include "Header.h"

#line 75 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"

/* Substitute the variable and function names.  */
#define yyparse         USEparse
#define yylex           USElex
#define yyerror         USEerror
#define yydebug         USEdebug
#define yynerrs         USEnerrs


# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "LanguageUse_gen.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_VOID = 3,                   /* TOK_VOID  */
  YYSYMBOL_TOK_RETURN = 4,                 /* TOK_RETURN  */
  YYSYMBOL_TOK_REGISTER = 5,               /* TOK_REGISTER  */
  YYSYMBOL_TOK_AT = 6,                     /* TOK_AT  */
  YYSYMBOL_TOK_VOLATILE = 7,               /* TOK_VOLATILE  */
  YYSYMBOL_TOK_CONST = 8,                  /* TOK_CONST  */
  YYSYMBOL_TOK_ASM = 9,                    /* TOK_ASM  */
  YYSYMBOL_TOK_IF = 10,                    /* TOK_IF  */
  YYSYMBOL_TOK_ELSE = 11,                  /* TOK_ELSE  */
  YYSYMBOL_TOK_LOOP = 12,                  /* TOK_LOOP  */
  YYSYMBOL_TOK_WHILE = 13,                 /* TOK_WHILE  */
  YYSYMBOL_TOK_AND = 14,                   /* TOK_AND  */
  YYSYMBOL_TOK_OR = 15,                    /* TOK_OR  */
  YYSYMBOL_TOK_IDENTIFIER = 16,            /* TOK_IDENTIFIER  */
  YYSYMBOL_TOK_USE_IDENTIFIER = 17,        /* TOK_USE_IDENTIFIER  */
  YYSYMBOL_TOK_CHAR = 18,                  /* TOK_CHAR  */
  YYSYMBOL_TOK_UINTEGER = 19,              /* TOK_UINTEGER  */
  YYSYMBOL_TOK_FLOAT = 20,                 /* TOK_FLOAT  */
  YYSYMBOL_TOK_DOUBLE = 21,                /* TOK_DOUBLE  */
  YYSYMBOL_TOK_LDOUBLE = 22,               /* TOK_LDOUBLE  */
  YYSYMBOL_TOK_INTEGER = 23,               /* TOK_INTEGER  */
  YYSYMBOL_TOK_STRING = 24,                /* TOK_STRING  */
  YYSYMBOL_TOK_TRUE = 25,                  /* TOK_TRUE  */
  YYSYMBOL_TOK_FALSE = 26,                 /* TOK_FALSE  */
  YYSYMBOL_TOK_FINT8 = 27,                 /* TOK_FINT8  */
  YYSYMBOL_TOK_FINT16 = 28,                /* TOK_FINT16  */
  YYSYMBOL_TOK_FINT32 = 29,                /* TOK_FINT32  */
  YYSYMBOL_TOK_FINT64 = 30,                /* TOK_FINT64  */
  YYSYMBOL_TOK_FFLOAT = 31,                /* TOK_FFLOAT  */
  YYSYMBOL_TOK_FDOUBLE = 32,               /* TOK_FDOUBLE  */
  YYSYMBOL_TOK_FCHAR = 33,                 /* TOK_FCHAR  */
  YYSYMBOL_TOK_FLONG = 34,                 /* TOK_FLONG  */
  YYSYMBOL_TOK_FUNSIGNED = 35,             /* TOK_FUNSIGNED  */
  YYSYMBOL_TOK_FBOOL = 36,                 /* TOK_FBOOL  */
  YYSYMBOL_TOK_TYPE = 37,                  /* TOK_TYPE  */
  YYSYMBOL_TOK_INTF = 38,                  /* TOK_INTF  */
  YYSYMBOL_TOK_IMPL = 39,                  /* TOK_IMPL  */
  YYSYMBOL_TOK_USE = 40,                   /* TOK_USE  */
  YYSYMBOL_TOK_ENUM = 41,                  /* TOK_ENUM  */
  YYSYMBOL_TOK_BIND = 42,                  /* TOK_BIND  */
  YYSYMBOL_TOK_TO = 43,                    /* TOK_TO  */
  YYSYMBOL_TOK_SINGLETON = 44,             /* TOK_SINGLETON  */
  YYSYMBOL_TOK_TRANSIENT = 45,             /* TOK_TRANSIENT  */
  YYSYMBOL_TOK_QUANDO = 46,                /* TOK_QUANDO  */
  YYSYMBOL_TOK_ESTA = 47,                  /* TOK_ESTA  */
  YYSYMBOL_EQ_OP = 48,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 49,                     /* NE_OP  */
  YYSYMBOL_GE_OP = 50,                     /* GE_OP  */
  YYSYMBOL_LE_OP = 51,                     /* LE_OP  */
  YYSYMBOL_GT_OP = 52,                     /* GT_OP  */
  YYSYMBOL_LT_OP = 53,                     /* LT_OP  */
  YYSYMBOL_TOK_LSHIFT = 54,                /* TOK_LSHIFT  */
  YYSYMBOL_TOK_RSHIFT = 55,                /* TOK_RSHIFT  */
  YYSYMBOL_TOK_MUL_ASSIGN = 56,            /* TOK_MUL_ASSIGN  */
  YYSYMBOL_TOK_INLINE = 57,                /* TOK_INLINE  */
  YYSYMBOL_TOK_NOINLINE = 58,              /* TOK_NOINLINE  */
  YYSYMBOL_TOK_WEAK = 59,                  /* TOK_WEAK  */
  YYSYMBOL_TOK_SECTION = 60,               /* TOK_SECTION  */
  YYSYMBOL_TOK_NAKED = 61,                 /* TOK_NAKED  */
  YYSYMBOL_TOK_SIGNAL = 62,                /* TOK_SIGNAL  */
  YYSYMBOL_TOK_DEBUGONLY = 63,             /* TOK_DEBUGONLY  */
  YYSYMBOL_TOK_NOOPT = 64,                 /* TOK_NOOPT  */
  YYSYMBOL_65_ = 65,                       /* ';'  */
  YYSYMBOL_66_ = 66,                       /* '{'  */
  YYSYMBOL_67_ = 67,                       /* '}'  */
  YYSYMBOL_68_ = 68,                       /* ','  */
  YYSYMBOL_69_ = 69,                       /* '='  */
  YYSYMBOL_70_ = 70,                       /* '-'  */
  YYSYMBOL_71_ = 71,                       /* '('  */
  YYSYMBOL_72_ = 72,                       /* ')'  */
  YYSYMBOL_73_ = 73,                       /* '*'  */
  YYSYMBOL_74_ = 74,                       /* '['  */
  YYSYMBOL_75_ = 75,                       /* ']'  */
  YYSYMBOL_76_ = 76,                       /* ':'  */
  YYSYMBOL_77_ = 77,                       /* '~'  */
  YYSYMBOL_YYACCEPT = 78,                  /* $accept  */
  YYSYMBOL_programa = 79,                  /* programa  */
  YYSYMBOL_globals = 80,                   /* globals  */
  YYSYMBOL_global = 81,                    /* global  */
  YYSYMBOL_use = 82,                       /* use  */
  YYSYMBOL_enum = 83,                      /* enum  */
  YYSYMBOL_enum_items = 84,                /* enum_items  */
  YYSYMBOL_enum_item = 85,                 /* enum_item  */
  YYSYMBOL_function = 86,                  /* function  */
  YYSYMBOL_function_decl = 87,             /* function_decl  */
  YYSYMBOL_function_impl = 88,             /* function_impl  */
  YYSYMBOL_function_attributes = 89,       /* function_attributes  */
  YYSYMBOL_function_attribute = 90,        /* function_attribute  */
  YYSYMBOL_qualifier = 91,                 /* qualifier  */
  YYSYMBOL_function_params = 92,           /* function_params  */
  YYSYMBOL_function_param = 93,            /* function_param  */
  YYSYMBOL_pointer_type = 94,              /* pointer_type  */
  YYSYMBOL_register = 95,                  /* register  */
  YYSYMBOL_interface = 96,                 /* interface  */
  YYSYMBOL_interface_decls = 97,           /* interface_decls  */
  YYSYMBOL_interface_impl = 98,            /* interface_impl  */
  YYSYMBOL_type = 99,                      /* type  */
  YYSYMBOL_type_impls = 100,               /* type_impls  */
  YYSYMBOL_type_stmts = 101,               /* type_stmts  */
  YYSYMBOL_type_stmt = 102,                /* type_stmt  */
  YYSYMBOL_simplevar_decl = 103,           /* simplevar_decl  */
  YYSYMBOL_array = 104,                    /* array  */
  YYSYMBOL_matrix = 105,                   /* matrix  */
  YYSYMBOL_melements = 106,                /* melements  */
  YYSYMBOL_melement = 107,                 /* melement  */
  YYSYMBOL_relements = 108,                /* relements  */
  YYSYMBOL_elements = 109,                 /* elements  */
  YYSYMBOL_element = 110,                  /* element  */
  YYSYMBOL_const_expr = 111,               /* const_expr  */
  YYSYMBOL_unary = 112,                    /* unary  */
  YYSYMBOL_expr = 113,                     /* expr  */
  YYSYMBOL_cast = 114,                     /* cast  */
  YYSYMBOL_constructor = 115,              /* constructor  */
  YYSYMBOL_ignore_param = 116,             /* ignore_param  */
  YYSYMBOL_ignore_p = 117,                 /* ignore_p  */
  YYSYMBOL_stmts_rec = 118,                /* stmts_rec  */
  YYSYMBOL_stmts = 119,                    /* stmts  */
  YYSYMBOL_ignore_stmt = 120,              /* ignore_stmt  */
  YYSYMBOL_ignore = 121                    /* ignore  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

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
# define YYCOPY_NEEDED 1
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  32
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   293

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  115
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  220

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   319


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      71,    72,    73,     2,    68,    70,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    76,    65,
       2,    69,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    74,     2,    75,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,     2,    67,    77,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   119,   119,   125,   131,   139,   140,   141,   142,   143,
     144,   145,   147,   154,   159,   164,   168,   173,   178,   182,
     186,   190,   194,   194,   196,   202,   208,   218,   228,   233,
     238,   243,   244,   245,   246,   247,   248,   249,   250,   252,
     253,   255,   260,   266,   271,   275,   279,   283,   287,   291,
     296,   300,   304,   309,   314,   321,   327,   333,   338,   343,
     348,   354,   355,   356,   357,   358,   360,   361,   362,   364,
     365,   367,   372,   378,   379,   381,   383,   385,   389,   390,
     392,   393,   394,   395,   396,   397,   398,   399,   400,   403,
     404,   407,   408,   409,   412,   419,   426,   427,   432,   433,
     435,   436,   438,   439,   441,   442,   443,   448,   449,   450,
     451,   452,   453,   454,   455,   456
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOK_VOID",
  "TOK_RETURN", "TOK_REGISTER", "TOK_AT", "TOK_VOLATILE", "TOK_CONST",
  "TOK_ASM", "TOK_IF", "TOK_ELSE", "TOK_LOOP", "TOK_WHILE", "TOK_AND",
  "TOK_OR", "TOK_IDENTIFIER", "TOK_USE_IDENTIFIER", "TOK_CHAR",
  "TOK_UINTEGER", "TOK_FLOAT", "TOK_DOUBLE", "TOK_LDOUBLE", "TOK_INTEGER",
  "TOK_STRING", "TOK_TRUE", "TOK_FALSE", "TOK_FINT8", "TOK_FINT16",
  "TOK_FINT32", "TOK_FINT64", "TOK_FFLOAT", "TOK_FDOUBLE", "TOK_FCHAR",
  "TOK_FLONG", "TOK_FUNSIGNED", "TOK_FBOOL", "TOK_TYPE", "TOK_INTF",
  "TOK_IMPL", "TOK_USE", "TOK_ENUM", "TOK_BIND", "TOK_TO", "TOK_SINGLETON",
  "TOK_TRANSIENT", "TOK_QUANDO", "TOK_ESTA", "EQ_OP", "NE_OP", "GE_OP",
  "LE_OP", "GT_OP", "LT_OP", "TOK_LSHIFT", "TOK_RSHIFT", "TOK_MUL_ASSIGN",
  "TOK_INLINE", "TOK_NOINLINE", "TOK_WEAK", "TOK_SECTION", "TOK_NAKED",
  "TOK_SIGNAL", "TOK_DEBUGONLY", "TOK_NOOPT", "';'", "'{'", "'}'", "','",
  "'='", "'-'", "'('", "')'", "'*'", "'['", "']'", "':'", "'~'", "$accept",
  "programa", "globals", "global", "use", "enum", "enum_items",
  "enum_item", "function", "function_decl", "function_impl",
  "function_attributes", "function_attribute", "qualifier",
  "function_params", "function_param", "pointer_type", "register",
  "interface", "interface_decls", "interface_impl", "type", "type_impls",
  "type_stmts", "type_stmt", "simplevar_decl", "array", "matrix",
  "melements", "melement", "relements", "elements", "element",
  "const_expr", "unary", "expr", "cast", "constructor", "ignore_param",
  "ignore_p", "stmts_rec", "stmts", "ignore_stmt", "ignore", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-165)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-102)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     190,    71,  -165,  -165,   106,    80,    88,    40,    91,   147,
     190,  -165,  -165,  -165,  -165,  -165,  -165,    96,   138,  -165,
    -165,  -165,    95,   165,   117,    59,  -165,    64,   128,   134,
     146,   142,  -165,  -165,   150,   160,   168,  -165,   234,   235,
     179,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,   119,
     143,   143,  -165,  -165,  -165,  -165,  -165,  -165,  -165,   236,
      85,    -5,  -165,  -165,   237,  -165,   235,   143,    54,   -13,
    -165,   238,     2,   130,   103,  -165,   180,   137,  -165,   181,
    -165,  -165,  -165,   135,    37,  -165,  -165,    96,   239,  -165,
      -1,  -165,   193,    -8,  -165,  -165,   243,    -4,   191,   154,
    -165,   104,   196,  -165,   187,   235,   185,  -165,  -165,  -165,
    -165,  -165,   192,  -165,   156,  -165,   197,   242,  -165,   130,
     244,    85,   250,   198,   252,   205,   200,  -165,  -165,  -165,
     201,   202,  -165,  -165,    -6,  -165,   237,   185,  -165,    -7,
    -165,  -165,  -165,  -165,   258,  -165,  -165,  -165,  -165,   125,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,    42,  -165,   235,
     209,  -165,   235,   235,   235,  -165,  -165,   253,  -165,   144,
    -165,   203,  -165,  -165,    19,   185,  -165,   105,    85,   112,
     114,   115,  -165,  -165,    19,   261,    66,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,   212,    35,  -165,  -165,
    -165,   185,   151,   185,   185,   185,   213,  -165,  -165,   225,
    -165,  -165,   148,  -165,   149,   -46,   -27,  -165,   107,  -165
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    40,    39,     0,     0,     0,     0,     0,     0,
       2,     4,     5,    10,     9,    22,    23,     0,     0,     8,
       6,     7,     0,     0,     0,     0,    46,     0,     0,     0,
       0,     0,     1,     3,     0,     0,     0,    11,     0,    43,
       0,    82,    81,    85,    86,    87,    80,    83,    84,     0,
       0,     0,    67,    68,    91,    88,    66,    92,    93,     0,
       0,     0,    13,    14,     0,    12,    43,     0,     0,     0,
      42,     0,     0,     0,     0,    72,    74,     0,    77,    79,
      89,    90,    58,     0,     0,    65,    63,     0,     0,    64,
       0,    60,     0,     0,    51,    53,     0,     0,    21,     0,
      17,     0,     0,    44,     0,     0,    30,    45,    97,    99,
      98,    95,     0,    96,     0,    70,     0,     0,    69,     0,
       0,     0,     0,     0,     0,     0,     0,    56,    59,    61,
       0,     0,    50,    52,     0,    15,     0,    30,    49,     0,
      41,    32,    33,    31,     0,    34,    35,    36,    37,     0,
      29,    94,    75,    71,    73,    76,    78,     0,    57,    43,
       0,    62,    43,    43,    43,    20,    18,     0,    16,     0,
      47,     0,    38,    24,     0,     0,    55,     0,     0,     0,
       0,     0,    19,    25,     0,     0,     0,   109,   111,   110,
     115,   112,   113,   114,   108,   107,     0,     0,   103,   104,
      28,    30,     0,    30,    30,    30,     0,    48,   106,     0,
      26,   102,     0,    54,     0,     0,     0,    27,     0,   105
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -165,  -165,  -165,   271,  -165,    24,  -165,   152,  -165,   -45,
     124,  -132,   108,   133,   -64,   177,     0,  -165,  -165,  -165,
    -165,  -165,  -165,   -84,   -89,     4,  -165,  -165,  -165,   169,
    -165,   211,   167,    38,  -165,   262,  -165,  -165,  -165,  -165,
     109,    81,  -164,  -165
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     9,    10,    11,    12,    85,    99,   100,    14,    15,
      86,   149,   150,    87,    69,    70,    71,    19,    20,    97,
      89,    21,    83,    90,    91,    92,    52,    53,    74,    75,
      76,    77,    78,    54,    55,    79,    57,    58,   112,   113,
     196,   197,   198,   199
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      18,   128,   101,   108,    22,   169,     2,     3,   130,   170,
      18,    93,    93,   165,    22,    84,    95,   166,   109,   173,
     186,    35,   175,   187,    13,   110,   188,   189,   190,   191,
     192,   193,   194,   211,    13,   195,   186,   157,   183,   187,
       8,   175,   188,   189,   190,   191,   192,   193,   194,     2,
       3,   195,   133,   123,   211,   105,    29,    30,    84,   106,
      88,    96,    94,   132,   167,    26,   127,   171,   128,   212,
     103,   214,   215,   216,   111,    40,   124,    41,    42,    43,
      44,    45,    46,     8,    47,    48,  -100,    23,    80,    81,
      88,   125,     2,     3,   202,   177,    27,    96,   179,   180,
     181,    84,  -101,    59,    28,   102,    25,    31,   186,   176,
      26,   187,    34,   128,   188,   189,   190,   191,   192,   193,
     194,    88,    24,   195,    16,    49,     8,    26,   104,    50,
      60,   208,   209,    17,    16,    40,    51,    41,    42,    43,
      44,    45,    46,    17,    47,    48,    40,    32,    41,    42,
      43,    44,    45,    46,    36,    47,    48,    88,     2,     3,
      37,    41,    42,    43,    44,    45,    46,    84,    47,    48,
     115,   116,   105,   105,   219,    25,   137,   201,    88,    26,
     105,    38,   105,   105,   203,    73,   204,   205,    39,    50,
     173,   174,     8,   175,    61,     1,    51,     2,     3,    62,
      50,   121,    88,   122,   118,   119,     4,    51,    64,   183,
     184,    63,   175,    50,   174,   184,   175,   175,   213,    25,
      51,   135,   136,   152,   119,    65,   186,     5,     6,   187,
       7,     8,   188,   189,   190,   191,   192,   193,   194,    66,
      67,   195,   141,   142,   143,   144,   145,   146,   147,   148,
      72,    68,    82,    98,   107,   126,   117,   120,   129,   131,
     134,   138,   139,    73,   151,   154,   158,   156,   160,   159,
     161,   162,   163,   164,   172,   178,   182,   207,   185,   210,
     217,    33,   140,   200,   114,   153,   155,    56,   168,     0,
     218,     0,     0,   206
};

static const yytype_int16 yycheck[] =
{
       0,    90,    66,     1,     0,   137,     7,     8,    16,    16,
      10,    16,    16,    19,    10,    16,    61,    23,    16,    65,
       1,    17,    68,     4,     0,    23,     7,     8,     9,    10,
      11,    12,    13,   197,    10,    16,     1,   121,    65,     4,
      41,    68,     7,     8,     9,    10,    11,    12,    13,     7,
       8,    16,    97,    16,   218,    68,    16,    17,    16,    72,
      60,    61,    67,    67,    70,    73,    67,    74,   157,   201,
      16,   203,   204,   205,    72,    16,    39,    18,    19,    20,
      21,    22,    23,    41,    25,    26,    67,    16,    50,    51,
      90,    87,     7,     8,   178,   159,    16,    97,   162,   163,
     164,    16,    67,    39,    16,    67,    69,    16,     1,    67,
      73,     4,    16,   202,     7,     8,     9,    10,    11,    12,
      13,   121,    16,    16,     0,    66,    41,    73,    74,    70,
      66,    65,    66,     0,    10,    16,    77,    18,    19,    20,
      21,    22,    23,    10,    25,    26,    16,     0,    18,    19,
      20,    21,    22,    23,    16,    25,    26,   157,     7,     8,
      65,    18,    19,    20,    21,    22,    23,    16,    25,    26,
      67,    68,    68,    68,    67,    69,    72,    72,   178,    73,
      68,    16,    68,    68,    72,    66,    72,    72,    71,    70,
      65,    66,    41,    68,    66,     5,    77,     7,     8,    65,
      70,    66,   202,    68,    67,    68,    16,    77,    66,    65,
      66,    65,    68,    70,    66,    66,    68,    68,    67,    69,
      77,    67,    68,    67,    68,    65,     1,    37,    38,     4,
      40,    41,     7,     8,     9,    10,    11,    12,    13,    71,
       6,    16,    57,    58,    59,    60,    61,    62,    63,    64,
      71,    16,    16,    16,    16,    16,    76,    76,    65,    16,
      69,    65,    75,    66,    72,    23,    16,    23,    16,    71,
      65,    71,    71,    71,    16,    66,    23,    16,    75,    67,
      67,    10,   105,   175,    73,   116,   119,    25,   136,    -1,
     209,    -1,    -1,   184
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,     7,     8,    16,    37,    38,    40,    41,    79,
      80,    81,    82,    83,    86,    87,    88,    91,    94,    95,
      96,    99,   103,    16,    16,    69,    73,    16,    16,    16,
      17,    16,     0,    81,    16,   103,    16,    65,    16,    71,
      16,    18,    19,    20,    21,    22,    23,    25,    26,    66,
      70,    77,   104,   105,   111,   112,   113,   114,   115,    39,
      66,    66,    65,    65,    66,    65,    71,     6,    16,    92,
      93,    94,    71,    66,   106,   107,   108,   109,   110,   113,
     111,   111,    16,   100,    16,    83,    88,    91,    94,    98,
     101,   102,   103,    16,    67,    87,    94,    97,    16,    84,
      85,    92,   111,    16,    74,    68,    72,    16,     1,    16,
      23,    72,   116,   117,   109,    67,    68,    76,    67,    68,
      76,    66,    68,    16,    39,   103,    16,    67,   102,    65,
      16,    16,    67,    87,    69,    67,    68,    72,    65,    75,
      93,    57,    58,    59,    60,    61,    62,    63,    64,    89,
      90,    72,    67,   107,    23,   110,    23,   101,    16,    71,
      16,    65,    71,    71,    71,    19,    23,    70,    85,    89,
      16,    74,    16,    65,    66,    68,    67,    92,    66,    92,
      92,    92,    23,    65,    66,    75,     1,     4,     7,     8,
       9,    10,    11,    12,    13,    16,   118,   119,   120,   121,
      90,    72,   101,    72,    72,    72,   118,    16,    65,    66,
      67,   120,    89,    67,    89,    89,    89,    67,   119,    67
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    78,    79,    80,    80,    81,    81,    81,    81,    81,
      81,    81,    81,    82,    82,    83,    84,    84,    85,    85,
      85,    85,    86,    86,    87,    87,    88,    88,    89,    89,
      89,    90,    90,    90,    90,    90,    90,    90,    90,    91,
      91,    92,    92,    92,    93,    93,    94,    93,    93,    95,
      96,    96,    97,    97,    98,    99,    99,   100,   100,   101,
     101,   102,   102,   102,   102,   102,   103,   103,   103,   104,
     105,   106,   106,   107,   107,   108,   109,   109,   110,   110,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   112,
     112,   113,   113,   113,   114,   115,   116,   116,   117,   117,
     118,   118,   119,   119,   120,   120,   120,   121,   121,   121,
     121,   121,   121,   121,   121,   121
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     3,     3,     5,     3,     1,     3,     4,
       3,     1,     1,     1,     7,     7,     9,     9,     3,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     3,     1,     0,     2,     2,     2,     4,     6,     6,
       5,     4,     2,     1,     6,     7,     5,     3,     1,     2,
       1,     2,     3,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     1,     3,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     4,     3,     1,     1,     1,     1,
       0,     1,     2,     1,     1,     4,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        YY_LAC_DISCARD ("YYBACKUP");                              \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_TOK_IDENTIFIER: /* TOK_IDENTIFIER  */
#line 114 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).ident)); }
#line 1052 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_TOK_USE_IDENTIFIER: /* TOK_USE_IDENTIFIER  */
#line 114 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).ident)); }
#line 1058 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_global: /* global  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1064 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_use: /* use  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1070 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_enum: /* enum  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1076 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_enum_item: /* enum_item  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1082 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_function: /* function  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1088 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_function_decl: /* function_decl  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1094 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_function_impl: /* function_impl  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1100 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_register: /* register  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1106 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_interface: /* interface  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1112 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_interface_impl: /* interface_impl  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1118 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_type: /* type  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1124 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_type_stmt: /* type_stmt  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1130 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_simplevar_decl: /* simplevar_decl  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1136 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_const_expr: /* const_expr  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1142 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_unary: /* unary  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1148 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1154 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_cast: /* cast  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1160 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_constructor: /* constructor  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1166 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_ignore_param: /* ignore_param  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1172 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_ignore_stmt: /* ignore_stmt  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1178 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

    case YYSYMBOL_ignore: /* ignore  */
#line 115 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
         { fprintf(yyo, "'%s'", ((*yyvaluep).node) ? ((*yyvaluep).node)->getName().c_str() : ""); }
#line 1184 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, yyscan_t scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return YYENOMEM if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYPTRDIFF_T *yycapacity, YYPTRDIFF_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yy_state_t **yybottom,
                      yy_state_t *yybottom_no_free,
                      yy_state_t **yytop, yy_state_t *yytop_empty)
{
  YYPTRDIFF_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYPTRDIFF_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYPTRDIFF_T yyalloc = 2 * yysize_new;
      yy_state_t *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        YY_CAST (yy_state_t *,
                 YYSTACK_ALLOC (YY_CAST (YYSIZE_T,
                                         yyalloc * YYSIZEOF (*yybottom_new))));
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                                \
do {                                                                    \
  if (!yy_lac_established)                                              \
    {                                                                   \
      YYDPRINTF ((stderr,                                               \
                  "LAC: initial context established for %s\n",          \
                  yysymbol_name (yytoken)));                            \
      yy_lac_established = 1;                                           \
      switch (yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken))    \
        {                                                               \
        case YYENOMEM:                                                  \
          YYNOMEM;                                                      \
        case 1:                                                         \
          goto yyerrlab;                                                \
        }                                                               \
    }                                                                   \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      YYDPRINTF ((stderr, "LAC: initial context discarded due to "       \
                  Event "\n"));                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return YYENOMEM if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yy_state_t *yyesa, yy_state_t **yyes,
        YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, yysymbol_kind_t yytoken)
{
  yy_state_t *yyes_prev = yyssp;
  yy_state_t *yyesp = yyes_prev;
  /* Reduce until we encounter a shift and thereby accept the token.  */
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yysymbol_name (yytoken)));
  if (yytoken == YYSYMBOL_YYUNDEF)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[+*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          /* Use the default action.  */
          yyrule = yydefact[+*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          /* Use the action from yytable.  */
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      /* By now we know we have to simulate a reduce.  */
      YYDPRINTF ((stderr, " R%d", yyrule - 1));
      {
        /* Pop the corresponding number of values from the stack.  */
        YYPTRDIFF_T yylen = yyr2[yyrule];
        /* First pop from the LAC stack as many tokens as possible.  */
        if (yyesp != yyes_prev)
          {
            YYPTRDIFF_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yyesp = yyes_prev;
                yylen -= yysize;
              }
          }
        /* Only afterwards look at the main stack.  */
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      /* Push the resulting state of the reduction.  */
      {
        yy_state_fast_t yystate;
        {
          const int yylhs = yyr1[yyrule] - YYNTOKENS;
          const int yyi = yypgoto[yylhs] + *yyesp;
          yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyesp
                     ? yytable[yyi]
                     : yydefgoto[yylhs]);
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            YY_IGNORE_USELESS_CAST_BEGIN
            *yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return YYENOMEM;
              }
            YY_IGNORE_USELESS_CAST_BEGIN
            *++yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}

/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yy_state_t *yyesa;
  yy_state_t **yyes;
  YYPTRDIFF_T *yyes_capacity;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;

  int yyx;
  for (yyx = 0; yyx < YYNTOKENS; ++yyx)
    {
      yysymbol_kind_t yysym = YY_CAST (yysymbol_kind_t, yyx);
      if (yysym != YYSYMBOL_YYerror && yysym != YYSYMBOL_YYUNDEF)
        switch (yy_lac (yyctx->yyesa, yyctx->yyes, yyctx->yyes_capacity, yyctx->yyssp, yysym))
          {
          case YYENOMEM:
            return YYENOMEM;
          case 1:
            continue;
          default:
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else if (yyn == 0)
        YYDPRINTF ((stderr, "No expected tokens.\n"));
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store or if
   yy_lac returned YYENOMEM.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

    yy_state_t yyesa[20];
    yy_state_t *yyes = yyesa;
    YYPTRDIFF_T yyes_capacity = 20 < YYMAXDEPTH ? 20 : YYMAXDEPTH;

  /* Whether LAC context is established.  A Boolean.  */
  int yy_lac_established = 0;
  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      YY_LAC_ESTABLISH;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");
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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
  case 2: /* programa: globals  */
#line 119 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                   {
	for(auto stmt : *((yyvsp[0].nodes))) {
		program->addChild(stmt);
	}
}
#line 2146 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 3: /* globals: globals global  */
#line 125 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                         {
	if ((yyvsp[0].node)) {
		(yyvsp[-1].nodes)->push_back((yyvsp[0].node));
	}
}
#line 2156 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 4: /* globals: global  */
#line 131 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                 {
	(yyval.nodes) = new vector<Node*>();
	if ((yyvsp[0].node)) {
		(yyvsp[0].node)->setLocation((yylsp[0]));
		(yyval.nodes)->push_back((yyvsp[0].node));
	}
}
#line 2168 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 11: /* global: simplevar_decl ';'  */
#line 145 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                { (yyval.node) = NULL; }
#line 2174 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 12: /* global: qualifier simplevar_decl ';'  */
#line 147 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                      {
	if ((yyvsp[-2].nint) == qconst)
		(yyval.node) = (yyvsp[-1].node);
	else
		(yyval.node) = NULL;
}
#line 2185 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 13: /* use: TOK_USE TOK_IDENTIFIER ';'  */
#line 154 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                 {
	parseUseFile((yyvsp[-1].ident), (yylsp[-2]));
	(yyval.node) = NULL;
}
#line 2194 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 14: /* use: TOK_USE TOK_USE_IDENTIFIER ';'  */
#line 159 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                     {
	parseUseFile((yyvsp[-1].ident), (yylsp[-2]));
	(yyval.node) = NULL;
}
#line 2203 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 15: /* enum: TOK_ENUM TOK_IDENTIFIER '{' enum_items '}'  */
#line 164 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                      {
	(yyval.node) = new Enum((yyvsp[-3].ident), std::move(*(yyvsp[-1].nodes)), (yylsp[-3]));
}
#line 2211 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 16: /* enum_items: enum_items ',' enum_item  */
#line 168 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                             {
	(yyvsp[-2].nodes)->push_back((yyvsp[0].node));
	(yyval.nodes) = (yyvsp[-2].nodes);
}
#line 2220 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 17: /* enum_items: enum_item  */
#line 173 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                       {
	(yyval.nodes) = new vector<Node*>();
	(yyval.nodes)->push_back((yyvsp[0].node));
}
#line 2229 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 18: /* enum_item: TOK_IDENTIFIER '=' TOK_INTEGER  */
#line 178 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                     {
	(yyval.node) = new NamedConst((yyvsp[-2].ident), new Int8((yyvsp[0].nint), (yylsp[-2])));
}
#line 2237 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 19: /* enum_item: TOK_IDENTIFIER '=' '-' TOK_INTEGER  */
#line 182 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                         {
	(yyval.node) = new NamedConst((yyvsp[-3].ident), new Int8((yyvsp[0].nint) * -1, (yylsp[-3])));
}
#line 2245 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 20: /* enum_item: TOK_IDENTIFIER '=' TOK_UINTEGER  */
#line 186 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                      {
	(yyval.node) = new NamedConst((yyvsp[-2].ident), new UInt8((yyvsp[0].unint), (yylsp[-2])));
}
#line 2253 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 21: /* enum_item: TOK_IDENTIFIER  */
#line 190 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                               {
	(yyval.node) = new NamedConst((yyvsp[0].ident), (yylsp[0]));
}
#line 2261 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 24: /* function_decl: TOK_IDENTIFIER TOK_IDENTIFIER '(' function_params ')' function_attributes ';'  */
#line 196 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                                                            {
	FunctionDecl *func = new FunctionDecl(buildTypes->getType((yyvsp[-6].ident), true), (yyvsp[-5].ident), (yyvsp[-3].fps), (yylsp[-5]));
	func->setAttributes((yyvsp[-1].fattrs));
	(yyval.node) = func;
}
#line 2271 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 25: /* function_decl: pointer_type TOK_IDENTIFIER '(' function_params ')' function_attributes ';'  */
#line 202 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                                                          {
	FunctionDecl *func = new FunctionDecl((yyvsp[-6].dtype), (yyvsp[-5].ident), (yyvsp[-3].fps), (yylsp[-5]));
	func->setAttributes((yyvsp[-1].fattrs));
	(yyval.node) = func;
}
#line 2281 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 26: /* function_impl: TOK_IDENTIFIER TOK_IDENTIFIER '(' function_params ')' function_attributes '{' stmts_rec '}'  */
#line 208 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                                                                              {
	vector<Node*> stmts;
	FunctionImpl *func = new FunctionImpl(buildTypes->getType((yyvsp[-8].ident), true), (yyvsp[-7].ident), (yyvsp[-5].fps),
		std::move(stmts), (yylsp[-8]), (yylsp[0]));
	func->setExternal(true);
	func->setDeclaration(true);
    func->setAttributes((yyvsp[-3].fattrs));
	(yyval.node) = func;
}
#line 2295 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 27: /* function_impl: pointer_type TOK_IDENTIFIER '(' function_params ')' function_attributes '{' stmts_rec '}'  */
#line 218 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                                                                            {
	vector<Node*> stmts;
	FunctionImpl *func = new FunctionImpl((yyvsp[-8].dtype), (yyvsp[-7].ident), (yyvsp[-5].fps),
		std::move(stmts), (yylsp[-7]), (yylsp[0]));
	func->setExternal(true);
	func->setDeclaration(true);
	func->setAttributes((yyvsp[-3].fattrs));
	(yyval.node) = func;
}
#line 2309 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 28: /* function_attributes: function_attributes ',' function_attribute  */
#line 228 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                         {
	(yyvsp[-2].fattrs)->addAttribute((yyvsp[0].fattr));
	(yyval.fattrs) = (yyvsp[-2].fattrs);
}
#line 2318 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 29: /* function_attributes: function_attribute  */
#line 233 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                             {
	(yyval.fattrs) = new FunctionAttributes();
	(yyval.fattrs)->addAttribute((yyvsp[0].fattr));
}
#line 2327 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 30: /* function_attributes: %empty  */
#line 238 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                             {
	(yyval.fattrs) = new FunctionAttributes();
}
#line 2335 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 31: /* function_attribute: TOK_WEAK  */
#line 243 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                        { (yyval.fattr) = new FunctionAttribute(fa_weak, ""); }
#line 2341 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 32: /* function_attribute: TOK_INLINE  */
#line 244 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                { (yyval.fattr) = new FunctionAttribute(fa_inline, ""); }
#line 2347 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 33: /* function_attribute: TOK_NOINLINE  */
#line 245 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                { (yyval.fattr) = new FunctionAttribute(fa_noinline, ""); }
#line 2353 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 34: /* function_attribute: TOK_NAKED  */
#line 246 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                        { (yyval.fattr) = new FunctionAttribute(fa_naked, ""); }
#line 2359 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 35: /* function_attribute: TOK_SIGNAL  */
#line 247 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                { (yyval.fattr) = new FunctionAttribute(fa_signal, ""); }
#line 2365 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 36: /* function_attribute: TOK_DEBUGONLY  */
#line 248 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                { (yyval.fattr) = new FunctionAttribute(fa_debugonly, ""); }
#line 2371 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 37: /* function_attribute: TOK_NOOPT  */
#line 249 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                        { (yyval.fattr) = new FunctionAttribute(fa_noopt, ""); }
#line 2377 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 38: /* function_attribute: TOK_SECTION TOK_IDENTIFIER  */
#line 250 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                { (yyval.fattr) = new FunctionAttribute(fa_section, (yyvsp[0].ident)); }
#line 2383 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 39: /* qualifier: TOK_CONST  */
#line 252 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                { (yyval.nint) = qconst; }
#line 2389 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 40: /* qualifier: TOK_VOLATILE  */
#line 253 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                        { (yyval.nint) = qvolatile; }
#line 2395 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 41: /* function_params: function_params ',' function_param  */
#line 255 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                    {
    (yyvsp[-2].fps) -> append((yyvsp[0].fp));
    (yyval.fps) = (yyvsp[-2].fps);
}
#line 2404 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 42: /* function_params: function_param  */
#line 260 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                {
    FunctionParams *fps = new FunctionParams();
    fps->append((yyvsp[0].fp));
    (yyval.fps) = fps;
}
#line 2414 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 43: /* function_params: %empty  */
#line 266 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                        {
    FunctionParams *fps = new FunctionParams();
    (yyval.fps) = fps;
}
#line 2423 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 44: /* function_param: TOK_IDENTIFIER TOK_IDENTIFIER  */
#line 271 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                         {
	(yyval.fp) = new Variable((yyvsp[0].ident), buildTypes->getType((yyvsp[-1].ident), true), (yylsp[-1]));
}
#line 2431 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 45: /* function_param: pointer_type TOK_IDENTIFIER  */
#line 275 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                       {
	(yyval.fp) = new Variable((yyvsp[0].ident), (yyvsp[-1].dtype), (yylsp[0]));
}
#line 2439 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 46: /* pointer_type: TOK_IDENTIFIER '*'  */
#line 279 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                        {
	(yyval.dtype) = buildTypes->getPointerType((yyvsp[-1].ident), (yylsp[-1]), true);
}
#line 2447 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 47: /* function_param: TOK_IDENTIFIER '[' ']' TOK_IDENTIFIER  */
#line 283 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                 {
	(yyval.fp) = new ParamArray((yyvsp[0].ident), (yyvsp[-3].ident), (yylsp[-3]));
}
#line 2455 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 48: /* function_param: TOK_IDENTIFIER '[' ']' '[' ']' TOK_IDENTIFIER  */
#line 287 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                         {
	(yyval.fp) = new ParamMatrix((yyvsp[0].ident), (yyvsp[-5].ident), (yylsp[-5]));
}
#line 2463 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 49: /* register: TOK_REGISTER TOK_IDENTIFIER TOK_IDENTIFIER TOK_AT const_expr ';'  */
#line 291 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                                        {
	(yyval.node) = new Pointer((yyvsp[-3].ident), buildTypes->getType((yyvsp[-4].ident), true), (yyvsp[-1].node), (yylsp[-3]));
	(yyval.node)->setQualifier(qvolatile);
}
#line 2472 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 50: /* interface: TOK_INTF TOK_IDENTIFIER '{' interface_decls '}'  */
#line 296 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                      {
	(yyval.node) = new Interface((yyvsp[-3].ident), std::move(*(yyvsp[-1].nodes)), (yylsp[-3]));
}
#line 2480 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 51: /* interface: TOK_INTF TOK_IDENTIFIER '{' '}'  */
#line 300 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                {
	(yyval.node) = new Interface((yyvsp[-2].ident), (yylsp[-2]));
}
#line 2488 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 52: /* interface_decls: interface_decls function_decl  */
#line 304 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                {
	(yyvsp[-1].nodes)->push_back((yyvsp[0].node));
	(yyval.nodes) = (yyvsp[-1].nodes);
}
#line 2497 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 53: /* interface_decls: function_decl  */
#line 309 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                {
	(yyval.nodes) = new vector<Node*>();
	(yyval.nodes)->push_back((yyvsp[0].node));
}
#line 2506 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 54: /* interface_impl: TOK_IDENTIFIER TOK_IMPL TOK_IDENTIFIER '{' type_stmts '}'  */
#line 314 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                                         {
	vector<string> intf;
	intf.push_back((yyvsp[-3].ident));
	UserType *ut = new UserType((yyvsp[-5].ident), std::move(*(yyvsp[-1].nodes)), std::move(intf), (yylsp[-5]));
	(yyval.node) = ut;
}
#line 2517 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 55: /* type: TOK_TYPE TOK_IDENTIFIER TOK_IMPL type_impls '{' type_stmts '}'  */
#line 321 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                          {
	UserType *ut = new UserType((yyvsp[-5].ident), std::move(*(yyvsp[-1].nodes)), std::move(*(yyvsp[-3].strings)), (yylsp[-5]));
	ut->setDeclaration(true);
	(yyval.node) = ut;
}
#line 2527 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 56: /* type: TOK_TYPE TOK_IDENTIFIER '{' type_stmts '}'  */
#line 327 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                      {
	UserType *ut = new UserType((yyvsp[-3].ident), std::move(*(yyvsp[-1].nodes)), (yylsp[-3]));
	ut->setDeclaration(true);
	(yyval.node) = ut;
}
#line 2537 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 57: /* type_impls: type_impls ',' TOK_IDENTIFIER  */
#line 333 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                           {
	(yyvsp[-2].strings)->push_back((yyvsp[0].ident));
	(yyval.strings) = (yyvsp[-2].strings);
}
#line 2546 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 58: /* type_impls: TOK_IDENTIFIER  */
#line 338 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                            {
	(yyval.strings) = new vector<string>();
	(yyval.strings)->push_back((yyvsp[0].ident));
}
#line 2555 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 59: /* type_stmts: type_stmts type_stmt  */
#line 343 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                  {
	if ((yyvsp[0].node))
		(yyval.nodes)->push_back((yyvsp[0].node));
}
#line 2564 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 60: /* type_stmts: type_stmt  */
#line 348 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                       {
	(yyval.nodes) = new vector<Node*>();
	if ((yyvsp[0].node))
		(yyval.nodes)->push_back((yyvsp[0].node));
}
#line 2574 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 62: /* type_stmt: qualifier simplevar_decl ';'  */
#line 355 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                        { (yyvsp[-1].node)->setQualifier((DataQualifier)(yyvsp[-2].nint)); (yyval.node) = (yyvsp[-1].node); }
#line 2580 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 66: /* simplevar_decl: TOK_IDENTIFIER '=' expr  */
#line 360 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                { (yyval.node) = new Scalar((yyvsp[-2].ident), (yyvsp[0].node));   (yyval.node)->setLocation((yylsp[-2])); }
#line 2586 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 67: /* simplevar_decl: TOK_IDENTIFIER '=' array  */
#line 361 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                { (yyval.node) = new Array((yyvsp[-2].ident), (yyvsp[0].aes), (yylsp[-2])); }
#line 2592 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 68: /* simplevar_decl: TOK_IDENTIFIER '=' matrix  */
#line 362 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                { (yyval.node) = new Matrix((yyvsp[-2].ident), (yyvsp[0].mes), (yylsp[-2])); }
#line 2598 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 69: /* array: '{' elements '}'  */
#line 364 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                { (yyval.aes) = (yyvsp[-1].aes); }
#line 2604 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 70: /* matrix: '{' melements '}'  */
#line 365 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                { (yyval.mes) = (yyvsp[-1].mes); }
#line 2610 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 71: /* melements: melements ',' melement  */
#line 367 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                   {
	(yyvsp[-2].mes)->append((yyvsp[0].me));
	(yyval.mes) = (yyvsp[-2].mes);
}
#line 2619 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 72: /* melements: melement  */
#line 372 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                     {
	MatrixElements *mes = new MatrixElements((yyloc));
	mes->append((yyvsp[0].me));
	(yyval.mes) = mes;
}
#line 2629 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 73: /* melement: relements ':' TOK_INTEGER  */
#line 378 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                        { (yyval.me) = new MatrixElement((yyvsp[-2].aes), (unsigned)(yyvsp[0].nint)); }
#line 2635 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 74: /* melement: relements  */
#line 379 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                { (yyval.me) = new MatrixElement((yyvsp[0].aes), 1);}
#line 2641 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 75: /* relements: '{' elements '}'  */
#line 381 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                { (yyval.aes) = (yyvsp[-1].aes); }
#line 2647 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 76: /* elements: elements ',' element  */
#line 383 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                { (yyvsp[-2].aes)->append((yyvsp[0].ae));
										  (yyval.aes) = (yyvsp[-2].aes); }
#line 2654 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 77: /* elements: element  */
#line 385 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                        { ArrayElements *aes = new ArrayElements((yylsp[0]));
										  aes->append((yyvsp[0].ae));
										  (yyval.aes) = aes; }
#line 2662 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 78: /* element: expr ':' TOK_INTEGER  */
#line 389 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                        { (yyval.ae) = new ArrayElement((yyvsp[-2].node), (unsigned)(yyvsp[0].nint)); }
#line 2668 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 79: /* element: expr  */
#line 390 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                        { (yyval.ae) = new ArrayElement((yyvsp[0].node), 1); }
#line 2674 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 80: /* const_expr: TOK_INTEGER  */
#line 392 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                            { (yyval.node) = getNodeForIntConst((yyvsp[0].nint), (yylsp[0])); }
#line 2680 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 81: /* const_expr: TOK_UINTEGER  */
#line 393 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                    { (yyval.node) = getNodeForUIntConst((yyvsp[0].unint), (yylsp[0])); }
#line 2686 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 82: /* const_expr: TOK_CHAR  */
#line 394 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                    { (yyval.node) = new Char((yyvsp[0].ch), (yylsp[0])); }
#line 2692 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 83: /* const_expr: TOK_TRUE  */
#line 395 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                { (yyval.node) = new Int1(1, (yylsp[0])); }
#line 2698 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 84: /* const_expr: TOK_FALSE  */
#line 396 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                { (yyval.node) = new Int1(0, (yylsp[0])); }
#line 2704 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 85: /* const_expr: TOK_FLOAT  */
#line 397 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                        { (yyval.node) = new Float((yyvsp[0].nfloat), (yylsp[0])); }
#line 2710 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 86: /* const_expr: TOK_DOUBLE  */
#line 398 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                        { (yyval.node) = new Double((yyvsp[0].ndouble), (yylsp[0])); }
#line 2716 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 87: /* const_expr: TOK_LDOUBLE  */
#line 399 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                        { (yyval.node) = new Float128((yyvsp[0].nldouble), (yylsp[0])); }
#line 2722 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 88: /* const_expr: unary  */
#line 400 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 2728 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 89: /* unary: '-' const_expr  */
#line 403 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                        { (yyval.node) = new BinaryOp((yyvsp[0].node), '*', getNodeForIntConst(-1, (yylsp[0]))); }
#line 2734 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 90: /* unary: '~' const_expr  */
#line 404 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                { (yyval.node) = new FlipOp((yyvsp[0].node)); }
#line 2740 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 94: /* cast: TOK_IDENTIFIER '(' ignore_param ')'  */
#line 412 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                               {
	ParamsCall *pc = new ParamsCall();
	pc->append(new Node((yylsp[-3])));
	(yyval.node) = new FunctionCall((yyvsp[-3].ident), pc, (yylsp[-3]));
	(yyval.node)->setLocation((yylsp[-3]));
}
#line 2751 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 95: /* constructor: TOK_IDENTIFIER '(' ')'  */
#line 419 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                         {
	ParamsCall *pc = new ParamsCall();
	pc->append(new Node((yylsp[-2])));
	(yyval.node) = new FunctionCall((yyvsp[-2].ident), pc, (yylsp[-2]));
	(yyval.node)->setLocation((yylsp[-2]));
}
#line 2762 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 96: /* ignore_param: ignore_p  */
#line 426 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                        { (yyval.node) = NULL; }
#line 2768 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 97: /* ignore_param: error  */
#line 427 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                        { (yyval.node) = NULL; }
#line 2774 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 98: /* ignore_p: TOK_INTEGER  */
#line 432 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                { YYERROR; }
#line 2780 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 99: /* ignore_p: TOK_IDENTIFIER  */
#line 433 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                        { YYERROR; }
#line 2786 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 100: /* stmts_rec: %empty  */
#line 435 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                        { (yyval.nodes) = NULL; }
#line 2792 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 101: /* stmts_rec: stmts  */
#line 436 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                { (yyval.nodes) = NULL; }
#line 2798 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 102: /* stmts: stmts ignore_stmt  */
#line 438 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                { (yyval.nodes) = NULL; }
#line 2804 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 103: /* stmts: ignore_stmt  */
#line 439 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                        { (yyval.nodes) = NULL; }
#line 2810 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 104: /* ignore_stmt: ignore  */
#line 441 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                { (yyval.node) = NULL; }
#line 2816 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 105: /* ignore_stmt: error '{' stmts '}'  */
#line 442 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                { (yyval.node) = NULL; }
#line 2822 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 106: /* ignore_stmt: error ';'  */
#line 443 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                                                                { (yyval.node) = NULL; }
#line 2828 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 107: /* ignore: TOK_IDENTIFIER  */
#line 448 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                         { YYERROR; }
#line 2834 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 108: /* ignore: TOK_WHILE  */
#line 449 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                             { YYERROR; }
#line 2840 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 109: /* ignore: TOK_RETURN  */
#line 450 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                             { YYERROR; }
#line 2846 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 110: /* ignore: TOK_CONST  */
#line 451 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                             { YYERROR; }
#line 2852 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 111: /* ignore: TOK_VOLATILE  */
#line 452 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                             { YYERROR; }
#line 2858 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 112: /* ignore: TOK_IF  */
#line 453 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                             { YYERROR; }
#line 2864 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 113: /* ignore: TOK_ELSE  */
#line 454 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                             { YYERROR; }
#line 2870 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 114: /* ignore: TOK_LOOP  */
#line 455 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                             { YYERROR; }
#line 2876 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;

  case 115: /* ignore: TOK_ASM  */
#line 456 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"
                             { YYERROR; }
#line 2882 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"
    break;


#line 2886 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.cpp"

        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yyesa, &yyes, &yyes_capacity, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc, scanner);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 458 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/LanguageUse_gen.y"


/*static const char *
error_format_string (int argc)
{
  switch (argc)
    {
    default: // Avoid compiler warnings.
    case 0: return "%@: syntax error";
    case 1: return "%@: syntax error: unexpected %u";
      // TRANSLATOR '%@' is a location in a file, '%u' is an
      // "unexpectetoken", and '%0e', '%1e'... are expected tokens
      // at this pot.
      //
      // For instan on the expression "1 + * 2", you'd get
      //
      // 1.5: syntaerror: expected - or ( or number or function or variable before *
    case 2: return "%@: syntax error: expected %0e before %u";
    case 3: return "%@: syntax error: expected %0e or %1e before %u";
    case 4: return "%@: syntax error: expected %0e or %1e or %2e before %u";
    case 5: return "%@: syntax error: expected %0e or %1e or %2e or %3e before %u";
    case 6: return "%@: syntax error: expected %0e or %1e or %2e or %3e or %4e before %u";
    case 7: return "%@: syntax error: expected %0e or %1e or %2e or %3e or %4e or %5e before %u";
    case 8: return "%@: syntax error: expected %0e or %1e or %2e or %3e or %4e or %5e etc., before %u";
    }
}

static int yyreport_syntax_error (const yypcontext_t *ctx, yyscan_t scanner) {
	enum { ARGS_MAX = 6 };
	yysymbol_kind_t arg[ARGS_MAX];
	
	int argsize = yypcontext_expected_tokens (ctx, arg, ARGS_MAX);
	if (argsize < 0)
		return argsize;

	const int too_many_expected_tokens = argsize == 0 && arg[0] != YYSYMBOL_YYEMPTY;
	if (too_many_expected_tokens)
		argsize = ARGS_MAX;
	
	const char *format = error_format_string (1 + argsize + too_many_expected_tokens);

	const YYLTYPE *loc = yypcontext_location (ctx);
	while (*format) {
		// %@: location.
		if (format[0] == '%' && format[1] == '@') {
			fprintf(stderr, "%s:%d:%d:", build_filename(),
					loc->first_line, loc->first_column);
			format += 2;
		}
	// %u: unexpected token.
		else if (format[0] == '%' && format[1] == 'u') {
			fputs (yysymbol_name (yypcontext_token (ctx)), stderr);
			format += 2;
		}
	// %0e, %1e...: expected token.
		else if (format[0] == '%' && isdigit ((unsigned char) format[1])
			&& format[2] == 'e' && (format[1] - '0') < argsize) {
			
			int i = format[1] - '0';
			fputs (yysymbol_name (arg[i]), stderr);
			format += 3;
		} else {
			fputc (*format, stderr);
			++format;
		}
	}
	fputc ('\n', stderr);

	// Quote the source line.
	{
		fprintf (stderr, "%5d | %s\n", loc->first_line, uctx->line);
		fprintf (stderr, "%5s | %*s", "", loc->first_column, "^");
		for (int i = loc->last_column - loc->first_column - 1; 0 < i; --i)
			putc ('~', stderr);
		putc ('\n', stderr);
	}

	return 0;
}*/
