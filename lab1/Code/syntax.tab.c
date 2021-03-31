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
#line 2 "./syntax.y" /* yacc.c:339  */

    #include<stdio.h>
    #include"lex.yy.c"
	#define L 1
	#define LE 2
	#define G 3
	#define GE 4
	#define EQ 5
	#define NEQ 6
    #define BASE_NUM 258
    enum token{
        Program = 0, ExtDecList, ExtDef, Specifier, FunDec, CompSt, 
        VarDec, ExtDefList, StructSpecifier,
        OptTag, DefList, Tag, VarList, ParamDec,
        StmtList, Stmt, Exp, Def, DecList, Dec, Args,
        error
    };
    char *token_map[] = {"Program","ExtDecList","ExtDef","Specifier","FunDec","CompSt",
                         "VarDec","ExtDefList","StructSpecifier",
                         "OptTag","DefList","Tag","VarList","ParamDec",
                         "StmtList","Stmt","Exp","Def","DecList","Dec","Args","error"};
    char *token2_map[] = {"SEMI","COMMA","ASSIGNOP","PLUS",
                          "MINUS","STAR","DIV","AND","OR","NOT","DOT","TYPE","LP","RP","LB","RB" ,"LC","RC","STRUCT","RETURN",
                          "IF","ELSE","WHILE","INT","FLOAT","ID","RELOP","SUB","LOWER_THAN_ELSE"};
    union TreeVal{
        int i;
        float f;
        char *str;
    };
    struct ErrorNode{
        int Linenumber;
        char ErrorType;
        char *Information;
        struct ErrorNode* next;
    };
    struct ErrorNode *ErrorHead=NULL;
    void print_Node(struct ErrorNode* node);
    void print_Errors();
    void insert_Error(char errorType,int linenumber,char* information);
    int HaveErrors=0;
    struct GrammarTree;
    struct ListNode{
        struct GrammarTree *val;
        struct ListNode *next;
    };
    struct GrammarTree{
        int line;
        union TreeVal val;
        int type;
        struct ListNode *head;
    };
    void insert(struct GrammarTree *t1,struct GrammarTree *t2);
    struct GrammarTree *createnode(int type,int line,void *value);
    void insertall(struct GrammarTree *t1,struct GrammarTree *t2,...);
    struct GrammarTree *root;
    void __DFS(struct GrammarTree *n,int depth);
    void print_tree();

#line 125 "./syntax.tab.c" /* yacc.c:339  */

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
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
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
    SEMI = 258,
    COMMA = 259,
    ASSIGNOP = 260,
    PLUS = 261,
    MINUS = 262,
    STAR = 263,
    DIV = 264,
    AND = 265,
    OR = 266,
    NOT = 267,
    DOT = 268,
    TYPE = 269,
    LP = 270,
    RP = 271,
    LB = 272,
    RB = 273,
    LC = 274,
    RC = 275,
    STRUCT = 276,
    RETURN = 277,
    IF = 278,
    ELSE = 279,
    WHILE = 280,
    INT = 281,
    FLOAT = 282,
    ID = 283,
    RELOP = 284,
    SUB = 285,
    LOWER_THAN_ELSE = 286
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 61 "./syntax.y" /* yacc.c:355  */

    union {
        struct GrammarTree * t;
        int i;
        float f;
        char *str;
    }type_treenode;

#line 206 "./syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
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

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 237 "./syntax.tab.c" /* yacc.c:358  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   290

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   107,   107,   112,   116,   118,   124,   129,   134,   141,
     144,   152,   156,   159,   169,   175,   179,   181,   185,   188,
     196,   203,   211,   218,   226,   231,   234,   238,   246,   249,
     251,   255,   257,   263,   272,   284,   293,   300,   307,   315,
     323,   326,   327,   335,   340,   342,   348,   350,   357,   362,
     367,   372,   377,   382,   387,   392,   397,   403,   407,   411,
     419,   426,   433,   439,   442,   445,   448,   455,   463,   468
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMI", "COMMA", "ASSIGNOP", "PLUS",
  "MINUS", "STAR", "DIV", "AND", "OR", "NOT", "DOT", "TYPE", "LP", "RP",
  "LB", "RB", "LC", "RC", "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "INT",
  "FLOAT", "ID", "RELOP", "SUB", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
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
     285,   286
};
# endif

#define YYPACT_NINF -76

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-76)))

#define YYTABLE_NINF -47

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -3,   -76,   -20,    36,   -76,    -3,    14,   -76,     0,    27,
     -76,   -76,   -76,   -76,   -76,    32,    50,   122,    38,     6,
     101,   -76,    40,    28,    68,    86,   -76,    59,    28,    44,
      86,    79,   -76,    28,    80,    93,   -76,   -76,   -76,    81,
     245,   -76,   258,   100,   114,   -76,   -76,   -76,    73,   -76,
      -3,   -76,    33,    33,    33,    33,   104,    13,   -76,   -76,
     105,   -76,   110,   245,    62,    33,   -76,    28,   -76,    37,
      -1,   169,    75,    33,   113,    33,   126,   -76,   -76,   -76,
     -76,    33,    33,    33,    33,    33,    33,    33,   112,   143,
      33,   224,   -76,   -76,   -76,   -76,   183,   245,   197,   127,
     -76,   155,   129,   224,   273,   273,    -1,    -1,   237,   237,
     -76,   128,   210,   270,   109,   -76,   245,   -76,    33,   -76,
     -76,   -76,   123,   124,   -76,   -76,   245,   245,   -76,   -76
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    11,    16,     0,     2,     4,     0,    12,    17,     0,
      14,     1,     3,     8,     6,    18,     0,     0,     0,     0,
       0,     5,     0,     0,     0,     0,     7,     0,     0,     0,
       0,     0,    22,     0,     0,    25,    20,    18,    10,     0,
      29,    42,     0,     0,    44,    13,    40,    23,     0,    21,
       0,    19,     0,     0,     0,     0,     0,     0,    64,    65,
      63,    31,     0,    29,     0,     0,    43,     0,    24,    57,
      58,     0,     0,     0,     0,     0,     0,    27,    28,    38,
      30,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    47,    45,    56,    39,    32,     0,     0,     0,     0,
      60,    69,     0,    48,    52,    53,    54,    55,    49,    50,
      62,     0,     0,    51,     0,    37,     0,    67,     0,    59,
      66,    61,     0,    33,    35,    68,     0,     0,    36,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   144,   -76,   133,     5,   -76,   -76,   -76,   -24,
     -76,   107,   -76,   149,    88,   -75,    19,   -76,   106,   -76,
     -52,    63
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    16,    28,     7,     9,    10,    17,
      18,    34,    35,    61,    62,    63,    29,    30,    43,    44,
      64,   102
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      69,    70,    71,    72,    42,     6,    83,    27,     8,    48,
       6,     1,    88,    91,    74,    13,    89,    14,     2,   -15,
       1,    96,   115,    98,   101,    33,   -41,     2,    75,   103,
     104,   105,   106,   107,   108,   109,    11,   112,   113,   123,
      52,   124,    15,    42,    40,    53,    19,    20,    54,    46,
      88,   128,   129,    21,    89,    33,    37,    25,    36,    58,
      59,    60,    41,    79,    45,    80,   101,    81,    82,    83,
      84,    85,    86,    87,    22,    88,    94,   -26,    95,    89,
      81,    82,    83,    84,    85,    86,    87,    27,    88,   -26,
      24,    90,    89,   -41,    39,    47,    49,    50,   -41,    51,
       1,   -41,    31,    66,    90,   -41,   -41,     2,   -41,   -41,
     122,   -41,   -41,   -41,   -41,     1,    52,    32,    67,    73,
      76,    53,     2,    22,    54,    -9,    23,    99,    25,    97,
      77,    55,    56,    52,    57,    58,    59,    60,    53,    24,
     110,    54,   100,   117,   111,   119,   120,   126,   127,    12,
      52,    78,    58,    59,    60,    53,    38,    68,    54,   118,
      81,    82,    83,    84,    85,    86,    87,    26,    88,    58,
      59,    60,    89,    92,    81,    82,    83,    84,    85,    86,
      87,   125,    88,     0,    90,    93,    89,     0,    81,    82,
      83,    84,    85,    86,    87,     0,    88,     0,    90,   114,
      89,     0,    81,    82,    83,    84,    85,    86,    87,     0,
      88,     0,    90,   116,    89,    81,    82,    83,    84,    85,
      86,    87,     0,    88,     0,     0,    90,    89,   121,    81,
      82,    83,    84,    85,    86,    87,     0,    88,     0,    90,
       0,    89,     0,    82,    83,    84,    85,     0,     0,     0,
      88,     0,    52,    90,    89,     0,     0,    53,     0,    22,
      54,   -46,   -46,    65,    25,     0,    90,    55,    56,     0,
      57,    58,    59,    60,     0,    24,    82,    83,    84,    85,
      83,    84,    85,    88,     0,     0,    88,    89,     0,     0,
      89
};

static const yytype_int8 yycheck[] =
{
      52,    53,    54,    55,    28,     0,     7,     1,    28,    33,
       5,    14,    13,    65,     1,     1,    17,     3,    21,    19,
      14,    73,    97,    75,    76,    20,    20,    21,    15,    81,
      82,    83,    84,    85,    86,    87,     0,    89,    90,   114,
       7,   116,    28,    67,    25,    12,    19,    15,    15,    30,
      13,   126,   127,     3,    17,    50,    28,    19,    18,    26,
      27,    28,     3,     1,    20,     3,   118,     5,     6,     7,
       8,     9,    10,    11,     1,    13,     1,     4,     3,    17,
       5,     6,     7,     8,     9,    10,    11,     1,    13,    16,
      17,    29,    17,     7,    26,    16,    16,     4,    12,    18,
      14,    15,     1,     3,    29,    19,    20,    21,    22,    23,
       1,    25,    26,    27,    28,    14,     7,    16,     4,    15,
      15,    12,    21,     1,    15,     3,     4,     1,    19,    16,
      20,    22,    23,     7,    25,    26,    27,    28,    12,    17,
      28,    15,    16,    16,     1,    16,    18,    24,    24,     5,
       7,    63,    26,    27,    28,    12,    23,    50,    15,     4,
       5,     6,     7,     8,     9,    10,    11,    18,    13,    26,
      27,    28,    17,    67,     5,     6,     7,     8,     9,    10,
      11,   118,    13,    -1,    29,    16,    17,    -1,     5,     6,
       7,     8,     9,    10,    11,    -1,    13,    -1,    29,    16,
      17,    -1,     5,     6,     7,     8,     9,    10,    11,    -1,
      13,    -1,    29,    16,    17,     5,     6,     7,     8,     9,
      10,    11,    -1,    13,    -1,    -1,    29,    17,    18,     5,
       6,     7,     8,     9,    10,    11,    -1,    13,    -1,    29,
      -1,    17,    -1,     6,     7,     8,     9,    -1,    -1,    -1,
      13,    -1,     7,    29,    17,    -1,    -1,    12,    -1,     1,
      15,     3,     4,     5,    19,    -1,    29,    22,    23,    -1,
      25,    26,    27,    28,    -1,    17,     6,     7,     8,     9,
       7,     8,     9,    13,    -1,    -1,    13,    17,    -1,    -1,
      17
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    21,    33,    34,    35,    37,    38,    28,    39,
      40,     0,    34,     1,     3,    28,    36,    41,    42,    19,
      15,     3,     1,     4,    17,    19,    45,     1,    37,    48,
      49,     1,    16,    37,    43,    44,    18,    28,    36,    26,
      48,     3,    41,    50,    51,    20,    48,    16,    41,    16,
       4,    18,     7,    12,    15,    22,    23,    25,    26,    27,
      28,    45,    46,    47,    52,     5,     3,     4,    43,    52,
      52,    52,    52,    15,     1,    15,    15,    20,    46,     1,
       3,     5,     6,     7,     8,     9,    10,    11,    13,    17,
      29,    52,    50,    16,     1,     3,    52,    16,    52,     1,
      16,    52,    53,    52,    52,    52,    52,    52,    52,    52,
      28,     1,    52,    52,    16,    47,    16,    16,     4,    16,
      18,    18,     1,    47,    47,    53,    24,    24,    47,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    36,
      36,    37,    37,    38,    38,    39,    39,    40,    41,    41,
      41,    42,    42,    42,    43,    43,    44,    45,    46,    46,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      48,    48,    48,    49,    50,    50,    51,    51,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     2,     1,
       3,     1,     1,     5,     2,     1,     0,     1,     1,     4,
       3,     4,     3,     4,     3,     1,     2,     4,     2,     0,
       2,     1,     3,     5,     7,     5,     7,     4,     2,     3,
       2,     0,     2,     3,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     4,
       3,     4,     3,     1,     1,     1,     4,     4,     3,     1
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 107 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(Program,(yyloc).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);
        root = (yyval.type_treenode).t;}
#line 1527 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 112 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(ExtDefList,(yyloc).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1536 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 116 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(ExtDefList,(yyloc).first_line,NULL);}
#line 1542 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 118 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(ExtDef,(yyloc).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(SEMI,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1553 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 124 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(ExtDef,(yyloc).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(SEMI,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1563 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 129 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(ExtDef,(yyloc).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1573 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 134 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(error,(yyloc).first_line,NULL);
        HaveErrors++;
        char *tmp="Syntax error";
		insert_Error('B',(yyval.type_treenode).t->line,tmp);
    }
#line 1584 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 141 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(ExtDecList,(yyloc).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1592 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 144 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(ExtDecList,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(COMMA,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1603 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 152 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(Specifier,(yyloc).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(TYPE,(yylsp[0]).first_line,(void *)&(yyvsp[0].type_treenode).str);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1612 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 156 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Specifier,(yyloc).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1619 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 159 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(StructSpecifier,(yyloc).first_line,NULL);
        (yyvsp[-4].type_treenode).t = createnode(STRUCT,(yylsp[-4]).first_line,NULL);
        (yyvsp[-2].type_treenode).t = createnode(LC,(yylsp[-2]).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(RC,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-4].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-3].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1634 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 169 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.type_treenode).t = createnode(StructSpecifier,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(STRUCT,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1644 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 175 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(OptTag,(yyloc).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(ID,(yylsp[0]).first_line,(void *)&(yyvsp[0].type_treenode).str);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1653 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 179 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(OptTag,(yyloc).first_line,NULL);}
#line 1659 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 181 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Tag,(yyloc).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(ID,(yylsp[0]).first_line,(void *)&(yyvsp[0].type_treenode).str);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1667 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 185 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(VarDec,(yyloc).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(ID,(yylsp[0]).first_line,(void *)&(yyvsp[0].type_treenode).str);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1675 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 188 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(VarDec,(yyloc).first_line,NULL);
        (yyvsp[-2].type_treenode).t = createnode(LB,(yylsp[-2]).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(INT,(yylsp[-1]).first_line,(void *)&(yyvsp[-1].type_treenode).i);
        (yyvsp[0].type_treenode).t = createnode(RB,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-3].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1688 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 196 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(VarDec,(yyloc).first_line,NULL);
        HaveErrors++;
        char *tmp="Wrong Definition";
		insert_Error('B',(yyval.type_treenode).t->line,tmp);
        //printf("Error type B at line %d:Wrong Definition.\n",$$.t->line);
        }
#line 1699 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 203 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(FunDec,(yyloc).first_line,NULL);
        (yyvsp[-3].type_treenode).t = createnode(ID,(yylsp[-3]).first_line,(void *)&(yyvsp[-3].type_treenode).str);
        (yyvsp[-2].type_treenode).t = createnode(LP,(yylsp[-2]).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(RP,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-3].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1712 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 211 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(FunDec,(yyloc).first_line,NULL);
        (yyvsp[-2].type_treenode).t = createnode(ID,(yylsp[-2]).first_line,(void *)&(yyvsp[-2].type_treenode).str);
        (yyvsp[-1].type_treenode).t = createnode(LP,(yylsp[-1]).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(RP,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1724 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 218 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(FunDec,(yyloc).first_line,NULL);
        HaveErrors=HaveErrors+1;
        char *tmp="Wrong Function Definition";
		insert_Error('B',(yyval.type_treenode).t->line,tmp);
        //printf("Error type B at line %d:Wrong Function Definition.\n",$$.t->line);
    }
#line 1736 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 226 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(VarList,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(COMMA,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1746 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 231 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(VarList,(yyloc).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1753 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 234 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(ParamDec,(yyloc).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1761 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 238 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(CompSt,(yyloc).first_line,NULL);
        (yyvsp[-3].type_treenode).t = createnode(LC,(yylsp[-3]).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(RC,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-3].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1773 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 246 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(StmtList,(yyloc).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1781 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 249 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(StmtList,(yyloc).first_line,NULL);}
#line 1787 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 251 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Stmt,(yyloc).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(SEMI,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1796 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 255 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Stmt,(yyloc).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1803 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 257 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Stmt,(yyloc).first_line,NULL);
        (yyvsp[-2].type_treenode).t = createnode(RETURN,(yylsp[-2]).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(SEMI,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1814 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 263 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Stmt,(yyloc).first_line,NULL);
        (yyvsp[-4].type_treenode).t = createnode(IF,(yylsp[-4]).first_line,NULL);
        (yyvsp[-3].type_treenode).t = createnode(LP,(yylsp[-3]).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(RP,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-4].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-3].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1828 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 272 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Stmt,(yyloc).first_line,NULL);
        (yyvsp[-6].type_treenode).t = createnode(IF,(yylsp[-6]).first_line,NULL);
        (yyvsp[-5].type_treenode).t = createnode(LP,(yylsp[-5]).first_line,NULL);
        (yyvsp[-3].type_treenode).t = createnode(RP,(yylsp[-3]).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(ELSE,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-6].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-5].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-4].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-3].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1845 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 284 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Stmt,(yyloc).first_line,NULL);
        (yyvsp[-4].type_treenode).t = createnode(WHILE,(yylsp[-4]).first_line,NULL);
        (yyvsp[-3].type_treenode).t = createnode(LP,(yylsp[-3]).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(RP,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-4].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-3].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1859 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 293 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(Stmt,(yyloc).first_line,NULL);
        HaveErrors++;
        char *tmp="Wrong statement after if(...)";
		insert_Error('B',(yyval.type_treenode).t->line,tmp);
        //printf("Error type B at line %d:Wrong statement after \'if(...)\'.\n",$$.t->line); 
    }
#line 1871 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 300 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(Stmt,(yyloc).first_line,NULL);
        HaveErrors++;
        char *tmp="Unexpectd Expression";
		insert_Error('B',(yyval.type_treenode).t->line,tmp);
        //printf("Error type B at line %d:Unexpectd Expression.\n",$$.t->line);
    }
#line 1883 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 307 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(Stmt,(yyloc).first_line,NULL);
        HaveErrors++;
        char *tmp="Exexpectd \';\'";
		insert_Error('B',(yyval.type_treenode).t->line,tmp);
        //printf("Error type B at line %d:Expected \';\'.\n",$$.t->line); 
    }
#line 1895 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 315 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(Stmt,(yyloc).first_line,NULL);
        HaveErrors++;
        char *tmp="Exexpectd \';\'";
		insert_Error('B',(yyval.type_treenode).t->line,tmp);
        //printf("Error type B at line %d:Expected \';\'.\n",$$.t->line);         
    }
#line 1907 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 323 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(DefList,(yyloc).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1915 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 326 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(DefList,(yyloc).first_line,NULL);}
#line 1921 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 327 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(DefList,(yyloc).first_line,NULL);
        HaveErrors++;
        char *tmp="Syntax error";
		insert_Error('B',(yyval.type_treenode).t->line,tmp);
        //printf("Error type B at line %d:Syntax error.\n",$$.t->line);   
    }
#line 1933 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 335 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Def,(yyloc).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(SEMI,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1943 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 340 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(DecList,(yyloc).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1950 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 342 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(DecList,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(COMMA,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1960 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 348 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Dec,(yyloc).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1967 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 350 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Dec,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(ASSIGNOP,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1977 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 357 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(ASSIGNOP,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1987 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 362 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(AND,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 1997 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 367 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(OR,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2007 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 372 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(RELOP,(yylsp[-1]).first_line,(void *)&(yyvsp[-1].type_treenode).i);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2017 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 377 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(PLUS,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2027 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 382 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(SUB,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2037 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 387 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(STAR,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2047 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 392 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(DIV,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2057 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 397 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-2].type_treenode).t = createnode(LP,(yylsp[-2]).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(RP,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2068 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 403 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(MINUS,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2077 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 407 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(NOT,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2086 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 411 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-3].type_treenode).t = createnode(ID,(yylsp[-3]).first_line,(void *)&(yyvsp[-3].type_treenode).str);
        (yyvsp[-2].type_treenode).t = createnode(LP,(yylsp[-2]).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(RP,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-3].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2099 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 419 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-2].type_treenode).t = createnode(ID,(yylsp[-2]).first_line,(void *)&(yyvsp[-2].type_treenode).str);
        (yyvsp[-1].type_treenode).t = createnode(LP,(yylsp[-1]).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(RP,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2111 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 426 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-2].type_treenode).t = createnode(LB,(yylsp[-2]).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(RB,(yylsp[0]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-3].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2123 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 433 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(DOT,(yylsp[-1]).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(ID,(yylsp[0]).first_line,(void *)&(yyvsp[0].type_treenode).str);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2134 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 439 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(ID,(yylsp[0]).first_line,(void *)&(yyvsp[0].type_treenode).str);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2142 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 442 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(INT,(yylsp[0]).first_line,(void *)&(yyvsp[0].type_treenode).i);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2150 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 445 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        (yyvsp[0].type_treenode).t = createnode(FLOAT,(yylsp[0]).first_line,(void *)&(yyvsp[0].type_treenode).f);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2158 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 448 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        HaveErrors++;
        char* tmp="Unexpected operation after \'[\'";
		insert_Error('B',(yyval.type_treenode).t->line,tmp);
        //printf("Error type B at line %d:Unexpected operation after \'[\'.\n",$$.t->line);    
        }
#line 2170 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 455 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.type_treenode).t = createnode(Exp,(yyloc).first_line,NULL);
        HaveErrors++;
        char *tmp="Unexpected varlist after \'(\'";
		insert_Error('B',(yyval.type_treenode).t->line,tmp);
        //printf("Error type B at line %d:Unexpected varlist after \'(\'.\n",$$.t->line); 
    }
#line 2182 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 463 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Args,(yyloc).first_line,NULL);
        (yyvsp[-1].type_treenode).t = createnode(COMMA,(yylsp[-1]).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[-2].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[-1].type_treenode).t);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2192 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 468 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_treenode).t = createnode(Args,(yyloc).first_line,NULL);
        insert((yyval.type_treenode).t,(yyvsp[0].type_treenode).t);}
#line 2199 "./syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2203 "./syntax.tab.c" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
#line 471 "./syntax.y" /* yacc.c:1906  */


int yyerror(char* msg){

}

void print_Node(struct ErrorNode* node){
    printf("Error Type %c at line %d:%s.\n",node->ErrorType,node->Linenumber,node->Information);
}
void print_Errors(){
    if(HaveErrors==0) return;
    struct ErrorNode* p=ErrorHead;
    while(p!=NULL){
        print_Node(p);
        p=p->next;
    }
}
void insert_Error(char errorType,int linenumber,char* information){
    if(ErrorHead==NULL){
        ErrorHead=(struct ErrorNode*)malloc(sizeof(struct ErrorNode));
        ErrorHead->Linenumber=linenumber;
        ErrorHead->ErrorType=errorType;
        char* tmp=information;
        ErrorHead->Information=tmp;
        ErrorHead->next=NULL;
    }
    else{
        struct ErrorNode* p=ErrorHead;
        struct ErrorNode* q=(struct ErrorNode*)malloc(sizeof(struct ErrorNode));
        q->Linenumber=linenumber;
        q->ErrorType=errorType;
        q->next=NULL;
        char* tmp=information;
        q->Information=tmp;
        if(p->Linenumber>q->Linenumber){
            q->next=ErrorHead;
            ErrorHead=q;
            return;
        }
        while(p!=NULL){
            if(p->next==NULL && p->Linenumber<q->Linenumber){
                p->next=q;
                return;
            }
            if(p->Linenumber<=q->Linenumber && p->next->Linenumber>=q->Linenumber){
                q->next=p->next;
                p->next=q;
                return;
            }
            p=p->next;
        }
    }
}
void insert(struct GrammarTree *t1,struct GrammarTree *t2){
    if(t1->head == NULL)
    {
        t1->head = (struct ListNode*)malloc(sizeof(struct ListNode));
        t1->head->val = t2;
        t1->head->next = NULL;
    }
    else
    {
        struct ListNode *l = t1->head;
        while(l->next != NULL)
        {
            l = l->next;
        }
        l->next =(struct ListNode*)malloc(sizeof(struct ListNode));
        l = l->next;
        l->val = t2;
        l->next =  NULL;
    }
}
void __DFS(struct GrammarTree *n,int depth){
    struct ListNode *l = n->head;
    switch(n->type){
        case error:
            {
                for(int i = 0;i < depth;i++)
                    printf("  ");
                printf("error\n");
                return;
            }
        case Program: 
        case ExtDecList: 
        case ExtDef:
        case Specifier:
        case FunDec:
        case CompSt:
        case VarDec:
        case ExtDefList:
        case StructSpecifier:
        case OptTag:
        case DefList:
        case Tag:
        case VarList:
        case ParamDec:
        case StmtList:
        case Stmt:
        case Exp:
        case Def:
        case DecList:
        case Dec:
        case Args:
            if(l == NULL)
                return ;
            for(int i = 0;i < depth;i++)
                printf("  ");
            printf("%s (%d)\n",token_map[n->type],n->line);
            while(l != NULL)
            {
                __DFS(l->val,depth+1);
                l = l-> next;
            }
            return ;
        case TYPE:
            for(int i = 0;i < depth;i++)
                printf("  ");
            printf("TYPE: %s\n",n->val.str);
            return ;
        case ID:
            for(int i = 0;i < depth;i++)
                printf("  ");
            printf("ID: %s\n",n->val.str);
            return ;
        case INT:
            for(int i = 0;i < depth;i++)
                printf("  ");
            printf("INT: %d\n",n->val.i);
            return ;
        case FLOAT:
            for(int i = 0;i < depth;i++)
                printf("  ");
            printf("FLOAT: %f\n",n->val.f);
            return ;
        case SEMI:
        case COMMA:
        case ASSIGNOP:
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
        case AND:
        case OR:
        case NOT:
        case DOT:
        case LP:
        case RP:
        case LB:
        case RB:
        case LC:
        case RC:
        case STRUCT:
        case RETURN:
        case IF:
        case ELSE:
        case WHILE: 
        case RELOP: 
        case SUB:
        case LOWER_THAN_ELSE:
            for(int i = 0;i < depth;i++)
                printf("  ");
            printf("%s\n",token2_map[n->type - BASE_NUM]);
            return ;
    }
}
void print_tree(){
    if(HaveErrors==0)
        __DFS(root,0);
}
struct GrammarTree *createnode(int type,int line,void *value){
    struct GrammarTree *res= (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
    res->type = type;
    res->line = line;
    res->head = NULL;
    if(type == ID || type == TYPE)
    {
        res->val.str = *((char **)value);
    }
    else if(type == INT)
    {
        res->val.i = *((int *)value);
    }
    else if(type == FLOAT)
    {
        res->val.f = *(float *)value;
    }
    return res;
}
