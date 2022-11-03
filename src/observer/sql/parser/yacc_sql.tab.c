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




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  size_t values_length;
  size_t value_length_array[MAX_RECORD_NUM];
  Values values_array[MAX_RECORD_NUM];
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  char id[MAX_NUM];
  struct ParserContext *parent_context;
  struct ParserContext *child_context;
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.values_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


<<<<<<< HEAD
#line 131 "yacc_sql.tab.c"
=======
#line 132 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end

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

<<<<<<< HEAD
#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_DESC = 10,                      /* DESC  */
  YYSYMBOL_SHOW = 11,                      /* SHOW  */
  YYSYMBOL_SYNC = 12,                      /* SYNC  */
  YYSYMBOL_INSERT = 13,                    /* INSERT  */
  YYSYMBOL_DELETE = 14,                    /* DELETE  */
  YYSYMBOL_UPDATE = 15,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 16,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 17,                    /* RBRACE  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 19,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 20,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 21,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 22,                     /* INT_T  */
  YYSYMBOL_STRING_T = 23,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 24,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 25,                    /* DATE_T  */
  YYSYMBOL_HELP = 26,                      /* HELP  */
  YYSYMBOL_EXIT = 27,                      /* EXIT  */
  YYSYMBOL_DOT = 28,                       /* DOT  */
  YYSYMBOL_INTO = 29,                      /* INTO  */
  YYSYMBOL_VALUES = 30,                    /* VALUES  */
  YYSYMBOL_FROM = 31,                      /* FROM  */
  YYSYMBOL_WHERE = 32,                     /* WHERE  */
  YYSYMBOL_NOT = 33,                       /* NOT  */
  YYSYMBOL_LIKE = 34,                      /* LIKE  */
  YYSYMBOL_AND = 35,                       /* AND  */
  YYSYMBOL_SET = 36,                       /* SET  */
  YYSYMBOL_ON = 37,                        /* ON  */
  YYSYMBOL_LOAD = 38,                      /* LOAD  */
  YYSYMBOL_DATA = 39,                      /* DATA  */
  YYSYMBOL_INFILE = 40,                    /* INFILE  */
  YYSYMBOL_EQ = 41,                        /* EQ  */
  YYSYMBOL_LT = 42,                        /* LT  */
  YYSYMBOL_GT = 43,                        /* GT  */
  YYSYMBOL_LE = 44,                        /* LE  */
  YYSYMBOL_GE = 45,                        /* GE  */
  YYSYMBOL_NE = 46,                        /* NE  */
  YYSYMBOL_COUNT_F = 47,                   /* COUNT_F  */
  YYSYMBOL_AVG_F = 48,                     /* AVG_F  */
  YYSYMBOL_MAX_F = 49,                     /* MAX_F  */
  YYSYMBOL_MIN_F = 50,                     /* MIN_F  */
  YYSYMBOL_SUM_F = 51,                     /* SUM_F  */
  YYSYMBOL_NUMBER = 52,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 53,                     /* FLOAT  */
  YYSYMBOL_DATE_STR = 54,                  /* DATE_STR  */
  YYSYMBOL_ID = 55,                        /* ID  */
  YYSYMBOL_PATH = 56,                      /* PATH  */
  YYSYMBOL_SSS = 57,                       /* SSS  */
  YYSYMBOL_STAR = 58,                      /* STAR  */
  YYSYMBOL_STRING_V = 59,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 60,                  /* $accept  */
  YYSYMBOL_commands = 61,                  /* commands  */
  YYSYMBOL_command = 62,                   /* command  */
  YYSYMBOL_exit = 63,                      /* exit  */
  YYSYMBOL_help = 64,                      /* help  */
  YYSYMBOL_sync = 65,                      /* sync  */
  YYSYMBOL_begin = 66,                     /* begin  */
  YYSYMBOL_commit = 67,                    /* commit  */
  YYSYMBOL_rollback = 68,                  /* rollback  */
  YYSYMBOL_drop_table = 69,                /* drop_table  */
  YYSYMBOL_show_tables = 70,               /* show_tables  */
  YYSYMBOL_show_index = 71,                /* show_index  */
  YYSYMBOL_desc_table = 72,                /* desc_table  */
  YYSYMBOL_create_index = 73,              /* create_index  */
  YYSYMBOL_drop_index = 74,                /* drop_index  */
  YYSYMBOL_create_table = 75,              /* create_table  */
  YYSYMBOL_attr_def_list = 76,             /* attr_def_list  */
  YYSYMBOL_attr_def = 77,                  /* attr_def  */
  YYSYMBOL_number = 78,                    /* number  */
  YYSYMBOL_type = 79,                      /* type  */
  YYSYMBOL_ID_get = 80,                    /* ID_get  */
  YYSYMBOL_insert = 81,                    /* insert  */
  YYSYMBOL_values_list = 82,               /* values_list  */
  YYSYMBOL_values = 83,                    /* values  */
  YYSYMBOL_value_list = 84,                /* value_list  */
  YYSYMBOL_value = 85,                     /* value  */
  YYSYMBOL_delete = 86,                    /* delete  */
  YYSYMBOL_update = 87,                    /* update  */
  YYSYMBOL_select = 88,                    /* select  */
  YYSYMBOL_select_attr = 89,               /* select_attr  */
  YYSYMBOL_aggrefunc_list = 90,            /* aggrefunc_list  */
  YYSYMBOL_aggrefunc = 91,                 /* aggrefunc  */
  YYSYMBOL_aggrefunc_type = 92,            /* aggrefunc_type  */
  YYSYMBOL_attr_list = 93,                 /* attr_list  */
  YYSYMBOL_rel_list = 94,                  /* rel_list  */
  YYSYMBOL_where = 95,                     /* where  */
  YYSYMBOL_condition_list = 96,            /* condition_list  */
  YYSYMBOL_condition = 97,                 /* condition  */
  YYSYMBOL_comOp = 98,                     /* comOp  */
  YYSYMBOL_load_data = 99                  /* load_data  */
=======
/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    TABLE = 261,
    TABLES = 262,
    INDEX = 263,
    SELECT = 264,
    DESC = 265,
    SHOW = 266,
    SYNC = 267,
    INSERT = 268,
    DELETE = 269,
    UPDATE = 270,
    LBRACE = 271,
    RBRACE = 272,
    COMMA = 273,
    TRX_BEGIN = 274,
    TRX_COMMIT = 275,
    TRX_ROLLBACK = 276,
    INT_T = 277,
    STRING_T = 278,
    FLOAT_T = 279,
    DATE_T = 280,
    HELP = 281,
    EXIT = 282,
    DOT = 283,
    INTO = 284,
    VALUES = 285,
    FROM = 286,
    WHERE = 287,
    NOT = 288,
    LIKE = 289,
    AND = 290,
    SET = 291,
    ON = 292,
    LOAD = 293,
    DATA = 294,
    INFILE = 295,
    EQ = 296,
    LT = 297,
    GT = 298,
    LE = 299,
    GE = 300,
    NE = 301,
    NUMBER = 302,
    FLOAT = 303,
    DATE_STR = 304,
    ID = 305,
    PATH = 306,
    SSS = 307,
    STAR = 308,
    STRING_V = 309
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 113 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;

#line 249 "yacc_sql.tab.c"

>>>>>>> support parsing sub select of update in front-end
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
<<<<<<< HEAD
<<<<<<< HEAD
#define YYLAST   193
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#define YYLAST   189
=======
#define YYLAST   174
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
#define YYLAST   184
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
<<<<<<< HEAD
<<<<<<< HEAD
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
<<<<<<< HEAD
#define YYNSTATES  201
=======
#define YYNSTATES  199
=======
#define YYNNTS  41
=======
#define YYNNTS  42
>>>>>>> update without aggregation-func
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
<<<<<<< HEAD
#define YYNSTATES  185
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
#define YYNSTATES  189
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   314


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
      55,    56,    57,    58,    59
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
<<<<<<< HEAD
       0,   145,   145,   147,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   172,   177,   182,   188,   194,   200,   206,   212,
     217,   224,   231,   239,   246,   255,   257,   261,   272,   285,
     288,   289,   290,   291,   294,   303,   319,   321,   326,   334,
     336,   341,   344,   347,   352,   359,   369,   379,   398,   403,
<<<<<<< HEAD
     408,   413,   418,   421,   423,   429,   434,   439,   444,   451,
     452,   453,   454,   455,   457,   459,   466,   475,   477,   481,
     483,   487,   489,   494,   518,   538,   558,   580,   601,   622,
     644,   645,   646,   647,   648,   649,   650,   651,   655
=======
     408,   413,   416,   418,   424,   429,   434,   439,   446,   447,
     448,   449,   450,   452,   454,   461,   470,   472,   476,   478,
     482,   484,   489,   513,   533,   553,   575,   596,   617,   639,
     640,   641,   642,   643,   644,   645,   646,   650
=======
       0,   140,   140,   142,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   167,   172,   177,   183,   189,   195,   201,   207,
     212,   219,   226,   234,   241,   250,   252,   256,   267,   280,
     283,   284,   285,   286,   289,   298,   314,   316,   321,   329,
<<<<<<< HEAD
     331,   336,   339,   342,   347,   354,   366,   377,   380,   384,
     386,   398,   411,   415,   434,   439,   444,   450,   452,   459,
     468,   470,   474,   476,   480,   482,   487,   511,   531,   551,
     573,   594,   615,   637,   638,   639,   640,   641,   642,   643,
     644,   648
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
     331,   336,   339,   342,   347,   356,   368,   380,   387,   389,
     394,   396,   408,   421,   425,   444,   449,   454,   460,   462,
     469,   478,   480,   484,   486,   490,   492,   497,   522,   542,
     562,   584,   605,   626,   648,   649,   650,   651,   652,   653,
     654,   655,   659
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
<<<<<<< HEAD
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "NOT", "LIKE",
  "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE",
  "GE", "NE", "COUNT_F", "AVG_F", "MAX_F", "MIN_F", "SUM_F", "NUMBER",
  "FLOAT", "DATE_STR", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "show_index", "desc_table",
  "create_index", "drop_index", "create_table", "attr_def_list",
  "attr_def", "number", "type", "ID_get", "insert", "values_list",
  "values", "value_list", "value", "delete", "update", "select",
  "select_attr", "aggrefunc_list", "aggrefunc", "aggrefunc_type",
  "attr_list", "rel_list", "where", "condition_list", "condition", "comOp",
  "load_data", YY_NULLPTR
=======
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE",
  "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "HELP", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "NOT", "LIKE", "AND", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE",
  "NUMBER", "FLOAT", "DATE_STR", "ID", "PATH", "SSS", "STAR", "STRING_V",
  "$accept", "commands", "command", "exit", "help", "sync", "begin",
  "commit", "rollback", "drop_table", "show_tables", "show_index",
  "desc_table", "create_index", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "insert",
  "values_list", "values", "value_list", "value", "delete", "update",
<<<<<<< HEAD
  "set_stmt", "set_value", "nest_lbrace", "select", "select_stmt",
  "select_attr", "attr_list", "rel_list", "where", "condition_list",
  "condition", "comOp", "load_data", YY_NULLPTR
>>>>>>> support parsing sub select of update in front-end
=======
  "set_stmt", "set_stmts", "set_value", "nest_lbrace", "select",
  "select_stmt", "select_attr", "attr_list", "rel_list", "where",
  "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
>>>>>>> update without aggregation-func
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

<<<<<<< HEAD
<<<<<<< HEAD
#define YYPACT_NINF (-122)
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#define YYPACT_NINF (-120)
=======
#define YYPACT_NINF (-107)
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
#define YYPACT_NINF (-108)
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
    -122,     5,  -122,     0,    74,    26,   -42,    14,    31,    -1,
      -2,   -20,    44,    61,    76,    80,    82,     9,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,    32,    34,    40,
      46,  -122,  -122,  -122,  -122,  -122,    18,    89,    55,    94,
      97,   121,   122,    95,  -122,    72,    73,    93,  -122,  -122,
    -122,  -122,  -122,    90,   115,    96,   129,   131,    81,   -51,
    -122,  -122,    83,    68,  -122,   -25,  -122,  -122,    84,   105,
     108,    86,    85,    88,    91,  -122,  -122,    60,    89,    89,
     119,    94,   127,    -5,   128,   144,   132,     8,   146,   109,
     123,  -122,   133,    98,   137,    99,  -122,  -122,  -122,   100,
     108,  -122,  -122,  -122,   101,  -122,  -122,    57,   139,  -122,
    -122,  -122,    11,  -122,    25,   124,  -122,    57,   152,    88,
     143,  -122,  -122,  -122,  -122,   145,   107,    89,   119,   160,
     147,   148,   132,   162,   112,   134,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,    39,    45,     8,  -122,   108,   114,   133,
     167,   120,   154,  -122,  -122,  -122,  -122,    57,   156,   139,
    -122,    25,  -122,  -122,  -122,   149,  -122,   124,   171,   172,
    -122,  -122,  -122,   159,   175,   148,  -122,  -122,    51,   125,
    -122,  -122,  -122,  -122,  -122,  -122,   151,  -122,  -122,   126,
    -122
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
    -120,     4,  -120,    -1,    40,    26,   -49,    20,    17,     5,
       2,   -12,    44,    62,    75,    76,    77,    46,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,    27,    28,    31,
      32,  -120,  -120,  -120,  -120,  -120,    -6,    81,    74,    93,
     100,    90,   114,    92,  -120,    69,    70,    91,  -120,  -120,
    -120,  -120,  -120,    86,   112,    94,   126,   127,    78,    79,
    -120,  -120,    80,    13,  -120,   -23,  -120,  -120,    82,   102,
     104,    83,    84,    85,    87,  -120,  -120,     8,    81,   121,
      93,   128,    -7,   129,   140,   131,    37,   141,   107,   120,
    -120,   132,    97,   135,    98,  -120,  -120,    99,   104,  -120,
    -120,  -120,   101,  -120,  -120,    61,   134,  -120,  -120,  -120,
      11,  -120,    25,   122,  -120,    61,   149,    85,   142,  -120,
    -120,  -120,  -120,   144,   103,    81,   121,   158,   145,   146,
     131,   160,   110,   133,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,    43,    49,    37,  -120,   104,   111,   132,   165,   117,
     153,  -120,  -120,  -120,  -120,    61,   154,   134,  -120,    25,
    -120,  -120,  -120,   147,  -120,   122,   169,   170,  -120,  -120,
    -120,   157,   173,   146,  -120,  -120,    55,   123,  -120,  -120,
    -120,  -120,  -120,  -120,   151,  -120,  -120,   125,  -120
=======
    -107,     5,  -107,     0,    28,   -20,   -21,    15,     4,     6,
      10,    -8,    41,    49,    50,    52,    58,    31,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,    59,  -107,    24,    26,
      27,    35,   -16,    55,    65,    87,    99,    76,  -107,    64,
      66,    72,  -107,  -107,  -107,  -107,  -107,    75,  -107,   101,
      81,   116,   117,    71,    73,  -107,  -107,    74,  -107,  -107,
      77,    92,    93,    78,    93,    79,    80,    82,  -107,  -107,
      -7,    55,   108,   126,   118,    -2,   130,    94,   133,   109,
    -107,   119,    88,   123,    90,  -107,  -107,    91,    93,  -107,
      57,   124,  -107,  -107,  -107,    23,  -107,    38,   110,  -107,
      11,  -107,   137,    80,   127,  -107,  -107,  -107,  -107,   131,
      96,    55,   108,  -107,   132,   118,   145,   102,   115,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,    39,    45,    -2,  -107,
    -107,  -107,  -107,   142,   103,   119,   151,   111,   138,  -107,
    -107,    57,   139,   124,  -107,    38,  -107,  -107,  -107,   129,
    -107,   110,   143,   156,  -107,  -107,  -107,   144,   159,   132,
    -107,  -107,    51,   113,  -107,  -107,  -107,  -107,  -107,  -107,
     136,  -107,  -107,   120,  -107
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
    -108,     4,  -108,    -1,    53,   -47,   -24,    26,    47,    20,
      37,    10,    73,    75,    76,    82,    88,    58,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,   100,  -108,    54,    55,
      56,    57,    -8,    90,    78,   107,   108,    81,  -108,    63,
      64,    79,  -108,  -108,  -108,  -108,  -108,    80,  -108,   101,
      84,   113,   115,    69,    72,  -108,  -108,    74,  -108,  -108,
      83,    93,    94,    85,   109,    86,    87,    89,  -108,  -108,
      -7,    90,   110,   122,   114,    17,   126,    91,    79,    94,
     102,  -108,   116,    77,   120,    92,  -108,  -108,    95,    94,
    -108,   -20,   123,  -108,  -108,  -108,    29,  -108,     2,   105,
    -108,     6,   109,   140,   138,    87,   129,  -108,  -108,  -108,
    -108,   131,    98,    90,   110,  -108,   132,   114,   146,   103,
     117,  -108,  -108,  -108,  -108,  -108,  -108,  -108,    34,    40,
      17,  -108,  -108,  -108,  -108,   143,  -108,  -108,   104,   116,
     152,   111,   139,  -108,  -108,   -20,   142,   123,  -108,     2,
    -108,  -108,  -108,   133,  -108,   105,   145,   154,  -108,  -108,
    -108,   147,   157,   132,  -108,  -108,    46,   118,  -108,  -108,
    -108,  -108,  -108,  -108,   135,  -108,  -108,   119,  -108
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
<<<<<<< HEAD
      14,     8,     5,     7,     6,     4,    19,     0,     0,     0,
       0,    69,    70,    71,    72,    73,    74,    74,     0,    63,
       0,     0,     0,     0,    24,     0,     0,     0,    25,    26,
      27,    23,    22,     0,     0,     0,     0,     0,     0,     0,
<<<<<<< HEAD
      59,    58,     0,     0,    62,     0,    31,    29,     0,     0,
      79,     0,     0,     0,     0,    28,    33,    74,    74,    74,
      77,    63,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    44,    35,     0,     0,     0,    75,    60,    61,     0,
      79,    64,    68,    66,     0,    65,    30,     0,    46,    51,
      52,    53,     0,    54,     0,    81,    55,     0,     0,     0,
       0,    40,    41,    42,    43,    38,     0,    74,    77,     0,
       0,    49,     0,     0,     0,     0,    96,    90,    91,    92,
      93,    94,    95,     0,     0,     0,    80,    79,     0,    35,
       0,     0,     0,    76,    78,    57,    67,     0,     0,    46,
      45,     0,    97,    85,    83,    86,    84,    81,     0,     0,
      36,    34,    39,     0,     0,    49,    48,    47,     0,     0,
      82,    56,    98,    37,    32,    50,     0,    87,    88,     0,
      89
=======
      59,    58,     0,     0,    61,     0,    31,    29,     0,     0,
      78,     0,     0,     0,     0,    28,    33,    73,    73,    76,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      44,    35,     0,     0,     0,    74,    60,     0,    78,    63,
      67,    65,     0,    64,    30,     0,    46,    51,    52,    53,
       0,    54,     0,    80,    55,     0,     0,     0,     0,    40,
      41,    42,    43,    38,     0,    73,    76,     0,     0,    49,
       0,     0,     0,     0,    95,    89,    90,    91,    92,    93,
      94,     0,     0,     0,    79,    78,     0,    35,     0,     0,
       0,    75,    77,    57,    66,     0,     0,    46,    45,     0,
      96,    84,    82,    85,    83,    80,     0,     0,    36,    34,
      39,     0,     0,    49,    48,    47,     0,     0,    81,    56,
      97,    37,    32,    50,     0,    86,    87,     0,    88
=======
      14,     8,     5,     7,     6,     4,     0,    19,     0,     0,
<<<<<<< HEAD
       0,     0,    67,    67,     0,     0,     0,     0,    24,     0,
       0,    58,    25,    26,    27,    23,    22,     0,    62,     0,
       0,     0,     0,     0,     0,    65,    64,     0,    31,    29,
       0,     0,    72,     0,    72,     0,     0,     0,    28,    33,
      67,    67,    70,     0,     0,     0,     0,     0,     0,     0,
      44,    35,     0,     0,     0,    68,    66,     0,    72,    30,
       0,    46,    51,    52,    53,     0,    54,     0,    74,    55,
       0,    56,     0,     0,     0,    40,    41,    42,    43,    38,
       0,    67,    70,    63,    49,     0,     0,     0,     0,    89,
      83,    84,    85,    86,    87,    88,     0,     0,     0,    73,
      61,    59,    57,     0,     0,    35,     0,     0,     0,    69,
      71,     0,     0,    46,    45,     0,    90,    78,    76,    79,
      77,    74,     0,     0,    36,    34,    39,     0,     0,    49,
      48,    47,     0,     0,    75,    60,    91,    37,    32,    50,
       0,    80,    81,     0,    82
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
       0,     0,    68,    68,     0,     0,     0,     0,    24,     0,
       0,     0,    25,    26,    27,    23,    22,     0,    63,     0,
       0,     0,     0,     0,     0,    66,    65,     0,    31,    29,
       0,     0,    73,     0,    58,     0,     0,     0,    28,    33,
      68,    68,    71,     0,     0,     0,     0,     0,     0,    73,
       0,    44,    35,     0,     0,     0,    69,    67,     0,    73,
      30,     0,    46,    51,    52,    53,     0,    54,     0,    75,
      55,     0,    58,     0,     0,     0,     0,    40,    41,    42,
      43,    38,     0,    68,    71,    64,    49,     0,     0,     0,
       0,    90,    84,    85,    86,    87,    88,    89,     0,     0,
       0,    74,    62,    60,    57,     0,    59,    56,     0,    35,
       0,     0,     0,    70,    72,     0,     0,    46,    45,     0,
      91,    79,    77,    80,    78,    75,     0,     0,    36,    34,
      39,     0,     0,    49,    48,    47,     0,     0,    76,    61,
      92,    37,    32,    50,     0,    81,    82,     0,    83
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,    23,    54,  -122,  -122,
    -122,  -122,    15,    43,     1,  -116,  -122,  -122,  -122,  -122,
     102,   116,  -122,   -47,    49,  -108,    13,    33,  -121,  -122
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
    -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,  -120,    24,    50,  -120,  -120,
    -120,  -120,    15,    45,     0,  -114,  -120,  -120,  -120,  -120,
      96,   115,  -120,   -47,    48,  -106,    12,    36,  -119,  -120
=======
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,    20,    53,  -107,  -107,
    -107,  -107,    14,    43,     2,   -97,  -107,  -107,  -107,  -107,
    -107,  -107,    29,  -107,   -43,    47,   -70,    12,    36,  -106,
    -107
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,    16,    51,  -108,  -108,
    -108,  -108,    13,    44,    -6,   -99,  -108,  -108,    96,    60,
    -108,  -108,  -108,    28,  -108,   -43,    50,   -48,    11,    35,
    -107,  -108
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
<<<<<<< HEAD
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
<<<<<<< HEAD
      26,    27,    28,    29,    30,    31,   130,   102,   183,   135,
     103,    32,   143,   118,   168,   124,    33,    34,    35,    48,
      74,    49,    50,    70,   110,    98,   156,   125,   153,    36
=======
      26,    27,    28,    29,    30,    31,   128,   101,   181,   133,
     102,    32,   141,   116,   166,   122,    33,    34,    35,    48,
      74,    49,    50,    70,   108,    97,   154,   123,   151,    36
=======
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
<<<<<<< HEAD
      26,    27,    28,    29,    30,    31,   114,    91,   167,   119,
      92,    32,   126,   101,   152,   107,    33,    34,    74,   142,
     143,    35,    36,    44,    65,    98,    86,   139,   108,   136,
      37
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
      26,    27,    28,    29,    30,    31,   116,    92,   171,   121,
      93,    32,   128,   102,   156,   108,    33,    34,    74,    89,
     144,   145,    35,    36,    44,    65,    99,    86,   141,   109,
     138,    37
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
      71,   141,   139,   154,    88,     2,    37,    89,    38,     3,
       4,   157,   113,    51,     5,     6,     7,     8,     9,    10,
      11,    52,    53,   114,    12,    13,    14,    92,    55,    56,
      93,    15,    16,    94,    54,    57,    68,   174,   176,   144,
     106,   107,   108,    17,   145,   146,    69,    58,    63,   178,
     188,   185,   147,   148,   149,   150,   151,   152,   145,   146,
     119,   120,   121,   122,    59,   123,   147,   148,   149,   150,
     151,   152,   197,    41,    42,    43,    44,    45,    68,    60,
      39,    46,    40,    61,    47,    62,    72,    64,   105,    65,
     163,   119,   120,   121,   173,    66,   123,   119,   120,   121,
     175,    67,   123,   119,   120,   121,   196,    68,   123,   119,
     120,   121,    73,    75,   123,    41,    42,    43,    44,    45,
     131,   132,   133,   134,    76,    77,    78,    79,    80,    81,
      82,    83,    85,    84,    86,    96,    87,   109,    90,    95,
      97,    99,   100,   101,   112,   115,   104,   116,   117,   126,
     127,   129,   128,   136,   137,   138,   140,   142,   158,   155,
     160,   161,   162,   165,   166,   170,   167,   171,   172,   179,
     181,   184,   182,   186,   191,   192,   193,   189,   194,   199,
     198,   200,   180,   159,   187,   169,   195,   164,   177,    91,
     190,     0,     0,   111
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
      71,   139,   137,   152,     2,    37,    51,    38,     3,     4,
     111,   155,    68,     5,     6,     7,     8,     9,    10,    11,
      54,   112,    69,    12,    13,    14,    68,    52,    53,    91,
      15,    16,    92,    56,    55,    93,   104,   172,   174,   142,
     105,   106,    17,    57,   143,   144,    39,    58,    40,   176,
     186,   183,   145,   146,   147,   148,   149,   150,   143,   144,
      41,    42,    43,    44,    45,    59,   145,   146,   147,   148,
     149,   150,   195,    41,    42,    43,    44,    45,    60,    61,
      62,    46,    64,    65,    47,    63,    66,    67,   161,   117,
     118,   119,   120,    76,   121,   117,   118,   119,   171,    68,
     121,   117,   118,   119,   173,    72,   121,   117,   118,   119,
     194,    73,   121,   117,   118,   119,    75,    77,   121,   129,
     130,   131,   132,    78,    79,    80,    82,    81,    83,    85,
      86,    84,    95,    87,    88,    89,    96,    94,    98,   107,
     100,    99,   103,   114,   124,   110,   113,   115,   125,   126,
     127,   134,   140,   135,   136,   156,   138,   153,   160,   158,
     159,   163,   164,   168,   165,   169,   177,   170,   179,   180,
     182,   184,   189,   190,   191,   187,   192,   157,   196,   197,
     198,   178,   185,   193,   162,   167,   109,   188,    90,   175
=======
      66,   137,    63,   124,    88,     2,    38,    48,    39,     3,
       4,    63,    64,   141,     5,     6,     7,     8,     9,    10,
      11,    94,    46,    47,    12,    13,    14,   140,   123,    45,
      42,    15,    16,    43,    40,    49,    41,    95,    96,   158,
     160,    50,    51,    17,    52,   102,   103,   104,   105,   172,
     106,   127,    53,    54,   169,    55,   128,   129,   102,   103,
     104,    56,    58,   106,   130,   131,   132,   133,   134,   135,
      57,   128,   129,    63,    59,   181,    60,    61,   149,   130,
     131,   132,   133,   134,   135,    62,   102,   103,   104,   157,
      68,   106,   102,   103,   104,   159,    67,   106,   102,   103,
     104,   180,    69,   106,   102,   103,   104,    70,    73,   106,
     115,   116,   117,   118,    71,    75,    72,    76,    77,    78,
      79,    80,    84,    81,    82,    85,    97,    83,    87,    99,
      90,    89,    93,   109,   100,   110,   111,   113,   112,   120,
     121,   122,   125,   144,   146,   138,   148,   147,   154,   156,
     151,     5,   155,   163,   165,   168,   170,   173,   166,   176,
     175,   177,   178,   182,   183,   164,   145,   171,   153,   150,
     184,   179,   162,   174,   161
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
      66,   139,   126,    42,     2,    38,    43,    39,     3,     4,
      63,    63,   143,     5,     6,     7,     8,     9,    10,    11,
      64,    95,   142,    12,    13,    14,    45,   103,   104,   105,
      15,    16,   107,    46,    47,   130,   131,    96,    97,   162,
     164,   113,    17,   132,   133,   134,   135,   136,   137,    49,
      48,   125,   176,   103,   104,   105,   173,   129,   107,    40,
      51,    41,   130,   131,   103,   104,   105,   106,    50,   107,
     132,   133,   134,   135,   136,   137,    52,   185,    53,    54,
     153,   103,   104,   105,   161,    55,   107,   103,   104,   105,
     163,    56,   107,   103,   104,   105,   184,    57,   107,   117,
     118,   119,   120,    58,    59,    60,    61,    62,    63,    67,
      68,    69,    70,    71,    72,    73,    78,    76,    79,    80,
      75,    77,    81,    84,    82,   100,    85,    88,    98,   110,
     101,   114,   111,    83,   115,    87,   122,    91,    90,    94,
     140,   127,   123,   147,   148,   124,   150,   151,   152,   158,
     155,   160,     5,   159,   167,   169,   172,   180,   170,   174,
     182,   177,   179,   187,   181,   168,   149,   183,   186,   188,
     175,   157,   146,   166,   154,   165,   178,     0,     0,     0,
       0,     0,     0,     0,   112
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
};

static const yytype_int16 yycheck[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
      47,   117,   110,   124,    55,     0,     6,    58,     8,     4,
       5,   127,    17,    55,     9,    10,    11,    12,    13,    14,
      15,     7,     8,    28,    19,    20,    21,    52,    29,    31,
      55,    26,    27,    58,     3,    55,    18,   153,   154,    28,
      87,    88,    89,    38,    33,    34,    28,     3,    39,   157,
     171,   167,    41,    42,    43,    44,    45,    46,    33,    34,
      52,    53,    54,    55,     3,    57,    41,    42,    43,    44,
      45,    46,   188,    47,    48,    49,    50,    51,    18,     3,
       6,    55,     8,     3,    58,     3,    31,    55,    28,    55,
     137,    52,    53,    54,    55,    55,    57,    52,    53,    54,
      55,    55,    57,    52,    53,    54,    55,    18,    57,    52,
      53,    54,    18,    16,    57,    47,    48,    49,    50,    51,
      22,    23,    24,    25,     3,     3,    31,    55,    55,    36,
      40,    16,     3,    37,     3,    30,    55,    18,    55,    55,
      32,    55,    57,    55,    17,    17,    55,     3,    16,     3,
      41,    18,    29,    16,    55,    55,    55,    18,     6,    35,
      17,    16,    55,     3,    17,     3,    18,    55,    34,    55,
       3,    17,    52,    17,     3,     3,    17,    28,     3,    28,
      55,    55,   159,   129,   169,   142,   185,   138,   155,    73,
     177,    -1,    -1,    91
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
      47,   115,   108,   122,     0,     6,    55,     8,     4,     5,
      17,   125,    18,     9,    10,    11,    12,    13,    14,    15,
       3,    28,    28,    19,    20,    21,    18,     7,     8,    52,
      26,    27,    55,    31,    29,    58,    28,   151,   152,    28,
      87,    88,    38,    55,    33,    34,     6,     3,     8,   155,
     169,   165,    41,    42,    43,    44,    45,    46,    33,    34,
      47,    48,    49,    50,    51,     3,    41,    42,    43,    44,
      45,    46,   186,    47,    48,    49,    50,    51,     3,     3,
       3,    55,    55,    55,    58,    39,    55,    55,   135,    52,
      53,    54,    55,     3,    57,    52,    53,    54,    55,    18,
      57,    52,    53,    54,    55,    31,    57,    52,    53,    54,
      55,    18,    57,    52,    53,    54,    16,     3,    57,    22,
      23,    24,    25,    31,    55,    55,    40,    36,    16,     3,
       3,    37,    30,    55,    55,    55,    32,    55,    55,    18,
      55,    57,    55,     3,     3,    17,    17,    16,    41,    29,
      18,    16,    18,    55,    55,     6,    55,    35,    55,    17,
      16,     3,    17,     3,    18,    55,    55,    34,     3,    52,
      17,    17,     3,     3,    17,    28,     3,   127,    55,    28,
      55,   157,   167,   183,   136,   140,    90,   175,    73,   153
=======
      43,   107,    18,   100,    74,     0,     6,     3,     8,     4,
       5,    18,    28,   110,     9,    10,    11,    12,    13,    14,
      15,    28,     7,     8,    19,    20,    21,    16,    98,    50,
      50,    26,    27,    53,     6,    29,     8,    80,    81,   136,
     137,    31,    50,    38,     3,    47,    48,    49,    50,   155,
      52,    28,     3,     3,   151,     3,    33,    34,    47,    48,
      49,     3,     3,    52,    41,    42,    43,    44,    45,    46,
      39,    33,    34,    18,    50,   172,    50,    50,   121,    41,
      42,    43,    44,    45,    46,    50,    47,    48,    49,    50,
       3,    52,    47,    48,    49,    50,    31,    52,    47,    48,
      49,    50,     3,    52,    47,    48,    49,    31,    36,    52,
      22,    23,    24,    25,    50,    40,    50,    16,    37,     3,
       3,    50,    30,    50,    50,    32,    18,    50,    50,     3,
      50,    52,    50,     3,    16,    41,     3,    18,    29,    16,
      50,    50,    18,     6,    17,    35,    50,    16,     3,    34,
      18,     9,    50,    50,     3,    17,    17,    28,    47,     3,
      17,    17,     3,    50,    28,   145,   113,   153,   125,   122,
      50,   169,   143,   161,   138
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
      43,   108,   101,    50,     0,     6,    53,     8,     4,     5,
      18,    18,   111,     9,    10,    11,    12,    13,    14,    15,
      28,    28,    16,    19,    20,    21,    50,    47,    48,    49,
      26,    27,    52,     7,     8,    33,    34,    80,    81,   138,
     139,    89,    38,    41,    42,    43,    44,    45,    46,    29,
       3,    99,   159,    47,    48,    49,   155,    28,    52,     6,
      50,     8,    33,    34,    47,    48,    49,    50,    31,    52,
      41,    42,    43,    44,    45,    46,     3,   176,     3,     3,
     123,    47,    48,    49,    50,     3,    52,    47,    48,    49,
      50,     3,    52,    47,    48,    49,    50,    39,    52,    22,
      23,    24,    25,     3,    50,    50,    50,    50,    18,    31,
       3,     3,    31,    50,    50,    36,     3,    16,     3,    50,
      40,    37,    50,    30,    50,     3,    32,    18,    18,     3,
      16,    29,    41,    50,    18,    50,    16,    50,    52,    50,
      35,    18,    50,     3,     6,    50,    17,    16,    50,     3,
      18,    34,     9,    50,    50,     3,    17,     3,    47,    17,
       3,    28,    17,    28,    17,   149,   115,   173,    50,    50,
     157,   127,   112,   145,   124,   140,   165,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
<<<<<<< HEAD
       0,    61,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    38,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    81,    86,    87,    88,    99,     6,     8,     6,
       8,    47,    48,    49,    50,    51,    55,    58,    89,    91,
      92,    55,     7,     8,     3,    29,    31,    55,     3,     3,
       3,     3,     3,    39,    55,    55,    55,    55,    18,    28,
      93,    93,    31,    18,    90,    16,     3,     3,    31,    55,
<<<<<<< HEAD
      55,    36,    40,    16,    37,     3,     3,    55,    55,    58,
      55,    91,    52,    55,    58,    55,    30,    32,    95,    55,
      57,    55,    77,    80,    55,    28,    93,    93,    93,    18,
      94,    90,    17,    17,    28,    17,     3,    16,    83,    52,
      53,    54,    55,    57,    85,    97,     3,    41,    29,    18,
      76,    22,    23,    24,    25,    79,    16,    55,    55,    95,
      55,    85,    18,    82,    28,    33,    34,    41,    42,    43,
      44,    45,    46,    98,    98,    35,    96,    85,     6,    77,
      17,    16,    55,    93,    94,     3,    17,    18,    84,    83,
       3,    55,    34,    55,    85,    55,    85,    97,    95,    55,
      76,     3,    52,    78,    17,    85,    17,    82,    98,    28,
      96,     3,     3,    17,     3,    84,    55,    85,    55,    28,
      55
=======
      55,    36,    40,    16,    37,     3,     3,    55,    55,    55,
      91,    52,    55,    58,    55,    30,    32,    95,    55,    57,
      55,    77,    80,    55,    28,    93,    93,    18,    94,    90,
      17,    17,    28,    17,     3,    16,    83,    52,    53,    54,
      55,    57,    85,    97,     3,    41,    29,    18,    76,    22,
      23,    24,    25,    79,    16,    55,    55,    95,    55,    85,
      18,    82,    28,    33,    34,    41,    42,    43,    44,    45,
      46,    98,    98,    35,    96,    85,     6,    77,    17,    16,
      55,    93,    94,     3,    17,    18,    84,    83,     3,    55,
      34,    55,    85,    55,    85,    97,    95,    55,    76,     3,
      52,    78,    17,    85,    17,    82,    98,    28,    96,     3,
       3,    17,     3,    84,    55,    85,    55,    28,    55
=======
       0,    56,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    38,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    76,    81,    82,    87,    88,    96,     6,     8,
       6,     8,    50,    53,    89,    50,     7,     8,     3,    29,
      31,    50,     3,     3,     3,     3,     3,    39,     3,    50,
      50,    50,    50,    18,    28,    90,    90,    31,     3,     3,
      31,    50,    50,    36,    83,    40,    16,    37,     3,     3,
<<<<<<< HEAD
      50,    50,    50,    50,    30,    32,    91,    50,    91,    52,
      50,    72,    75,    50,    28,    89,    89,    18,    90,     3,
      16,    78,    47,    48,    49,    50,    52,    80,    93,     3,
      41,     3,    29,    18,    71,    22,    23,    24,    25,    74,
      16,    50,    50,    91,    80,    18,    77,    28,    33,    34,
      41,    42,    43,    44,    45,    46,    94,    94,    35,    92,
      16,    80,    84,    85,     6,    72,    17,    16,    50,    89,
      90,    18,    79,    78,     3,    50,    34,    50,    80,    50,
      80,    93,    87,    50,    71,     3,    47,    73,    17,    80,
      17,    77,    94,    28,    92,    17,     3,    17,     3,    79,
      50,    80,    50,    28,    50
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
      50,    50,    50,    50,    30,    32,    92,    50,    18,    84,
      52,    50,    72,    75,    50,    28,    90,    90,    18,    91,
       3,    16,    78,    47,    48,    49,    50,    52,    80,    94,
       3,    41,    83,    92,    29,    18,    71,    22,    23,    24,
      25,    74,    16,    50,    50,    92,    80,    18,    77,    28,
      33,    34,    41,    42,    43,    44,    45,    46,    95,    95,
      35,    93,    16,    80,    85,    86,    84,     3,     6,    72,
      17,    16,    50,    90,    91,    18,    79,    78,     3,    50,
      34,    50,    80,    50,    80,    94,    88,    50,    71,     3,
      47,    73,    17,    80,    17,    77,    95,    28,    93,    17,
       3,    17,     3,    79,    50,    80,    50,    28,    50
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
<<<<<<< HEAD
       0,    60,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    76,    77,    77,    78,
      79,    79,    79,    79,    80,    81,    82,    82,    83,    84,
      84,    85,    85,    85,    85,    86,    87,    88,    89,    89,
<<<<<<< HEAD
      89,    89,    89,    90,    90,    91,    91,    91,    91,    92,
      92,    92,    92,    92,    93,    93,    93,    94,    94,    95,
      95,    96,    96,    97,    97,    97,    97,    97,    97,    97,
      98,    98,    98,    98,    98,    98,    98,    98,    99
=======
      89,    89,    90,    90,    91,    91,    91,    91,    92,    92,
      92,    92,    92,    93,    93,    93,    94,    94,    95,    95,
      96,    96,    97,    97,    97,    97,    97,    97,    97,    98,
      98,    98,    98,    98,    98,    98,    98,    99
=======
       0,    55,    56,    56,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    71,    72,    72,    73,
      74,    74,    74,    74,    75,    76,    77,    77,    78,    79,
<<<<<<< HEAD
      79,    80,    80,    80,    80,    81,    82,    83,    83,    84,
      84,    85,    86,    87,    88,    88,    88,    89,    89,    89,
      90,    90,    91,    91,    92,    92,    93,    93,    93,    93,
      93,    93,    93,    94,    94,    94,    94,    94,    94,    94,
      94,    95
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
      79,    80,    80,    80,    80,    81,    82,    83,    84,    84,
      85,    85,    86,    87,    88,    89,    89,    89,    90,    90,
      90,    91,    91,    92,    92,    93,    93,    94,    94,    94,
      94,    94,    94,    94,    95,    95,    95,    95,    95,    95,
      95,    95,    96
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       5,     3,     9,     4,     8,     0,     3,     5,     2,     1,
       1,     1,     1,     1,     1,     7,     0,     3,     4,     0,
<<<<<<< HEAD
<<<<<<< HEAD
       3,     1,     1,     1,     1,     5,     8,     7,     2,     2,
<<<<<<< HEAD
       4,     4,     2,     0,     3,     4,     4,     6,     4,     1,
       1,     1,     1,     1,     0,     3,     5,     0,     3,     0,
       3,     0,     3,     3,     3,     3,     3,     5,     5,     7,
       1,     1,     1,     1,     1,     1,     1,     2,     8
=======
       4,     2,     0,     3,     4,     4,     6,     4,     1,     1,
       1,     1,     1,     0,     3,     5,     0,     3,     0,     3,
       0,     3,     3,     3,     3,     3,     5,     5,     7,     1,
       1,     1,     1,     1,     1,     1,     2,     8
=======
       3,     1,     1,     1,     1,     5,     5,     4,     0,     1,
       3,     1,     2,     6,     2,     2,     4,     0,     3,     5,
       0,     3,     0,     3,     0,     3,     3,     3,     3,     3,
       5,     5,     7,     1,     1,     1,     1,     1,     1,     1,
       2,     8
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
       3,     1,     1,     1,     1,     5,     6,     4,     0,     3,
       1,     3,     1,     2,     6,     2,     2,     4,     0,     3,
       5,     0,     3,     0,     3,     0,     3,     3,     3,     3,
       3,     5,     5,     7,     1,     1,     1,     1,     1,     1,
       1,     2,     8
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
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
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
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
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex (&yylval, scanner);
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
<<<<<<< HEAD
  case 22: /* exit: EXIT SEMICOLON  */
#line 172 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1364 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 177 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1372 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 182 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1380 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 188 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1388 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 194 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1396 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 200 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1404 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 206 "yacc_sql.y"
=======
  case 22:
#line 167 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1566 "yacc_sql.tab.c"
    break;

  case 23:
#line 172 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1574 "yacc_sql.tab.c"
    break;

  case 24:
#line 177 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1582 "yacc_sql.tab.c"
    break;

  case 25:
#line 183 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1590 "yacc_sql.tab.c"
    break;

  case 26:
#line 189 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1598 "yacc_sql.tab.c"
    break;

  case 27:
#line 195 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1606 "yacc_sql.tab.c"
    break;

  case 28:
#line 201 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1413 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1408 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 212 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1421 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 218 "yacc_sql.y"
=======
#line 1613 "yacc_sql.tab.c"
=======
#line 1615 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 29:
#line 207 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1623 "yacc_sql.tab.c"
    break;

  case 30:
#line 213 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
                {
			CONTEXT->ssql->flag=SCF_SHOW_INDEX;//"show_index";
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1430 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1425 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 224 "yacc_sql.y"
=======
#line 1630 "yacc_sql.tab.c"
=======
#line 1632 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 31:
#line 219 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1439 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1434 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 32: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 232 "yacc_sql.y"
=======
#line 1639 "yacc_sql.tab.c"
=======
#line 1641 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 32:
#line 227 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1448 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1443 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 33: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 240 "yacc_sql.y"
=======
#line 1648 "yacc_sql.tab.c"
=======
#line 1650 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 33:
#line 235 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1457 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1452 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 34: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 247 "yacc_sql.y"
=======
#line 1657 "yacc_sql.tab.c"
=======
#line 1659 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 34:
#line 242 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1469 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1464 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 36: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 257 "yacc_sql.y"
                                   {    }
#line 1475 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 262 "yacc_sql.y"
=======
#line 1669 "yacc_sql.tab.c"
=======
#line 1671 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 36:
#line 252 "yacc_sql.y"
                                   {    }
#line 1677 "yacc_sql.tab.c"
    break;

  case 37:
#line 257 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1490 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1485 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 38: /* attr_def: ID_get type  */
#line 273 "yacc_sql.y"
=======
#line 1690 "yacc_sql.tab.c"
=======
#line 1692 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 38:
#line 268 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1505 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1500 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 39: /* number: NUMBER  */
#line 285 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1511 "yacc_sql.tab.c"
    break;

  case 40: /* type: INT_T  */
#line 288 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1517 "yacc_sql.tab.c"
    break;

  case 41: /* type: STRING_T  */
#line 289 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1523 "yacc_sql.tab.c"
    break;

  case 42: /* type: FLOAT_T  */
#line 290 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1529 "yacc_sql.tab.c"
    break;

  case 43: /* type: DATE_T  */
#line 291 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1535 "yacc_sql.tab.c"
    break;

  case 44: /* ID_get: ID  */
#line 295 "yacc_sql.y"
=======
#line 1705 "yacc_sql.tab.c"
=======
#line 1707 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 39:
#line 280 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1713 "yacc_sql.tab.c"
    break;

  case 40:
#line 283 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1719 "yacc_sql.tab.c"
    break;

  case 41:
#line 284 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1725 "yacc_sql.tab.c"
    break;

  case 42:
#line 285 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1731 "yacc_sql.tab.c"
    break;

  case 43:
#line 286 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1737 "yacc_sql.tab.c"
    break;

  case 44:
#line 290 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1544 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1539 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 45: /* insert: INSERT INTO ID VALUES values values_list SEMICOLON  */
#line 304 "yacc_sql.y"
=======
#line 1744 "yacc_sql.tab.c"
=======
#line 1746 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 45:
#line 299 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
                {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string), CONTEXT->values_array, CONTEXT->value_length_array, CONTEXT->values_length);

      //临时变量清零
      CONTEXT->value_length=0;
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1563 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1558 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 47: /* values_list: COMMA values values_list  */
#line 321 "yacc_sql.y"
                                {
    }
#line 1570 "yacc_sql.tab.c"
    break;

  case 48: /* values: LBRACE value value_list RBRACE  */
#line 326 "yacc_sql.y"
=======
#line 1763 "yacc_sql.tab.c"
=======
#line 1765 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 47:
#line 316 "yacc_sql.y"
                                {
    }
#line 1772 "yacc_sql.tab.c"
    break;

  case 48:
#line 321 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
                                    {
        for (int i = 0; i < CONTEXT->value_length; i++) {
            CONTEXT->values_array[CONTEXT->values_length][i] = CONTEXT->values[i];
        }
        CONTEXT->value_length_array[CONTEXT->values_length++] = CONTEXT->value_length;
        CONTEXT->value_length = 0;
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1582 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1577 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 50: /* value_list: COMMA value value_list  */
#line 336 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1590 "yacc_sql.tab.c"
    break;

  case 51: /* value: NUMBER  */
#line 341 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1598 "yacc_sql.tab.c"
    break;

  case 52: /* value: FLOAT  */
#line 344 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1606 "yacc_sql.tab.c"
    break;

  case 53: /* value: DATE_STR  */
#line 347 "yacc_sql.y"
=======
#line 1782 "yacc_sql.tab.c"
=======
#line 1784 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 50:
#line 331 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1792 "yacc_sql.tab.c"
    break;

  case 51:
#line 336 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1800 "yacc_sql.tab.c"
    break;

  case 52:
#line 339 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1808 "yacc_sql.tab.c"
    break;

  case 53:
#line 342 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
                 {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
		if(value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string))==-1)
		yyerror(scanner,"qfs");
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1616 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1611 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 54: /* value: SSS  */
#line 352 "yacc_sql.y"
=======
#line 1816 "yacc_sql.tab.c"
=======
#line 1818 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 54:
#line 347 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
		printf("before init one value: %d\n", CONTEXT->value_length);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
  		printf("one value: %d\n", CONTEXT->value_length);
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1625 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1620 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 55: /* delete: DELETE FROM ID where SEMICOLON  */
#line 360 "yacc_sql.y"
=======
#line 1825 "yacc_sql.tab.c"
    break;

  case 55:
#line 355 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
=======
#line 1829 "yacc_sql.tab.c"
    break;

  case 55:
#line 357 "yacc_sql.y"
>>>>>>> update without aggregation-func
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1637 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1632 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 56: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 370 "yacc_sql.y"
=======
#line 1837 "yacc_sql.tab.c"
    break;

  case 56:
#line 367 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
=======
#line 1841 "yacc_sql.tab.c"
    break;

  case 56:
#line 369 "yacc_sql.y"
>>>>>>> update without aggregation-func
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = CONTEXT->values;
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-4].string), value, CONTEXT->value_length,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
			CONTEXT->value_length = 0;
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1649 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1644 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 57: /* select: SELECT select_attr FROM ID rel_list where SEMICOLON  */
#line 380 "yacc_sql.y"
=======
#line 1849 "yacc_sql.tab.c"
=======
#line 1854 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 57:
#line 380 "yacc_sql.y"
                        {
        updates_append_attribute(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), CONTEXT->value_length-1);
        printf("one set_stmt:\n");
        printf("%d\n", CONTEXT->value_length);
    }
#line 1864 "yacc_sql.tab.c"
    break;

  case 59:
#line 389 "yacc_sql.y"
                               {
        }
#line 1871 "yacc_sql.tab.c"
    break;

  case 60:
#line 394 "yacc_sql.y"
          {
    }
#line 1878 "yacc_sql.tab.c"
    break;

  case 61:
#line 396 "yacc_sql.y"
                                     {
        if (CONTEXT->parent_context == NULL) {
            yyerror(scanner, "no parent context of current context");
        } else {
            yyset_extra(CONTEXT->parent_context, scanner);
        }
        ParserContext *child = CONTEXT->child_context;
        value_init_select(&CONTEXT->values[CONTEXT->value_length++], child->ssql);
    }
#line 1892 "yacc_sql.tab.c"
    break;

  case 62:
#line 408 "yacc_sql.y"
           {
            if (CONTEXT->child_context == NULL) {
                ParserContext *child = (ParserContext *)malloc(sizeof(ParserContext));
                CONTEXT->child_context = child;
                memset(child, 0, sizeof(ParserContext));
                child->ssql = query_create();
                child->parent_context = CONTEXT;
                yyset_extra(child, scanner);
            }
        }
#line 1907 "yacc_sql.tab.c"
    break;

  case 63:
#line 421 "yacc_sql.y"
                          {}
#line 1913 "yacc_sql.tab.c"
    break;

<<<<<<< HEAD
  case 63:
#line 416 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
=======
  case 64:
#line 426 "yacc_sql.y"
>>>>>>> update without aggregation-func
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1669 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1664 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 58: /* select_attr: STAR attr_list  */
#line 398 "yacc_sql.y"
=======
#line 1919 "yacc_sql.tab.c"
    break;

  case 64:
#line 434 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
=======
#line 1933 "yacc_sql.tab.c"
    break;

  case 65:
#line 444 "yacc_sql.y"
>>>>>>> update without aggregation-func
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1679 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1674 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 59: /* select_attr: ID attr_list  */
#line 403 "yacc_sql.y"
=======
#line 1929 "yacc_sql.tab.c"
    break;

  case 65:
#line 439 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
=======
#line 1943 "yacc_sql.tab.c"
    break;

  case 66:
#line 449 "yacc_sql.y"
>>>>>>> update without aggregation-func
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1689 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1684 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 60: /* select_attr: ID DOT ID attr_list  */
#line 408 "yacc_sql.y"
=======
#line 1939 "yacc_sql.tab.c"
    break;

  case 66:
#line 444 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
=======
#line 1953 "yacc_sql.tab.c"
    break;

  case 67:
#line 454 "yacc_sql.y"
>>>>>>> update without aggregation-func
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1699 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1694 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 61: /* select_attr: ID DOT STAR attr_list  */
#line 413 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1709 "yacc_sql.tab.c"
    break;

  case 62: /* select_attr: aggrefunc aggrefunc_list  */
#line 418 "yacc_sql.y"
                                    {
		}
#line 1716 "yacc_sql.tab.c"
    break;

  case 64: /* aggrefunc_list: COMMA aggrefunc aggrefunc_list  */
#line 423 "yacc_sql.y"
                                         {
		}
#line 1723 "yacc_sql.tab.c"
    break;

  case 65: /* aggrefunc: aggrefunc_type LBRACE STAR RBRACE  */
#line 429 "yacc_sql.y"
                                          {
			Aggrefunc func;
			aggrefunc_init(&func,(yyvsp[-3].number),NULL,"*",-1);
			selects_append_aggrefuncs(&CONTEXT->ssql->sstr.selection, &func);
		}
#line 1733 "yacc_sql.tab.c"
    break;

  case 66: /* aggrefunc: aggrefunc_type LBRACE ID RBRACE  */
#line 434 "yacc_sql.y"
                                          {
			Aggrefunc func;
			aggrefunc_init(&func,(yyvsp[-3].number),NULL,(yyvsp[-1].string),-1);
			selects_append_aggrefuncs(&CONTEXT->ssql->sstr.selection, &func);
		}
#line 1743 "yacc_sql.tab.c"
    break;

  case 67: /* aggrefunc: aggrefunc_type LBRACE ID DOT ID RBRACE  */
#line 439 "yacc_sql.y"
                                                 {
			Aggrefunc func;
			aggrefunc_init(&func,(yyvsp[-5].number),(yyvsp[-3].string),(yyvsp[-1].string),-1);
			selects_append_aggrefuncs(&CONTEXT->ssql->sstr.selection, &func);
		}
#line 1753 "yacc_sql.tab.c"
    break;

  case 68: /* aggrefunc: aggrefunc_type LBRACE NUMBER RBRACE  */
#line 444 "yacc_sql.y"
                                              {//只支持无符号
			Aggrefunc func;
			aggrefunc_init(&func,(yyvsp[-3].number),NULL,NULL,(yyvsp[-1].number));
			selects_append_aggrefuncs(&CONTEXT->ssql->sstr.selection, &func);
		}
#line 1763 "yacc_sql.tab.c"
    break;

  case 69: /* aggrefunc_type: COUNT_F  */
#line 451 "yacc_sql.y"
                { (yyval.number)=COUNTS; }
#line 1769 "yacc_sql.tab.c"
    break;

  case 70: /* aggrefunc_type: AVG_F  */
#line 452 "yacc_sql.y"
                { (yyval.number)=AVGS; }
#line 1775 "yacc_sql.tab.c"
    break;

  case 71: /* aggrefunc_type: MAX_F  */
#line 453 "yacc_sql.y"
                { (yyval.number)=MAXS; }
#line 1781 "yacc_sql.tab.c"
    break;

  case 72: /* aggrefunc_type: MIN_F  */
#line 454 "yacc_sql.y"
                { (yyval.number)=MINS; }
#line 1787 "yacc_sql.tab.c"
    break;

  case 73: /* aggrefunc_type: SUM_F  */
#line 455 "yacc_sql.y"
                { (yyval.number)=SUMS; }
#line 1793 "yacc_sql.tab.c"
    break;

<<<<<<< HEAD
  case 75: /* attr_list: COMMA ID attr_list  */
#line 459 "yacc_sql.y"
=======
  case 74: /* attr_list: COMMA ID attr_list  */
#line 454 "yacc_sql.y"
=======
#line 1949 "yacc_sql.tab.c"
    break;

  case 68:
#line 452 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
#line 1963 "yacc_sql.tab.c"
    break;

  case 69:
#line 462 "yacc_sql.y"
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1805 "yacc_sql.tab.c"
    break;

  case 76: /* attr_list: COMMA ID DOT ID attr_list  */
#line 466 "yacc_sql.y"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1790 "yacc_sql.tab.c"
    break;

  case 75: /* attr_list: COMMA ID DOT ID attr_list  */
#line 461 "yacc_sql.y"
=======
#line 1961 "yacc_sql.tab.c"
    break;

  case 69:
#line 459 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
#line 1975 "yacc_sql.tab.c"
    break;

  case 70:
#line 469 "yacc_sql.y"
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1817 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1802 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 78: /* rel_list: COMMA ID rel_list  */
#line 477 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 1825 "yacc_sql.tab.c"
    break;

  case 80: /* where: WHERE condition condition_list  */
#line 483 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1833 "yacc_sql.tab.c"
    break;

  case 82: /* condition_list: AND condition condition_list  */
#line 489 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1841 "yacc_sql.tab.c"
    break;

<<<<<<< HEAD
  case 83: /* condition: ID comOp value  */
#line 495 "yacc_sql.y"
=======
  case 82: /* condition: ID comOp value  */
#line 490 "yacc_sql.y"
=======
#line 1973 "yacc_sql.tab.c"
=======
#line 1987 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 72:
#line 480 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 1995 "yacc_sql.tab.c"
    break;

  case 74:
#line 486 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2003 "yacc_sql.tab.c"
    break;

  case 76:
#line 492 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2011 "yacc_sql.tab.c"
    break;

<<<<<<< HEAD
  case 76:
#line 488 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
  case 77:
#line 498 "yacc_sql.y"
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
            if ((CONTEXT->comp == LIKE_AS || CONTEXT->comp == NOT_LIKE) && right_value->type == CHARS) {
                right_value->type = REGEXP;
            }

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			CONTEXT->value_length--;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1869 "yacc_sql.tab.c"
    break;

  case 84: /* condition: value comOp value  */
#line 519 "yacc_sql.y"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1854 "yacc_sql.tab.c"
    break;

  case 83: /* condition: value comOp value  */
#line 514 "yacc_sql.y"
=======
#line 2025 "yacc_sql.tab.c"
    break;

  case 77:
#line 512 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
#line 2040 "yacc_sql.tab.c"
    break;

  case 78:
#line 523 "yacc_sql.y"
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1893 "yacc_sql.tab.c"
    break;

  case 85: /* condition: ID comOp ID  */
#line 539 "yacc_sql.y"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1878 "yacc_sql.tab.c"
    break;

  case 84: /* condition: ID comOp ID  */
#line 534 "yacc_sql.y"
=======
#line 2049 "yacc_sql.tab.c"
    break;

  case 78:
#line 532 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
#line 2064 "yacc_sql.tab.c"
    break;

  case 79:
#line 543 "yacc_sql.y"
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1917 "yacc_sql.tab.c"
    break;

  case 86: /* condition: value comOp ID  */
#line 559 "yacc_sql.y"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1902 "yacc_sql.tab.c"
    break;

  case 85: /* condition: value comOp ID  */
#line 554 "yacc_sql.y"
=======
#line 2073 "yacc_sql.tab.c"
    break;

  case 79:
#line 552 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
#line 2088 "yacc_sql.tab.c"
    break;

  case 80:
#line 563 "yacc_sql.y"
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 1943 "yacc_sql.tab.c"
    break;

  case 87: /* condition: ID DOT ID comOp value  */
#line 581 "yacc_sql.y"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1928 "yacc_sql.tab.c"
    break;

  case 86: /* condition: ID DOT ID comOp value  */
#line 576 "yacc_sql.y"
=======
#line 2099 "yacc_sql.tab.c"
    break;

  case 80:
#line 574 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
#line 2114 "yacc_sql.tab.c"
    break;

  case 81:
#line 585 "yacc_sql.y"
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1968 "yacc_sql.tab.c"
    break;

  case 88: /* condition: value comOp ID DOT ID  */
#line 602 "yacc_sql.y"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1953 "yacc_sql.tab.c"
    break;

  case 87: /* condition: value comOp ID DOT ID  */
#line 597 "yacc_sql.y"
=======
#line 2124 "yacc_sql.tab.c"
    break;

  case 81:
#line 595 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
#line 2139 "yacc_sql.tab.c"
    break;

  case 82:
#line 606 "yacc_sql.y"
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1993 "yacc_sql.tab.c"
    break;

  case 89: /* condition: ID DOT ID comOp ID DOT ID  */
#line 623 "yacc_sql.y"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 1978 "yacc_sql.tab.c"
    break;

  case 88: /* condition: ID DOT ID comOp ID DOT ID  */
#line 618 "yacc_sql.y"
=======
#line 2149 "yacc_sql.tab.c"
    break;

  case 82:
#line 616 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
#line 2164 "yacc_sql.tab.c"
    break;

  case 83:
#line 627 "yacc_sql.y"
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 2016 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 2001 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
    break;

  case 90: /* comOp: EQ  */
#line 644 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2022 "yacc_sql.tab.c"
    break;

  case 91: /* comOp: LT  */
#line 645 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2028 "yacc_sql.tab.c"
    break;

  case 92: /* comOp: GT  */
#line 646 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2034 "yacc_sql.tab.c"
    break;

  case 93: /* comOp: LE  */
#line 647 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2040 "yacc_sql.tab.c"
    break;

  case 94: /* comOp: GE  */
#line 648 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2046 "yacc_sql.tab.c"
    break;

  case 95: /* comOp: NE  */
#line 649 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2052 "yacc_sql.tab.c"
    break;

  case 96: /* comOp: LIKE  */
#line 650 "yacc_sql.y"
           { CONTEXT->comp = LIKE_AS; }
#line 2058 "yacc_sql.tab.c"
    break;

  case 97: /* comOp: NOT LIKE  */
#line 651 "yacc_sql.y"
               { CONTEXT->comp = NOT_LIKE; }
#line 2064 "yacc_sql.tab.c"
    break;

<<<<<<< HEAD
  case 98: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 656 "yacc_sql.y"
=======
  case 97: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 651 "yacc_sql.y"
=======
#line 2172 "yacc_sql.tab.c"
=======
#line 2187 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
    break;

  case 84:
#line 648 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2193 "yacc_sql.tab.c"
    break;

  case 85:
#line 649 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2199 "yacc_sql.tab.c"
    break;

  case 86:
#line 650 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2205 "yacc_sql.tab.c"
    break;

  case 87:
#line 651 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2211 "yacc_sql.tab.c"
    break;

  case 88:
#line 652 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2217 "yacc_sql.tab.c"
    break;

  case 89:
#line 653 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2223 "yacc_sql.tab.c"
    break;

  case 90:
#line 654 "yacc_sql.y"
           { CONTEXT->comp = LIKE_AS; }
#line 2229 "yacc_sql.tab.c"
    break;

  case 91:
#line 655 "yacc_sql.y"
               { CONTEXT->comp = NOT_LIKE; }
#line 2235 "yacc_sql.tab.c"
    break;

<<<<<<< HEAD
  case 91:
#line 649 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
  case 92:
#line 660 "yacc_sql.y"
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
<<<<<<< HEAD
<<<<<<< HEAD
#line 2073 "yacc_sql.tab.c"
    break;


#line 2077 "yacc_sql.tab.c"
=======
=======
>>>>>>> update without aggregation-func
<<<<<<< HEAD
#line 2058 "yacc_sql.tab.c"
    break;


#line 2062 "yacc_sql.tab.c"
=======
#line 2229 "yacc_sql.tab.c"
    break;


#line 2233 "yacc_sql.tab.c"
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
#line 2244 "yacc_sql.tab.c"
    break;


#line 2248 "yacc_sql.tab.c"
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

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
      yyerror (scanner, YY_("syntax error"));
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
                      yytoken, &yylval, scanner);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}
<<<<<<< HEAD
<<<<<<< HEAD

<<<<<<< HEAD
#line 661 "yacc_sql.y"
=======
#line 656 "yacc_sql.y"
=======
#line 654 "yacc_sql.y"
>>>>>>> support parsing sub select of update in front-end
<<<<<<< HEAD
>>>>>>> support parsing sub select of update in front-end
=======
=======
#line 665 "yacc_sql.y"
>>>>>>> update without aggregation-func
>>>>>>> update without aggregation-func

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
