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
#line 12 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"

  #include <stdlib.h>
  #include <limits.h>
  #define SCANNER_OR_VISITOR
  #include "Header.h"

#line 75 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"

/* Substitute the variable and function names.  */
#define yyparse         MAINparse
#define yylex           MAINlex
#define yyerror         MAINerror
#define yydebug         MAINdebug
#define yynerrs         MAINnerrs


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

#include "Language_gen_y.hpp"
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
  YYSYMBOL_65_ = 65,                       /* '|'  */
  YYSYMBOL_66_ = 66,                       /* '^'  */
  YYSYMBOL_67_ = 67,                       /* '&'  */
  YYSYMBOL_68_ = 68,                       /* '+'  */
  YYSYMBOL_69_ = 69,                       /* '-'  */
  YYSYMBOL_70_ = 70,                       /* '*'  */
  YYSYMBOL_71_ = 71,                       /* '/'  */
  YYSYMBOL_72_ = 72,                       /* '%'  */
  YYSYMBOL_UMINUS = 73,                    /* UMINUS  */
  YYSYMBOL_UADDRESS = 74,                  /* UADDRESS  */
  YYSYMBOL_UDEREFERENCE = 75,              /* UDEREFERENCE  */
  YYSYMBOL_76_ = 76,                       /* '!'  */
  YYSYMBOL_77_ = 77,                       /* '~'  */
  YYSYMBOL_78_ = 78,                       /* ';'  */
  YYSYMBOL_79_ = 79,                       /* '.'  */
  YYSYMBOL_80_ = 80,                       /* '{'  */
  YYSYMBOL_81_ = 81,                       /* '}'  */
  YYSYMBOL_82_ = 82,                       /* ','  */
  YYSYMBOL_83_ = 83,                       /* '='  */
  YYSYMBOL_84_ = 84,                       /* '('  */
  YYSYMBOL_85_ = 85,                       /* ')'  */
  YYSYMBOL_86_ = 86,                       /* '['  */
  YYSYMBOL_87_ = 87,                       /* ']'  */
  YYSYMBOL_88_ = 88,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 89,                  /* $accept  */
  YYSYMBOL_programa = 90,                  /* programa  */
  YYSYMBOL_globals = 91,                   /* globals  */
  YYSYMBOL_global = 92,                    /* global  */
  YYSYMBOL_use = 93,                       /* use  */
  YYSYMBOL_string_chain = 94,              /* string_chain  */
  YYSYMBOL_enum = 95,                      /* enum  */
  YYSYMBOL_enum_items = 96,                /* enum_items  */
  YYSYMBOL_enum_item = 97,                 /* enum_item  */
  YYSYMBOL_function = 98,                  /* function  */
  YYSYMBOL_function_decl = 99,             /* function_decl  */
  YYSYMBOL_function_impl = 100,            /* function_impl  */
  YYSYMBOL_function_attributes = 101,      /* function_attributes  */
  YYSYMBOL_function_attribute = 102,       /* function_attribute  */
  YYSYMBOL_qualifier = 103,                /* qualifier  */
  YYSYMBOL_function_params = 104,          /* function_params  */
  YYSYMBOL_function_param = 105,           /* function_param  */
  YYSYMBOL_pointer_type = 106,             /* pointer_type  */
  YYSYMBOL_register = 107,                 /* register  */
  YYSYMBOL_interface = 108,                /* interface  */
  YYSYMBOL_interface_decls = 109,          /* interface_decls  */
  YYSYMBOL_interface_impl = 110,           /* interface_impl  */
  YYSYMBOL_type = 111,                     /* type  */
  YYSYMBOL_type_impls = 112,               /* type_impls  */
  YYSYMBOL_type_stmts = 113,               /* type_stmts  */
  YYSYMBOL_type_stmt = 114,                /* type_stmt  */
  YYSYMBOL_bind = 115,                     /* bind  */
  YYSYMBOL_bind_scope = 116,               /* bind_scope  */
  YYSYMBOL_array = 117,                    /* array  */
  YYSYMBOL_matrix = 118,                   /* matrix  */
  YYSYMBOL_melements = 119,                /* melements  */
  YYSYMBOL_melement = 120,                 /* melement  */
  YYSYMBOL_relements = 121,                /* relements  */
  YYSYMBOL_elements = 122,                 /* elements  */
  YYSYMBOL_element = 123,                  /* element  */
  YYSYMBOL_asminline = 124,                /* asminline  */
  YYSYMBOL_stmts = 125,                    /* stmts  */
  YYSYMBOL_stmts_rec = 126,                /* stmts_rec  */
  YYSYMBOL_stmt = 127,                     /* stmt  */
  YYSYMBOL_var_decl = 128,                 /* var_decl  */
  YYSYMBOL_var_decl_stmt = 129,            /* var_decl_stmt  */
  YYSYMBOL_returnblock = 130,              /* returnblock  */
  YYSYMBOL_condblock = 131,                /* condblock  */
  YYSYMBOL_elseblock = 132,                /* elseblock  */
  YYSYMBOL_whileblock = 133,               /* whileblock  */
  YYSYMBOL_expr = 134,                     /* expr  */
  YYSYMBOL_factor = 135,                   /* factor  */
  YYSYMBOL_left_value = 136,               /* left_value  */
  YYSYMBOL_left_value_base = 137,          /* left_value_base  */
  YYSYMBOL_ident_access = 138,             /* ident_access  */
  YYSYMBOL_function_call = 139,            /* function_call  */
  YYSYMBOL_array_access = 140,             /* array_access  */
  YYSYMBOL_matrix_access = 141,            /* matrix_access  */
  YYSYMBOL_paramscall = 142                /* paramscall  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  39
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   987

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  168
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  350

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   322


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
       2,     2,     2,    76,     2,     2,     2,    72,    67,     2,
      84,    85,    70,    68,    82,    69,    79,    71,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    88,    78,
       2,    83,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    86,     2,    87,    66,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,    65,    81,    77,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      73,    74,    75
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   134,   134,   136,   142,   148,   156,   157,   158,   159,
     160,   162,   163,   164,   166,   171,   176,   181,   185,   190,
     195,   199,   203,   207,   211,   211,   213,   219,   225,   232,
     239,   244,   249,   254,   255,   256,   257,   258,   259,   260,
     261,   272,   273,   275,   280,   286,   291,   295,   299,   303,
     307,   311,   316,   320,   324,   329,   334,   341,   346,   351,
     356,   361,   366,   372,   373,   374,   375,   377,   384,   385,
     387,   388,   390,   395,   401,   402,   404,   406,   408,   412,
     413,   415,   416,   418,   419,   421,   424,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443,   444,   445,   448,   449,   451,   452,   453,   458,   467,
     474,   475,   481,   485,   490,   491,   501,   506,   511,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   567,   568,   570,   571,   572,   574,
     583,   590,   597,   604,   628,   634,   640,   645,   651
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
  "TOK_SIGNAL", "TOK_DEBUGONLY", "TOK_NOOPT", "'|'", "'^'", "'&'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "UMINUS", "UADDRESS", "UDEREFERENCE", "'!'",
  "'~'", "';'", "'.'", "'{'", "'}'", "','", "'='", "'('", "')'", "'['",
  "']'", "':'", "$accept", "programa", "globals", "global", "use",
  "string_chain", "enum", "enum_items", "enum_item", "function",
  "function_decl", "function_impl", "function_attributes",
  "function_attribute", "qualifier", "function_params", "function_param",
  "pointer_type", "register", "interface", "interface_decls",
  "interface_impl", "type", "type_impls", "type_stmts", "type_stmt",
  "bind", "bind_scope", "array", "matrix", "melements", "melement",
  "relements", "elements", "element", "asminline", "stmts", "stmts_rec",
  "stmt", "var_decl", "var_decl_stmt", "returnblock", "condblock",
  "elseblock", "whileblock", "expr", "factor", "left_value",
  "left_value_base", "ident_access", "function_call", "array_access",
  "matrix_access", "paramscall", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-248)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     904,     5,  -248,  -248,    17,    23,    29,    31,    67,    31,
      98,   904,  -248,  -248,  -248,  -248,  -248,  -248,   124,   130,
    -248,  -248,  -248,  -248,  -248,   -49,   -18,    77,    86,   142,
     213,   157,  -248,   -29,    81,  -248,   138,   163,   -20,  -248,
    -248,   180,   237,   178,   176,  -248,   188,   407,   253,   259,
     268,   282,   274,   275,   226,     9,  -248,   276,   277,    31,
     211,  -248,   407,   274,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,   407,   407,   407,   407,   407,   395,
     407,  -248,  -248,   808,  -248,  -248,   209,   -42,  -248,   248,
    -248,  -248,  -248,   407,   -13,    25,  -248,   289,  -248,    89,
      30,  -248,  -248,   305,  -248,    20,  -248,  -248,    19,  -248,
    -248,   306,    14,  -248,   240,   189,  -248,    59,   808,   133,
    -248,  -248,  -248,  -248,  -248,   407,   192,  -248,   236,   197,
    -248,    82,   327,   407,   407,   407,   407,   407,   407,   407,
     407,   407,   407,   407,   407,   407,   407,   407,   407,   407,
     407,   407,   244,   529,  -248,   245,   274,   290,  -248,   226,
     315,   252,   321,   198,  -248,  -248,   255,   256,  -248,  -248,
      43,  -248,   277,  -248,  -248,   265,   290,   205,  -248,   264,
     322,  -248,   407,   332,  -248,   882,   836,   435,   435,   257,
     257,   257,   257,   106,   106,   907,   915,   845,   175,   175,
    -248,  -248,  -248,   808,   145,   407,  -248,    -8,  -248,  -248,
    -248,  -248,   340,  -248,  -248,  -248,  -248,    63,  -248,    33,
    -248,   274,   278,   274,   274,   274,  -248,  -248,   339,  -248,
    -248,   120,  -248,  -248,  -248,  -248,  -248,   407,  -248,   319,
    -248,   296,  -248,  -248,    72,   290,  -248,   146,   226,   153,
     154,   155,  -248,  -248,    72,   808,  -248,   348,   407,   378,
     407,   323,   407,   407,   326,   324,    72,  -248,  -248,   329,
    -248,  -248,   462,   330,  -248,   290,    36,   290,   290,   290,
     328,  -248,   808,   334,   487,    72,   445,   386,  -248,  -248,
    -248,  -248,   407,   341,   359,   360,   -51,   -35,   361,  -248,
     119,  -248,   123,    37,    80,  -248,   421,    72,   365,  -248,
      72,   407,   560,   407,   407,   407,   369,   407,   370,   407,
     407,  -248,   368,  -248,   380,   591,  -248,   622,   653,   684,
    -248,   715,  -248,   746,   777,   399,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,     6,  -248,    72,  -248,   382,  -248
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,    42,    41,   159,     0,     0,     0,     0,     0,
       0,     3,     5,     6,    11,    10,    24,    25,     0,     0,
       9,     7,     8,    13,    12,     0,     0,   156,   157,   158,
       0,     0,    48,     0,     0,    16,     0,     0,     0,     1,
       4,   159,     0,     0,   109,   104,     0,     0,     0,     0,
       0,     0,    45,     0,     0,     0,    14,     0,     0,     0,
     109,   103,     0,    45,   159,   146,   148,   149,   150,   151,
     147,   152,   144,   145,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   142,   153,   154,   156,   155,     0,
     160,   161,   162,     0,     0,     0,    44,     0,    60,     0,
     159,    66,    64,     0,    65,     0,    62,    63,     0,    53,
      55,     0,     0,    15,    23,     0,    19,     0,   108,     0,
     140,   138,   141,   127,   139,     0,     0,    73,    75,     0,
      78,    80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   168,   164,     0,    46,     0,     0,    32,    47,     0,
       0,     0,     0,   109,    58,    61,     0,     0,    52,    54,
       0,    17,     0,    68,    69,     0,    32,     0,    71,     0,
       0,    70,     0,     0,   143,   119,   120,   121,   122,   124,
     123,   126,   125,   136,   137,   130,   134,   135,   128,   129,
     131,   132,   133,   167,     0,     0,    51,     0,    43,    34,
      35,    33,     0,    36,    37,    38,    39,     0,    31,     0,
      59,    45,     0,    45,    45,    45,    22,    20,     0,    18,
      67,     0,    76,    72,    74,    77,    79,     0,   163,     0,
      49,     0,    40,    26,    83,     0,    57,     0,     0,     0,
       0,     0,    21,    27,    83,   166,   165,     0,   111,     0,
       0,     0,     0,     0,     0,     0,    84,    86,    97,     0,
     101,   102,     0,     0,    30,    32,     0,    32,    32,    32,
       0,    50,   110,    81,     0,    83,     0,     0,    98,    28,
      85,    99,     0,     0,     0,     0,     0,     0,     0,   100,
       0,    56,     0,     0,     0,    29,     0,    83,     0,   117,
      83,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    82,     0,   118,     0,     0,    91,     0,     0,     0,
      87,     0,    88,     0,     0,   112,   116,    96,    93,    95,
      94,    89,    90,    92,     0,   113,    83,   115,     0,   114
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -248,  -248,  -248,   439,  -248,    11,    91,  -248,   294,  -248,
     -41,   144,  -150,   222,  -248,   -57,   312,     1,  -248,  -248,
    -248,  -248,  -248,  -248,  -154,  -103,  -248,  -248,  -248,  -248,
    -248,   291,  -248,   353,   298,  -248,  -247,  -248,   207,    13,
     463,  -248,   148,  -248,  -248,    46,  -248,  -248,     0,     4,
    -235,  -248,  -248,  -248
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    10,    11,    12,    13,    36,   101,   115,   116,    15,
      16,   102,   217,   218,    18,    95,    96,    42,    20,    21,
     112,   104,    22,    99,   105,   106,    23,   175,    81,    82,
     126,   127,   128,   129,   130,   264,   265,   266,   267,   268,
      25,   269,   270,   345,   271,   131,    84,    85,    86,    87,
      88,    28,    29,   204
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      26,    19,   165,   154,    27,   219,   119,   280,   240,   273,
      53,    26,    19,    24,   110,    27,   260,   316,    26,   273,
      38,    30,    27,    59,    24,   108,   231,     2,     3,    45,
     108,   273,   317,    31,   318,   166,   100,    48,   308,    33,
       2,     3,   151,     2,     3,    34,   161,    35,   319,   100,
     273,    54,   100,    97,    26,   103,   111,    32,    27,    57,
     322,     8,   226,   324,    97,    46,   227,   107,    47,   162,
     117,   169,   273,   155,     8,   273,   258,     8,   241,     2,
       3,   259,   260,    37,   261,   262,   346,    32,    41,    32,
     109,    14,    83,    89,   276,   168,   133,   134,    39,   348,
      32,   164,    14,   173,   174,    26,   103,   156,   118,    27,
     157,   273,   228,   111,   246,   243,   165,   301,   107,   245,
     120,   121,   122,   123,   124,   300,   132,   302,   303,   304,
     135,   136,   137,   138,   139,   140,   141,   142,    57,   153,
      41,   243,   263,   244,    17,   245,    44,   143,   144,   145,
     146,   147,   148,   149,   150,    17,    48,    97,   253,    26,
     103,    55,   245,    27,   247,    49,   249,   250,   251,   159,
     183,   160,   107,   165,   146,   147,   148,   149,   150,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   253,   244,
     254,   245,   245,   254,    64,   245,    65,    66,    67,    68,
      69,    70,    71,    72,    73,   156,    56,    57,   176,    26,
     103,    50,    97,    27,    97,    97,    97,   237,   156,    51,
     238,   275,   107,     2,     3,   156,   156,   156,   277,   278,
     279,    52,   100,    58,   272,   148,   149,   150,    26,   103,
      32,   239,    27,    60,   272,    74,    61,    75,    76,    62,
      63,   107,   133,   134,    77,    78,   272,     8,    79,    90,
     171,   172,    80,   178,   179,    91,    26,   103,   181,   182,
      27,    62,   223,   255,    92,   272,   232,   182,    93,   107,
      94,    98,   113,   114,    62,    47,   135,   136,   137,   138,
     139,   140,   141,   142,   282,   158,   284,   272,   286,   287,
     272,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   163,   167,   170,   180,   146,   147,   148,   149,   150,
     205,   220,   207,   133,   134,   152,   221,   222,   312,   224,
     225,   133,   134,   230,   125,   234,   272,   209,   210,   211,
     212,   213,   214,   215,   216,   236,   242,   325,   248,   327,
     328,   329,   252,   331,   281,   333,   334,   135,   136,   137,
     138,   139,   140,   141,   142,   135,   136,   137,   138,   139,
     140,   141,   142,   257,   143,   144,   145,   146,   147,   148,
     149,   150,   143,   144,   145,   146,   147,   148,   149,   150,
     133,   134,   283,   285,   288,   289,   256,   291,   299,   305,
     344,    64,   184,    65,    66,    67,    68,    69,    70,    71,
      72,    73,   306,    64,   313,    65,    66,    67,    68,    69,
      70,    71,    72,    73,   135,   136,   137,   138,   139,   140,
     141,   142,   314,   315,   320,   321,   323,   330,   332,   335,
      40,   143,   144,   145,   146,   147,   148,   149,   150,   133,
     134,   336,    74,   349,    75,    76,   229,   274,   208,   311,
     233,    77,    78,   290,    74,   125,    75,    76,   177,    80,
     235,    43,     0,    77,    78,   137,   138,   139,   140,   141,
     142,    80,   347,   135,   136,   137,   138,   139,   140,   141,
     142,   133,   134,   146,   147,   148,   149,   150,     0,     0,
     143,   144,   145,   146,   147,   148,   149,   150,   292,     0,
       0,     0,     0,   309,     0,   310,     0,   293,   294,   295,
     296,   297,     0,   298,     0,   135,   136,   137,   138,   139,
     140,   141,   142,   133,   134,    46,     0,     0,    47,     0,
       0,     0,   143,   144,   145,   146,   147,   148,   149,   150,
       0,     0,     0,     0,     0,     0,     0,   307,     0,     0,
       0,     0,     0,     0,   133,   134,     0,   135,   136,   137,
     138,   139,   140,   141,   142,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   143,   144,   145,   146,   147,   148,
     149,   150,     0,     0,     0,   133,   134,   206,   135,   136,
     137,   138,   139,   140,   141,   142,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   143,   144,   145,   146,   147,
     148,   149,   150,     0,     0,     0,   133,   134,   326,   135,
     136,   137,   138,   139,   140,   141,   142,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   143,   144,   145,   146,
     147,   148,   149,   150,     0,     0,     0,   133,   134,   337,
     135,   136,   137,   138,   139,   140,   141,   142,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   143,   144,   145,
     146,   147,   148,   149,   150,     0,     0,     0,   133,   134,
     338,   135,   136,   137,   138,   139,   140,   141,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   143,   144,
     145,   146,   147,   148,   149,   150,     0,     0,     0,   133,
     134,   339,   135,   136,   137,   138,   139,   140,   141,   142,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   143,
     144,   145,   146,   147,   148,   149,   150,     0,     0,     0,
     133,   134,   340,   135,   136,   137,   138,   139,   140,   141,
     142,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     143,   144,   145,   146,   147,   148,   149,   150,     0,     0,
       0,   133,   134,   341,   135,   136,   137,   138,   139,   140,
     141,   142,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   143,   144,   145,   146,   147,   148,   149,   150,     0,
       0,     0,   133,   134,   342,   135,   136,   137,   138,   139,
     140,   141,   142,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   143,   144,   145,   146,   147,   148,   149,   150,
     133,     0,     0,     0,     0,   343,   135,   136,   137,   138,
     139,   140,   141,   142,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   143,   144,   145,   146,   147,   148,   149,
     150,     0,     0,     0,   135,   136,   137,   138,   139,   140,
     141,   142,     0,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,     1,
       0,     2,     3,   146,   147,   148,   149,   150,     0,     0,
       4,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     135,   136,   137,   138,   139,   140,   141,   142,     0,     0,
       0,     5,     6,     0,     7,     8,     9,   143,   144,   145,
     146,   147,   148,   149,   150,   135,   136,   137,   138,   139,
     140,   141,   142,   135,   136,   137,   138,   139,   140,   141,
     142,     0,     0,   144,   145,   146,   147,   148,   149,   150,
       0,     0,   145,   146,   147,   148,   149,   150
};

static const yytype_int16 yycheck[] =
{
       0,     0,   105,    16,     0,   159,    63,   254,    16,   244,
      39,    11,    11,     0,    55,    11,    10,    68,    18,   254,
       9,    16,    18,    43,    11,    16,   176,     7,     8,    78,
      16,   266,    83,    16,    69,    16,    16,    79,   285,    16,
       7,     8,    84,     7,     8,    16,    16,    16,    83,    16,
     285,    80,    16,    52,    54,    54,    55,    70,    54,    79,
     307,    41,    19,   310,    63,    83,    23,    54,    86,    39,
      59,   112,   307,    86,    41,   310,     4,    41,    86,     7,
       8,     9,    10,    16,    12,    13,    80,    70,    16,    70,
      81,     0,    46,    47,   248,    81,    14,    15,     0,   346,
      70,    81,    11,    44,    45,   105,   105,    82,    62,   105,
      85,   346,    69,   112,    81,    78,   219,    81,   105,    82,
      74,    75,    76,    77,    78,   275,    80,   277,   278,   279,
      48,    49,    50,    51,    52,    53,    54,    55,    79,    93,
      16,    78,    70,    80,     0,    82,    16,    65,    66,    67,
      68,    69,    70,    71,    72,    11,    79,   156,    78,   159,
     159,    80,    82,   159,   221,    79,   223,   224,   225,    80,
      88,    82,   159,   276,    68,    69,    70,    71,    72,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,    78,    80,
      80,    82,    82,    80,    16,    82,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    82,    78,    79,    85,   219,
     219,    79,   221,   219,   223,   224,   225,    82,    82,    16,
      85,    85,   219,     7,     8,    82,    82,    82,    85,    85,
      85,    84,    16,    80,   244,    70,    71,    72,   248,   248,
      70,   205,   248,    16,   254,    67,    78,    69,    70,    83,
      84,   248,    14,    15,    76,    77,   266,    41,    80,    16,
      81,    82,    84,    81,    82,    16,   276,   276,    81,    82,
     276,    83,    84,   237,    16,   285,    81,    82,     6,   276,
      16,    16,    16,    16,    83,    86,    48,    49,    50,    51,
      52,    53,    54,    55,   258,    16,   260,   307,   262,   263,
     310,    54,    55,    65,    66,    67,    68,    69,    70,    71,
      72,    16,    16,    83,    88,    68,    69,    70,    71,    72,
      86,    16,    87,    14,    15,    87,    84,    16,   292,    84,
      84,    14,    15,    78,    80,    23,   346,    57,    58,    59,
      60,    61,    62,    63,    64,    23,    16,   311,    80,   313,
     314,   315,    23,   317,    16,   319,   320,    48,    49,    50,
      51,    52,    53,    54,    55,    48,    49,    50,    51,    52,
      53,    54,    55,    87,    65,    66,    67,    68,    69,    70,
      71,    72,    65,    66,    67,    68,    69,    70,    71,    72,
      14,    15,    24,    80,    78,    81,    87,    78,    78,    81,
      11,    16,    85,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    88,    16,    83,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    48,    49,    50,    51,    52,    53,
      54,    55,    83,    83,    83,    24,    81,    78,    78,    81,
      11,    65,    66,    67,    68,    69,    70,    71,    72,    14,
      15,    81,    67,    81,    69,    70,   172,   245,   156,    83,
     179,    76,    77,   266,    67,    80,    69,    70,   125,    84,
     182,    18,    -1,    76,    77,    50,    51,    52,    53,    54,
      55,    84,   344,    48,    49,    50,    51,    52,    53,    54,
      55,    14,    15,    68,    69,    70,    71,    72,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    56,    -1,
      -1,    -1,    -1,    78,    -1,    80,    -1,    65,    66,    67,
      68,    69,    -1,    71,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    14,    15,    83,    -1,    -1,    86,    -1,
      -1,    -1,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    14,    15,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    -1,    -1,    14,    15,    78,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    -1,    -1,    -1,    14,    15,    78,    48,
      49,    50,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    14,    15,    78,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    -1,    14,    15,
      78,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    -1,    -1,    14,
      15,    78,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    -1,
      14,    15,    78,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    -1,
      -1,    14,    15,    78,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,    -1,
      -1,    -1,    14,    15,    78,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    69,    70,    71,    72,
      14,    -1,    -1,    -1,    -1,    78,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    65,    66,    67,    68,    69,    70,    71,    72,     5,
      -1,     7,     8,    68,    69,    70,    71,    72,    -1,    -1,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    37,    38,    -1,    40,    41,    42,    65,    66,    67,
      68,    69,    70,    71,    72,    48,    49,    50,    51,    52,
      53,    54,    55,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,    67,    68,    69,    70,    71,    72
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     7,     8,    16,    37,    38,    40,    41,    42,
      90,    91,    92,    93,    95,    98,    99,   100,   103,   106,
     107,   108,   111,   115,   128,   129,   137,   138,   140,   141,
      16,    16,    70,    16,    16,    16,    94,    16,    94,     0,
      92,    16,   106,   129,    16,    78,    83,    86,    79,    79,
      79,    16,    84,    39,    80,    80,    78,    79,    80,    43,
      16,    78,    83,    84,    16,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    67,    69,    70,    76,    77,    80,
      84,   117,   118,   134,   135,   136,   137,   138,   139,   134,
      16,    16,    16,     6,    16,   104,   105,   106,    16,   112,
      16,    95,   100,   106,   110,   113,   114,   128,    16,    81,
      99,   106,   109,    16,    16,    96,    97,    94,   134,   104,
     134,   134,   134,   134,   134,    80,   119,   120,   121,   122,
     123,   134,   134,    14,    15,    48,    49,    50,    51,    52,
      53,    54,    55,    65,    66,    67,    68,    69,    70,    71,
      72,    84,    87,   134,    16,    86,    82,    85,    16,    80,
      82,    16,    39,    16,    81,   114,    16,    16,    81,    99,
      83,    81,    82,    44,    45,   116,    85,   122,    81,    82,
      88,    81,    82,    88,    85,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   142,    86,    78,    87,   105,    57,
      58,    59,    60,    61,    62,    63,    64,   101,   102,   113,
      16,    84,    16,    84,    84,    84,    19,    23,    69,    97,
      78,   101,    81,   120,    23,   123,    23,    82,    85,   134,
      16,    86,    16,    78,    80,    82,    81,   104,    80,   104,
     104,   104,    23,    78,    80,   134,    87,    87,     4,     9,
      10,    12,    13,    70,   124,   125,   126,   127,   128,   130,
     131,   133,   137,   139,   102,    85,   113,    85,    85,    85,
     125,    16,   134,    24,   134,    80,   134,   134,    78,    81,
     127,    78,    56,    65,    66,    67,    68,    69,    71,    78,
     101,    81,   101,   101,   101,    81,    88,    80,   125,    78,
      80,    83,   134,    83,    83,    83,    68,    83,    69,    83,
      83,    24,   125,    81,   125,   134,    78,   134,   134,   134,
      78,   134,    78,   134,   134,    81,    81,    78,    78,    78,
      78,    78,    78,    78,    11,   132,    80,   131,   125,    81
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    89,    90,    90,    91,    91,    92,    92,    92,    92,
      92,    92,    92,    92,    93,    94,    94,    95,    96,    96,
      97,    97,    97,    97,    98,    98,    99,    99,   100,   100,
     101,   101,   101,   102,   102,   102,   102,   102,   102,   102,
     102,   103,   103,   104,   104,   104,   105,   105,   106,   105,
     105,   107,   108,   108,   109,   109,   110,   111,   111,   112,
     112,   113,   113,   114,   114,   114,   114,   115,   116,   116,
     117,   118,   119,   119,   120,   120,   121,   122,   122,   123,
     123,   124,   124,   125,   125,   126,   126,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   128,   128,   129,   129,   129,   129,   129,
     130,   130,   131,   131,   132,   132,   133,   133,   133,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   136,   136,   137,   137,   137,   138,
     138,   138,   138,   139,   140,   141,   142,   142,   142
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     5,     3,     1,
       3,     4,     3,     1,     1,     1,     7,     7,     9,     9,
       3,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     3,     1,     0,     2,     2,     2,     4,
       6,     6,     5,     4,     2,     1,     6,     7,     5,     3,
       1,     2,     1,     1,     1,     1,     1,     6,     1,     1,
       3,     3,     3,     1,     3,     1,     3,     3,     1,     3,
       1,     2,     4,     0,     1,     2,     1,     4,     4,     5,
       5,     4,     5,     5,     5,     5,     5,     1,     2,     2,
       2,     1,     1,     3,     2,     3,     3,     3,     4,     2,
       2,     1,     5,     6,     4,     2,     5,     3,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     4,     4,     7,     3,     1,     0
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
  YY_USE (yykind);
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
  case 3: /* programa: globals  */
#line 136 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                   {
	for(auto stmt : *((yyvsp[0].nodes))) {
		program->addChild(stmt);
	}
}
#line 2224 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 4: /* globals: globals global  */
#line 142 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                         {
	if ((yyvsp[0].node)) {
		(yyvsp[-1].nodes)->push_back((yyvsp[0].node));
	}
}
#line 2234 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 5: /* globals: global  */
#line 148 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                 {
	(yyval.nodes) = new vector<Node*>();
	if ((yyvsp[0].node)) {
		(yyvsp[0].node)->setLocation((yylsp[0]));
		(yyval.nodes)->push_back((yyvsp[0].node));
	}
}
#line 2246 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 14: /* use: TOK_USE string_chain ';'  */
#line 166 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                               {
	parseUseFile(join_strings(*(yyvsp[-1].strings), "."), (yylsp[-2]));
	(yyval.node) = NULL;
}
#line 2255 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 15: /* string_chain: string_chain '.' TOK_IDENTIFIER  */
#line 171 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                   {
	(yyval.strings) = (yyvsp[-2].strings);
	(yyval.strings)->push_back((yyvsp[0].ident));
}
#line 2264 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 16: /* string_chain: TOK_IDENTIFIER  */
#line 176 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                  {
	(yyval.strings) = new vector<string>();
	(yyval.strings)->push_back((yyvsp[0].ident));
}
#line 2273 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 17: /* enum: TOK_ENUM TOK_IDENTIFIER '{' enum_items '}'  */
#line 181 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                      {
	(yyval.node) = new Enum((yyvsp[-3].ident), std::move(*(yyvsp[-1].nodes)), (yylsp[-3]));
}
#line 2281 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 18: /* enum_items: enum_items ',' enum_item  */
#line 185 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                             {
	(yyvsp[-2].nodes)->push_back((yyvsp[0].node));
	(yyval.nodes) = (yyvsp[-2].nodes);
}
#line 2290 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 19: /* enum_items: enum_item  */
#line 190 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                       {
	(yyval.nodes) = new vector<Node*>();
	(yyval.nodes)->push_back((yyvsp[0].node));
}
#line 2299 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 20: /* enum_item: TOK_IDENTIFIER '=' TOK_INTEGER  */
#line 195 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                     {
	(yyval.node) = new NamedConst((yyvsp[-2].ident), new Int8((yyvsp[0].nint), (yylsp[-2])));
}
#line 2307 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 21: /* enum_item: TOK_IDENTIFIER '=' '-' TOK_INTEGER  */
#line 199 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                         {
	(yyval.node) = new NamedConst((yyvsp[-3].ident), new Int8((yyvsp[0].nint) * -1, (yylsp[-3])));
}
#line 2315 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 22: /* enum_item: TOK_IDENTIFIER '=' TOK_UINTEGER  */
#line 203 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                      {
	(yyval.node) = new NamedConst((yyvsp[-2].ident), new UInt8((yyvsp[0].unint), (yylsp[-2])));
}
#line 2323 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 23: /* enum_item: TOK_IDENTIFIER  */
#line 207 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                               {
	(yyval.node) = new NamedConst((yyvsp[0].ident), (yylsp[0]));
}
#line 2331 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 26: /* function_decl: TOK_IDENTIFIER TOK_IDENTIFIER '(' function_params ')' function_attributes ';'  */
#line 213 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                                                            {
	FunctionDecl *func = new FunctionDecl(buildTypes->getType((yyvsp[-6].ident), true), (yyvsp[-5].ident), (yyvsp[-3].fps), (yylsp[-5]));
	func->setAttributes((yyvsp[-1].fattrs));
	(yyval.node) = func;
}
#line 2341 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 27: /* function_decl: pointer_type TOK_IDENTIFIER '(' function_params ')' function_attributes ';'  */
#line 219 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                                                          {
	FunctionDecl *func = new FunctionDecl((yyvsp[-6].dtype), (yyvsp[-5].ident), (yyvsp[-3].fps), (yylsp[-5]));
	func->setAttributes((yyvsp[-1].fattrs));
	(yyval.node) = func;
}
#line 2351 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 28: /* function_impl: TOK_IDENTIFIER TOK_IDENTIFIER '(' function_params ')' function_attributes '{' stmts '}'  */
#line 225 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                                                                          {
	FunctionImpl *func = new FunctionImpl(buildTypes->getType((yyvsp[-8].ident), true), (yyvsp[-7].ident), (yyvsp[-5].fps),
		std::move(*(yyvsp[-1].nodes)), (yylsp[-7]), (yylsp[0])); 
	func->setAttributes((yyvsp[-3].fattrs));
	(yyval.node) = func;
}
#line 2362 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 29: /* function_impl: pointer_type TOK_IDENTIFIER '(' function_params ')' function_attributes '{' stmts '}'  */
#line 232 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                                                                        {
	FunctionImpl *func = new FunctionImpl((yyvsp[-8].dtype), (yyvsp[-7].ident), (yyvsp[-5].fps),
		std::move(*(yyvsp[-1].nodes)), (yylsp[-7]), (yylsp[0]));
	func->setAttributes((yyvsp[-3].fattrs));
	(yyval.node) = func;
}
#line 2373 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 30: /* function_attributes: function_attributes ',' function_attribute  */
#line 239 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                         {
	(yyvsp[-2].fattrs)->addAttribute((yyvsp[0].fattr));
	(yyval.fattrs) = (yyvsp[-2].fattrs);
}
#line 2382 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 31: /* function_attributes: function_attribute  */
#line 244 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                             {
	(yyval.fattrs) = new FunctionAttributes();
	(yyval.fattrs)->addAttribute((yyvsp[0].fattr));
}
#line 2391 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 32: /* function_attributes: %empty  */
#line 249 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                             {
	(yyval.fattrs) = new FunctionAttributes();
}
#line 2399 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 33: /* function_attribute: TOK_WEAK  */
#line 254 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                        { (yyval.fattr) = new FunctionAttribute(fa_weak, ""); }
#line 2405 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 34: /* function_attribute: TOK_INLINE  */
#line 255 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                { (yyval.fattr) = new FunctionAttribute(fa_inline, ""); }
#line 2411 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 35: /* function_attribute: TOK_NOINLINE  */
#line 256 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                { (yyval.fattr) = new FunctionAttribute(fa_noinline, ""); }
#line 2417 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 36: /* function_attribute: TOK_NAKED  */
#line 257 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                        { (yyval.fattr) = new FunctionAttribute(fa_naked, ""); }
#line 2423 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 37: /* function_attribute: TOK_SIGNAL  */
#line 258 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                { (yyval.fattr) = new FunctionAttribute(fa_signal, ""); }
#line 2429 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 38: /* function_attribute: TOK_DEBUGONLY  */
#line 259 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                { (yyval.fattr) = new FunctionAttribute(fa_debugonly, ""); }
#line 2435 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 39: /* function_attribute: TOK_NOOPT  */
#line 260 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                        { (yyval.fattr) = new FunctionAttribute(fa_noopt, ""); }
#line 2441 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 40: /* function_attribute: TOK_SECTION TOK_IDENTIFIER  */
#line 261 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.fattr) = new FunctionAttribute(fa_section, (yyvsp[0].ident)); }
#line 2447 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 41: /* qualifier: TOK_CONST  */
#line 272 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                { (yyval.nint) = qconst; }
#line 2453 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 42: /* qualifier: TOK_VOLATILE  */
#line 273 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.nint) = qvolatile; }
#line 2459 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 43: /* function_params: function_params ',' function_param  */
#line 275 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                    {
	(yyvsp[-2].fps) -> append((yyvsp[0].fp));
	(yyval.fps) = (yyvsp[-2].fps); 
}
#line 2468 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 44: /* function_params: function_param  */
#line 280 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                {
	FunctionParams *fps = new FunctionParams();
	fps->append((yyvsp[0].fp));
	(yyval.fps) = fps; 
}
#line 2478 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 45: /* function_params: %empty  */
#line 286 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                        {
	FunctionParams *fps = new FunctionParams();
	(yyval.fps) = fps;
}
#line 2487 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 46: /* function_param: TOK_IDENTIFIER TOK_IDENTIFIER  */
#line 291 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                         {
	(yyval.fp) = new Variable((yyvsp[0].ident), buildTypes->getType((yyvsp[-1].ident), true), (yylsp[-1]));
}
#line 2495 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 47: /* function_param: pointer_type TOK_IDENTIFIER  */
#line 295 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                       {
	(yyval.fp) = new Variable((yyvsp[0].ident), (yyvsp[-1].dtype), (yylsp[0]));
}
#line 2503 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 48: /* pointer_type: TOK_IDENTIFIER '*'  */
#line 299 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        {
	(yyval.dtype) = buildTypes->getPointerType((yyvsp[-1].ident), (yylsp[-1]), true);
}
#line 2511 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 49: /* function_param: TOK_IDENTIFIER '[' ']' TOK_IDENTIFIER  */
#line 303 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                 {
	(yyval.fp) = new ParamArray((yyvsp[0].ident), (yyvsp[-3].ident), (yylsp[-3]));
}
#line 2519 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 50: /* function_param: TOK_IDENTIFIER '[' ']' '[' ']' TOK_IDENTIFIER  */
#line 307 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                         {
	(yyval.fp) = new ParamMatrix((yyvsp[0].ident), (yyvsp[-5].ident), (yylsp[-5]));
}
#line 2527 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 51: /* register: TOK_REGISTER TOK_IDENTIFIER TOK_IDENTIFIER TOK_AT expr ';'  */
#line 311 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                                  {
	(yyval.node) = new Pointer((yyvsp[-3].ident), buildTypes->getType((yyvsp[-4].ident), true), (yyvsp[-1].node), (yylsp[-3]));
	(yyval.node)->setQualifier(qvolatile);
}
#line 2536 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 52: /* interface: TOK_INTF TOK_IDENTIFIER '{' interface_decls '}'  */
#line 316 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                      {
	(yyval.node) = new Interface((yyvsp[-3].ident), std::move(*(yyvsp[-1].nodes)), (yylsp[-3]));
}
#line 2544 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 53: /* interface: TOK_INTF TOK_IDENTIFIER '{' '}'  */
#line 320 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                {
	(yyval.node) = new Interface((yyvsp[-2].ident), (yylsp[-2]));
}
#line 2552 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 54: /* interface_decls: interface_decls function_decl  */
#line 324 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                {
	(yyvsp[-1].nodes)->push_back((yyvsp[0].node));
	(yyval.nodes) = (yyvsp[-1].nodes);
}
#line 2561 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 55: /* interface_decls: function_decl  */
#line 329 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                {
	(yyval.nodes) = new vector<Node*>();
	(yyval.nodes)->push_back((yyvsp[0].node));
}
#line 2570 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 56: /* interface_impl: TOK_IDENTIFIER TOK_IMPL TOK_IDENTIFIER '{' type_stmts '}'  */
#line 334 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                                         {
	vector<string> intf;
	intf.push_back((yyvsp[-3].ident));
	UserType *ut = new UserType((yyvsp[-5].ident), std::move(*(yyvsp[-1].nodes)), std::move(intf), (yylsp[-5]));
	(yyval.node) = ut;
}
#line 2581 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 57: /* type: TOK_TYPE TOK_IDENTIFIER TOK_IMPL type_impls '{' type_stmts '}'  */
#line 341 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                          {
	UserType *ut = new UserType((yyvsp[-5].ident), std::move(*(yyvsp[-1].nodes)), std::move(*(yyvsp[-3].strings)), (yylsp[-5]));
	(yyval.node) = ut;
}
#line 2590 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 58: /* type: TOK_TYPE TOK_IDENTIFIER '{' type_stmts '}'  */
#line 346 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                      {
	UserType *ut = new UserType((yyvsp[-3].ident), std::move(*(yyvsp[-1].nodes)), (yylsp[-3]));
	(yyval.node) = ut;
}
#line 2599 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 59: /* type_impls: type_impls ',' TOK_IDENTIFIER  */
#line 351 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                           {
	(yyvsp[-2].strings)->push_back((yyvsp[0].ident));
	(yyval.strings) = (yyvsp[-2].strings);
}
#line 2608 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 60: /* type_impls: TOK_IDENTIFIER  */
#line 356 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                            {
	(yyval.strings) = new vector<string>();
	(yyval.strings)->push_back((yyvsp[0].ident));
}
#line 2617 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 61: /* type_stmts: type_stmts type_stmt  */
#line 361 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                  {
	if ((yyvsp[0].node))
		(yyval.nodes)->push_back((yyvsp[0].node));
}
#line 2626 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 62: /* type_stmts: type_stmt  */
#line 366 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                       {
	(yyval.nodes) = new vector<Node*>();
	if ((yyvsp[0].node))
		(yyval.nodes)->push_back((yyvsp[0].node));
}
#line 2636 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 67: /* bind: TOK_BIND string_chain TOK_TO string_chain bind_scope ';'  */
#line 377 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                               {
	string sid = join_strings(*(yyvsp[-4].strings), ".");
	string sto = join_strings(*(yyvsp[-2].strings), ".");
	injections.insert({sto, new Injection(sid, sto, BindScope((yyvsp[-1].nint)), (yylsp[-4]))});
	(yyval.node) = NULL;
}
#line 2647 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 68: /* bind_scope: TOK_SINGLETON  */
#line 384 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                           { (yyval.nint) = bs_singleton; }
#line 2653 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 69: /* bind_scope: TOK_TRANSIENT  */
#line 385 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                   { (yyval.nint) = bs_transient; }
#line 2659 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 70: /* array: '{' elements '}'  */
#line 387 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                { (yyval.aes) = (yyvsp[-1].aes); }
#line 2665 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 71: /* matrix: '{' melements '}'  */
#line 388 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                { (yyval.mes) = (yyvsp[-1].mes); }
#line 2671 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 72: /* melements: melements ',' melement  */
#line 390 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                   {
	(yyvsp[-2].mes)->append((yyvsp[0].me));
	(yyval.mes) = (yyvsp[-2].mes);
}
#line 2680 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 73: /* melements: melement  */
#line 395 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                     {
	MatrixElements *mes = new MatrixElements((yyloc));
	mes->append((yyvsp[0].me));
	(yyval.mes) = mes;
}
#line 2690 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 74: /* melement: relements ':' TOK_INTEGER  */
#line 401 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.me) = new MatrixElement((yyvsp[-2].aes), (unsigned)(yyvsp[0].nint)); }
#line 2696 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 75: /* melement: relements  */
#line 402 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                { (yyval.me) = new MatrixElement((yyvsp[0].aes), 1);}
#line 2702 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 76: /* relements: '{' elements '}'  */
#line 404 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.aes) = (yyvsp[-1].aes); }
#line 2708 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 77: /* elements: elements ',' element  */
#line 406 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyvsp[-2].aes)->append((yyvsp[0].ae));
										  (yyval.aes) = (yyvsp[-2].aes); }
#line 2715 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 78: /* elements: element  */
#line 408 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                        { ArrayElements *aes = new ArrayElements((yylsp[0]));
										  aes->append((yyvsp[0].ae));
										  (yyval.aes) = aes; }
#line 2723 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 79: /* element: expr ':' TOK_INTEGER  */
#line 412 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.ae) = new ArrayElement((yyvsp[-2].node), (unsigned)(yyvsp[0].nint)); }
#line 2729 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 80: /* element: expr  */
#line 413 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                        { (yyval.ae) = new ArrayElement((yyvsp[0].node), 1); }
#line 2735 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 81: /* asminline: TOK_ASM TOK_STRING  */
#line 415 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                               { (yyval.node) = new InlineAssembly((yyvsp[0].str), (yylsp[-1])); }
#line 2741 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 82: /* asminline: TOK_ASM TOK_STRING ':' TOK_STRING  */
#line 416 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                              { (yyval.node) = new InlineAssembly((yyvsp[-2].str), (yyvsp[0].str), (yylsp[-3])); }
#line 2747 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 83: /* stmts: %empty  */
#line 418 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
               { (yyval.nodes) = new vector<Node*>(); }
#line 2753 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 85: /* stmts_rec: stmts_rec stmt  */
#line 421 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                           {
	(yyvsp[-1].nodes)->push_back((yyvsp[0].node));
}
#line 2761 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 86: /* stmts_rec: stmt  */
#line 424 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                 {
	(yyval.nodes) = new vector<Node*>();
	(yyval.nodes)->push_back((yyvsp[0].node));
	(yyvsp[0].node)->setLocation((yylsp[0]));
}
#line 2771 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 87: /* stmt: left_value_base '+' '+' ';'  */
#line 430 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new CompoundStore((yyvsp[-3].leftvd), '+', new Int8(1, (yylsp[-3]))); }
#line 2777 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 88: /* stmt: left_value_base '-' '-' ';'  */
#line 431 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                        { (yyval.node) = new CompoundStore((yyvsp[-3].leftvd), '-', new Int8(1, (yylsp[-3]))); }
#line 2783 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 89: /* stmt: left_value_base '+' '=' expr ';'  */
#line 432 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new CompoundStore((yyvsp[-4].leftvd), '+', (yyvsp[-1].node)); }
#line 2789 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 90: /* stmt: left_value_base '-' '=' expr ';'  */
#line 433 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new CompoundStore((yyvsp[-4].leftvd), '-', (yyvsp[-1].node)); }
#line 2795 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 91: /* stmt: left_value_base TOK_MUL_ASSIGN expr ';'  */
#line 434 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                       { (yyval.node) = new CompoundStore((yyvsp[-3].leftvd), '*', (yyvsp[-1].node)); }
#line 2801 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 92: /* stmt: left_value_base '/' '=' expr ';'  */
#line 435 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new CompoundStore((yyvsp[-4].leftvd), '/', (yyvsp[-1].node)); }
#line 2807 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 93: /* stmt: left_value_base '|' '=' expr ';'  */
#line 436 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new CompoundStore((yyvsp[-4].leftvd), '|', (yyvsp[-1].node)); }
#line 2813 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 94: /* stmt: left_value_base '&' '=' expr ';'  */
#line 437 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new CompoundStore((yyvsp[-4].leftvd), '&', (yyvsp[-1].node)); }
#line 2819 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 95: /* stmt: left_value_base '^' '=' expr ';'  */
#line 438 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new CompoundStore((yyvsp[-4].leftvd), '^', (yyvsp[-1].node)); }
#line 2825 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 96: /* stmt: '*' expr '=' expr ';'  */
#line 439 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                        { (yyval.node) = new PointerStore((yyvsp[-3].node), (yyvsp[-1].node), (yylsp[-3])); }
#line 2831 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 103: /* var_decl: qualifier var_decl_stmt ';'  */
#line 448 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.node) = (yyvsp[-1].node); (yyval.node)->setQualifier((DataQualifier)(yyvsp[-2].nint)); }
#line 2837 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 105: /* var_decl_stmt: left_value_base '=' array  */
#line 451 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                        { (yyval.node) = new Array((yyvsp[-2].leftvd)->ident, (yyvsp[0].aes), (yylsp[-2])); }
#line 2843 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 106: /* var_decl_stmt: left_value_base '=' matrix  */
#line 452 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new Matrix((yyvsp[-2].leftvd)->ident, (yyvsp[0].mes), (yylsp[-2])); }
#line 2849 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 107: /* var_decl_stmt: left_value_base '=' expr  */
#line 453 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                             {
	(yyvsp[-2].leftvd)->value->setToStore(true);
	(yyval.node) = new Scalar((yyvsp[-2].leftvd), (yyvsp[0].node));
}
#line 2858 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 108: /* var_decl_stmt: pointer_type TOK_IDENTIFIER '=' expr  */
#line 458 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                      {
	auto *lv = new LeftValueData();
	lv->ident = (yyvsp[-2].ident);
	lv->loc = (yylsp[-2]);
	Scalar *pointer = new Scalar(lv, (yyvsp[0].node));
	pointer->setDataType((yyvsp[-3].dtype));
	(yyval.node) = pointer;
}
#line 2871 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 109: /* var_decl_stmt: pointer_type TOK_IDENTIFIER  */
#line 467 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                      {
	NullPointer *nullValue = new NullPointer((yyvsp[-1].dtype), (yylsp[0]));
	Scalar *pointer = new Scalar((yyvsp[0].ident), nullValue);
	pointer->setDataType((yyvsp[-1].dtype));
	(yyval.node) = pointer;
}
#line 2882 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 110: /* returnblock: TOK_RETURN expr  */
#line 474 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new Return((yyvsp[0].node)); }
#line 2888 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 111: /* returnblock: TOK_RETURN  */
#line 475 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                        { (yyval.node) = new Return((yylsp[0])); }
#line 2894 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 112: /* condblock: TOK_IF expr '{' stmts '}'  */
#line 481 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                      {
	(yyvsp[-3].node)->setLocation((yylsp[-3]));
	(yyval.node) = new If((yyvsp[-3].node), std::move(*(yyvsp[-1].nodes)), (yylsp[-4]));
}
#line 2903 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 113: /* condblock: TOK_IF expr '{' stmts '}' elseblock  */
#line 485 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                {
	(yyvsp[-4].node)->setLocation((yylsp[-4]));
	(yyval.node) = new If((yyvsp[-4].node), std::move(*(yyvsp[-2].nodes)), std::move(*(yyvsp[0].nodes)), (yylsp[-5]));
}
#line 2912 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 114: /* elseblock: TOK_ELSE '{' stmts '}'  */
#line 490 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                   { (yyval.nodes) = (yyvsp[-1].nodes); }
#line 2918 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 115: /* elseblock: TOK_ELSE condblock  */
#line 491 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                               { 
	auto *nodes = new vector<Node*>();
	nodes->push_back((yyvsp[0].node));
	(yyval.nodes) = nodes;
}
#line 2928 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 116: /* whileblock: TOK_WHILE expr '{' stmts '}'  */
#line 501 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                          {
	(yyvsp[-3].node)->setLocation((yylsp[-3]));
	(yyval.node) = new While((yyvsp[-3].node), std::move(*(yyvsp[-1].nodes)), (yylsp[-4]));
}
#line 2937 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 117: /* whileblock: TOK_WHILE expr ';'  */
#line 506 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                {
	(yyvsp[-1].node)->setLocation((yylsp[-1]));
	(yyval.node) = new While((yyvsp[-1].node), (yylsp[-2]));
}
#line 2946 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 118: /* whileblock: TOK_LOOP '{' stmts '}'  */
#line 511 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                    {
	(yyval.node) = new Loop(std::move(*(yyvsp[-1].nodes)), (yylsp[-3]));
}
#line 2954 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 119: /* expr: expr TOK_AND expr  */
#line 520 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                    { (yyval.node) = new BinaryOp((yyvsp[-2].node), TOK_AND, (yyvsp[0].node)); }
#line 2960 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 120: /* expr: expr TOK_OR expr  */
#line 521 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                    { (yyval.node) = new BinaryOp((yyvsp[-2].node), TOK_OR, (yyvsp[0].node)); }
#line 2966 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 121: /* expr: expr EQ_OP expr  */
#line 522 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                    { (yyval.node) = new CmpOp((yyvsp[-2].node), EQ_OP, (yyvsp[0].node), (yylsp[-1])); }
#line 2972 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 122: /* expr: expr NE_OP expr  */
#line 523 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                    { (yyval.node) = new CmpOp((yyvsp[-2].node), NE_OP, (yyvsp[0].node), (yylsp[-1])); }
#line 2978 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 123: /* expr: expr LE_OP expr  */
#line 524 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.node) = new CmpOp((yyvsp[-2].node), LE_OP, (yyvsp[0].node), (yylsp[-1])); }
#line 2984 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 124: /* expr: expr GE_OP expr  */
#line 525 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.node) = new CmpOp((yyvsp[-2].node), GE_OP, (yyvsp[0].node), (yylsp[-1])); }
#line 2990 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 125: /* expr: expr LT_OP expr  */
#line 526 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.node) = new CmpOp((yyvsp[-2].node), LT_OP, (yyvsp[0].node), (yylsp[-1])); }
#line 2996 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 126: /* expr: expr GT_OP expr  */
#line 527 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.node) = new CmpOp((yyvsp[-2].node), GT_OP, (yyvsp[0].node), (yylsp[-1])); }
#line 3002 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 127: /* expr: '!' expr  */
#line 528 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                    { (yyval.node) = new CmpOp((yyvsp[0].node), EQ_OP, new Int1(0, (yylsp[0])), (yylsp[-1])); }
#line 3008 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 128: /* expr: expr '+' expr  */
#line 531 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new BinaryOp((yyvsp[-2].node), '+', (yyvsp[0].node)); }
#line 3014 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 129: /* expr: expr '-' expr  */
#line 532 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new BinaryOp((yyvsp[-2].node), '-', (yyvsp[0].node)); }
#line 3020 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 130: /* expr: expr '|' expr  */
#line 533 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new BinaryOp((yyvsp[-2].node), '|', (yyvsp[0].node)); }
#line 3026 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 131: /* expr: expr '*' expr  */
#line 534 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new BinaryOp((yyvsp[-2].node), '*', (yyvsp[0].node)); }
#line 3032 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 132: /* expr: expr '/' expr  */
#line 535 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new BinaryOp((yyvsp[-2].node), '/', (yyvsp[0].node)); }
#line 3038 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 133: /* expr: expr '%' expr  */
#line 536 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new BinaryOp((yyvsp[-2].node), '%', (yyvsp[0].node)); }
#line 3044 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 134: /* expr: expr '^' expr  */
#line 537 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new BinaryOp((yyvsp[-2].node), '^', (yyvsp[0].node)); }
#line 3050 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 135: /* expr: expr '&' expr  */
#line 538 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new BinaryOp((yyvsp[-2].node), '&', (yyvsp[0].node)); }
#line 3056 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 136: /* expr: expr TOK_LSHIFT expr  */
#line 539 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.node) = new BinaryOp((yyvsp[-2].node), TOK_LSHIFT, (yyvsp[0].node)); }
#line 3062 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 137: /* expr: expr TOK_RSHIFT expr  */
#line 540 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.node) = new BinaryOp((yyvsp[-2].node), TOK_RSHIFT, (yyvsp[0].node)); }
#line 3068 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 138: /* expr: '-' expr  */
#line 541 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.node) = new BinaryOp((yyvsp[0].node), '*', getNodeForIntConst(-1, (yylsp[0]))); }
#line 3074 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 139: /* expr: '~' expr  */
#line 542 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                        { (yyval.node) = new FlipOp((yyvsp[0].node)); }
#line 3080 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 140: /* expr: '&' expr  */
#line 543 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new AddressOf((yyvsp[0].node), (yylsp[0])); }
#line 3086 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 141: /* expr: '*' expr  */
#line 544 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.node) = new Dereference((yyvsp[0].node), (yylsp[0])); }
#line 3092 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 143: /* factor: '(' expr ')'  */
#line 547 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.node) = (yyvsp[-1].node); }
#line 3098 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 144: /* factor: TOK_TRUE  */
#line 548 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new Int1(1, (yylsp[0])); }
#line 3104 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 145: /* factor: TOK_FALSE  */
#line 549 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new Int1(0, (yylsp[0])); }
#line 3110 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 146: /* factor: TOK_CHAR  */
#line 550 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new Char((yyvsp[0].ch), (yylsp[0])); }
#line 3116 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 147: /* factor: TOK_INTEGER  */
#line 551 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = getNodeForIntConst((yyvsp[0].nint), (yylsp[0])); }
#line 3122 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 148: /* factor: TOK_UINTEGER  */
#line 552 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = getNodeForUIntConst((yyvsp[0].unint), (yylsp[0])); }
#line 3128 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 149: /* factor: TOK_FLOAT  */
#line 553 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new Float((yyvsp[0].nfloat), (yylsp[0])); }
#line 3134 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 150: /* factor: TOK_DOUBLE  */
#line 554 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new Double((yyvsp[0].ndouble), (yylsp[0])); }
#line 3140 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 151: /* factor: TOK_LDOUBLE  */
#line 555 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new Float128((yyvsp[0].nldouble), (yylsp[0])); }
#line 3146 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 152: /* factor: TOK_STRING  */
#line 556 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                { (yyval.node) = new StringConst("conststr", (yyvsp[0].str), (yylsp[0])); }
#line 3152 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 154: /* left_value: left_value_base  */
#line 567 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                        { (yyval.node) = (yyvsp[0].leftvd)->value; }
#line 3158 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 159: /* ident_access: TOK_IDENTIFIER  */
#line 574 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                  {
	auto *lvd = new LeftValueData();
	lvd->ident = (yyvsp[0].ident);
	lvd->loc = (yylsp[0]);
	// temporarily set as a load; can be changed below
	lvd->value = new Load((yyvsp[0].ident), (yylsp[0]));
	(yyval.leftvd) = lvd;
}
#line 3171 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 160: /* ident_access: ident_access '.' TOK_IDENTIFIER  */
#line 583 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                       {
	(yyvsp[-2].leftvd)->ident = (yyvsp[0].ident);
	(yyvsp[-2].leftvd)->stem = (yyvsp[-2].leftvd)->value;
	(yyvsp[-2].leftvd)->value = new FieldAccess((yyvsp[-2].leftvd)->stem, (yyvsp[0].ident), (yylsp[0]));
	(yyval.leftvd) = (yyvsp[-2].leftvd);
}
#line 3182 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 161: /* ident_access: array_access '.' TOK_IDENTIFIER  */
#line 590 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                       {
	(yyvsp[-2].leftvd)->ident = (yyvsp[0].ident);
	(yyvsp[-2].leftvd)->stem = (yyvsp[-2].leftvd)->value;
	(yyvsp[-2].leftvd)->value = new FieldAccess((yyvsp[-2].leftvd)->stem, (yyvsp[0].ident), (yylsp[0]));
	(yyval.leftvd) = (yyvsp[-2].leftvd);
}
#line 3193 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 162: /* ident_access: matrix_access '.' TOK_IDENTIFIER  */
#line 597 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                        {
	(yyvsp[-2].leftvd)->ident = (yyvsp[0].ident);
	(yyvsp[-2].leftvd)->stem = (yyvsp[-2].leftvd)->value;
	(yyvsp[-2].leftvd)->value = new FieldAccess((yyvsp[-2].leftvd)->stem, (yyvsp[0].ident), (yylsp[0]));
	(yyval.leftvd) = (yyvsp[-2].leftvd);
}
#line 3204 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 163: /* function_call: ident_access '(' paramscall ')'  */
#line 604 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                    {
	if ((yyvsp[-3].leftvd)->stem == NULL) { // is a simple global call
		if ((yyvsp[-3].leftvd)->ident == "copy" && (yyvsp[-1].pc)->getNumParams() == 1)
			(yyval.node) = new MemCopy((yyvsp[-1].pc)->getParamElement(0));
		else if ((yyvsp[-3].leftvd)->ident == "bitcast" && (yyvsp[-1].pc)->getNumParams() == 2) {
			Node *nodeTy = (yyvsp[-1].pc)->getParamElement(1);
			Load *load = dynamic_cast<Load*>(nodeTy);
			if (load && buildTypes->getType(load->getName()) != BuildTypes::undefinedType) {
				DataType dt = buildTypes->getType(load->getName());
				(yyval.node) = new BitCast((yyvsp[-1].pc)->getParamElement(0), dt);
			} else {
				yyerrorcpp("Wrong call to bitcast(var, new_type)", (yyvsp[-3].leftvd)->value);
				(yyval.node) = NULL;
			}
		} else {
			(yyval.node) = new FunctionCall((yyvsp[-3].leftvd)->ident, (yyvsp[-1].pc), (yylsp[-3]));
		}
	} else { // call to a function of a User type
		delete (yyvsp[-3].leftvd)->value; // the last ident is the function name; ignore the previous access
		(yyval.node) = new FunctionCall((yyvsp[-3].leftvd)->ident, (yyvsp[-1].pc), (yyvsp[-3].leftvd)->stem, (yylsp[-3]));
	}
	(yyval.node)->setLocation((yylsp[-3]));
}
#line 3232 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 164: /* array_access: left_value_base '[' expr ']'  */
#line 628 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                {
	(yyvsp[-3].leftvd)->stem = (yyvsp[-3].leftvd)->value;
	(yyvsp[-3].leftvd)->value = new ArrayAccess((yyvsp[-3].leftvd)->stem, (yyvsp[-1].node));
	(yyval.leftvd) = (yyvsp[-3].leftvd);
}
#line 3242 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 165: /* matrix_access: left_value_base '[' expr ']' '[' expr ']'  */
#line 634 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                                                     {
	(yyvsp[-6].leftvd)->stem = (yyvsp[-6].leftvd)->value;
	(yyvsp[-6].leftvd)->value = new MatrixAccess((yyvsp[-6].leftvd)->stem, (yyvsp[-4].node), (yyvsp[-1].node));
	(yyval.leftvd) = (yyvsp[-6].leftvd);
}
#line 3252 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 166: /* paramscall: paramscall ',' expr  */
#line 640 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                                 {
	(yyvsp[-2].pc)->append((yyvsp[0].node));
	(yyval.pc) = (yyvsp[-2].pc);
}
#line 3261 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 167: /* paramscall: expr  */
#line 645 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                  {
	ParamsCall *pc = new ParamsCall();
	pc->append((yyvsp[0].node));
	(yyval.pc) = pc;
}
#line 3271 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;

  case 168: /* paramscall: %empty  */
#line 651 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"
                    { (yyval.pc) = new ParamsCall(); }
#line 3277 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"
    break;


#line 3281 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.cpp"

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

#line 653 "/home/alisson/Downloads/robcmp-svds_and_rp2040/build-pointer-test/Language_gen.y"


Node *get_compound_node(Node *load, char op, Node *right) {
	if (dynamic_cast<Load*>(load))
		return new Scalar(load->getName(), new BinaryOp(load, op, right));
	else if (LoadArray *la = dynamic_cast<LoadArray*>(load))
		return new UpdateArray(load->getName(), la->getPosition(), new BinaryOp(load, op, right), load->getLoc());
	else if (LoadMatrix *lm = dynamic_cast<LoadMatrix*>(load))
		return new UpdateMatrix(load->getName(), lm->getPosition(), lm->getPosition2(), new BinaryOp(load, op, right), load->getLoc());
	else
		assert(false && "Unknown load node.");
}

string join_strings(const vector<string>& strings, const string& separator) {
	string result = strings[0];
	for(int i = 1; i < strings.size(); i++)
		result += separator + strings[i];
	return result;
}
