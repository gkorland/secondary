/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 24 "parser.y"
   

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "token.h"
#include "parser.h"
#include "ast.h"
#include "../rmutil/alloc.h"

extern int yylineno;
extern char *yytext;

typedef struct {
    ParseNode *root;
    int ok;
    char *errorMsg;
}parseCtx;


void yyerror(char *s);
    
#line 33 "parser.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    ParseTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 44
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  ParseNode* yy8;
  SIValue yy22;
  time_t yy23;
  SIValueVector yy27;
  property yy44;
  int yy64;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  parseCtx *ctx ;
#define ParseARG_PDECL , parseCtx *ctx 
#define ParseARG_FETCH  parseCtx *ctx  = yypParser->ctx 
#define ParseARG_STORE yypParser->ctx  = ctx 
#define YYNSTATE 78
#define YYNRULE 35
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
#define YY_ACTTAB_COUNT (111)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    64,   43,   69,   78,    7,    5,   70,   68,   67,   66,
 /*    10 */    42,    7,    5,   63,   44,   41,   38,   23,   77,   72,
 /*    20 */    76,   73,   75,   74,   13,   19,   48,   20,   64,   35,
 /*    30 */    32,   29,   26,   18,   62,   65,   16,   39,   33,    6,
 /*    40 */    54,   63,   44,   41,   38,   23,   46,   45,  114,   15,
 /*    50 */    51,    8,   40,   10,   17,    3,    8,   14,   47,    8,
 /*    60 */     8,   61,   60,   71,   50,   65,   65,   49,   12,   65,
 /*    70 */    34,   30,   59,   31,   27,   58,   28,   24,   57,   25,
 /*    80 */    53,   56,    9,    5,   11,   55,    1,   52,    4,    2,
 /*    90 */   115,   36,   21,   37,  115,  115,  115,  115,  115,  115,
 /*   100 */   115,  115,  115,  115,  115,  115,  115,  115,  115,  115,
 /*   110 */    22,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    11,   15,   13,    0,    1,    2,   17,   18,   19,   20,
 /*    10 */    17,    1,    2,   24,   25,   26,   27,   28,    3,    4,
 /*    20 */     5,    6,    7,    8,    9,   10,   16,   12,   11,   29,
 /*    30 */    30,   31,   32,   38,   16,   40,   41,   17,   17,   15,
 /*    40 */    13,   24,   25,   26,   27,   28,   22,   23,   34,   35,
 /*    50 */    16,   37,   15,   15,   35,   21,   37,   35,   35,   37,
 /*    60 */    37,   16,   16,   38,   38,   40,   40,   38,   21,   40,
 /*    70 */    15,   17,   16,   15,   17,   16,   15,   17,   16,   15,
 /*    80 */    14,   16,   15,    2,   21,   16,   15,   39,   36,   21,
 /*    90 */    43,   42,   42,   40,   43,   43,   43,   43,   43,   43,
 /*   100 */    43,   43,   43,   43,   43,   43,   43,   43,   43,   43,
 /*   110 */    40,
};
#define YY_SHIFT_USE_DFLT (-15)
#define YY_SHIFT_COUNT (44)
#define YY_SHIFT_MIN   (-14)
#define YY_SHIFT_MAX   (81)
static const signed char yy_shift_ofst[] = {
 /*     0 */    24,  -11,  -11,  -11,  -11,   24,   24,   24,   15,   17,
 /*    10 */    17,    0,    0,   71,   10,    3,   34,   81,   68,   66,
 /*    20 */    27,   69,   63,   67,   65,   60,   64,   62,   57,   61,
 /*    30 */    59,   54,   58,   56,   21,   55,   46,   47,   38,   45,
 /*    40 */    20,   37,   18,   -7,  -14,
};
#define YY_REDUCE_USE_DFLT (-6)
#define YY_REDUCE_COUNT (13)
#define YY_REDUCE_MIN   (-5)
#define YY_REDUCE_MAX   (70)
static const signed char yy_reduce_ofst[] = {
 /*     0 */    14,   -5,   29,   26,   25,   23,   22,   19,   52,   70,
 /*    10 */    53,   50,   49,   48,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
 /*    10 */   113,  113,  113,  113,  113,  113,  113,   90,  113,  113,
 /*    20 */   113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
 /*    30 */   113,  113,  113,  113,  113,  113,  113,  113,  113,  113,
 /*    40 */   113,  113,  113,  113,  113,  102,  101,   91,   89,   99,
 /*    50 */   100,   98,   88,   87,   86,  108,  112,  111,  110,  109,
 /*    60 */   107,  106,  105,  104,  103,   97,   96,   95,   94,   93,
 /*    70 */    92,   85,   84,   83,   82,   81,   80,   79,
};

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "AND",           "OR",            "EQ",          
  "NE",            "GT",            "GE",            "LT",          
  "LE",            "IN",            "IS",            "NOW",         
  "LIKE",          "STRING",        "TK_NULL",       "LP",          
  "RP",            "INTEGER",       "FLOAT",         "TRUE",        
  "FALSE",         "COMMA",         "ENUMERATOR",    "IDENT",       
  "TODAY",         "TIME",          "UNIXTIME",      "TIME_ADD",    
  "TIME_SUB",      "DAYS",          "HOURS",         "MINUTES",     
  "SECONDS",       "error",         "query",         "cond",        
  "op",            "prop",          "value",         "vallist",     
  "timestamp",     "multivals",     "duration",    
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "query ::= cond",
 /*   1 */ "op ::= EQ",
 /*   2 */ "op ::= GT",
 /*   3 */ "op ::= LT",
 /*   4 */ "op ::= LE",
 /*   5 */ "op ::= GE",
 /*   6 */ "op ::= NE",
 /*   7 */ "cond ::= prop op value",
 /*   8 */ "cond ::= prop LIKE STRING",
 /*   9 */ "cond ::= prop IS TK_NULL",
 /*  10 */ "cond ::= prop IN vallist",
 /*  11 */ "cond ::= LP cond RP",
 /*  12 */ "cond ::= cond AND cond",
 /*  13 */ "cond ::= cond OR cond",
 /*  14 */ "value ::= INTEGER",
 /*  15 */ "value ::= STRING",
 /*  16 */ "value ::= FLOAT",
 /*  17 */ "value ::= TRUE",
 /*  18 */ "value ::= FALSE",
 /*  19 */ "value ::= timestamp",
 /*  20 */ "vallist ::= LP multivals RP",
 /*  21 */ "multivals ::= value COMMA value",
 /*  22 */ "multivals ::= multivals COMMA value",
 /*  23 */ "prop ::= ENUMERATOR",
 /*  24 */ "prop ::= IDENT",
 /*  25 */ "timestamp ::= NOW",
 /*  26 */ "timestamp ::= TODAY",
 /*  27 */ "timestamp ::= TIME LP INTEGER RP",
 /*  28 */ "timestamp ::= UNIXTIME LP INTEGER RP",
 /*  29 */ "timestamp ::= TIME_ADD LP timestamp COMMA duration RP",
 /*  30 */ "timestamp ::= TIME_SUB LP timestamp COMMA duration RP",
 /*  31 */ "duration ::= DAYS LP INTEGER RP",
 /*  32 */ "duration ::= HOURS LP INTEGER RP",
 /*  33 */ "duration ::= MINUTES LP INTEGER RP",
 /*  34 */ "duration ::= SECONDS LP INTEGER RP",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    case 35: /* cond */
{
#line 64 "parser.y"
 ParseNode_Free((yypminor->yy8)); 
#line 458 "parser.c"
}
      break;
    case 37: /* prop */
{
#line 131 "parser.y"

     
    if ((yypminor->yy44).name != NULL) { 
        free((yypminor->yy44).name); 
        (yypminor->yy44).name = NULL;
    } 

#line 471 "parser.c"
}
      break;
    case 39: /* vallist */
    case 41: /* multivals */
{
#line 111 "parser.y"
SIValueVector_Free(&(yypminor->yy27));
#line 479 "parser.c"
}
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParseAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_COUNT
   || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 34, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 35, 3 },
  { 35, 3 },
  { 35, 3 },
  { 35, 3 },
  { 35, 3 },
  { 35, 3 },
  { 35, 3 },
  { 38, 1 },
  { 38, 1 },
  { 38, 1 },
  { 38, 1 },
  { 38, 1 },
  { 38, 1 },
  { 39, 3 },
  { 41, 3 },
  { 41, 3 },
  { 37, 1 },
  { 37, 1 },
  { 40, 1 },
  { 40, 1 },
  { 40, 4 },
  { 40, 4 },
  { 40, 6 },
  { 40, 6 },
  { 42, 4 },
  { 42, 4 },
  { 42, 4 },
  { 42, 4 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 0: /* query ::= cond */
#line 53 "parser.y"
{ ctx->root = yymsp[0].minor.yy8; }
#line 809 "parser.c"
        break;
      case 1: /* op ::= EQ */
#line 56 "parser.y"
{ yygotominor.yy64 = EQ; }
#line 814 "parser.c"
        break;
      case 2: /* op ::= GT */
#line 57 "parser.y"
{ yygotominor.yy64 = GT; }
#line 819 "parser.c"
        break;
      case 3: /* op ::= LT */
#line 58 "parser.y"
{ yygotominor.yy64 = LT; }
#line 824 "parser.c"
        break;
      case 4: /* op ::= LE */
#line 59 "parser.y"
{ yygotominor.yy64 = LE; }
#line 829 "parser.c"
        break;
      case 5: /* op ::= GE */
#line 60 "parser.y"
{ yygotominor.yy64 = GE; }
#line 834 "parser.c"
        break;
      case 6: /* op ::= NE */
#line 61 "parser.y"
{ yygotominor.yy64 = NE; }
#line 839 "parser.c"
        break;
      case 7: /* cond ::= prop op value */
#line 66 "parser.y"
{ 
    /* Terminal condition of a single predicate */
    yygotominor.yy8 = NewPredicateNode(yymsp[-2].minor.yy44, yymsp[-1].minor.yy64, yymsp[0].minor.yy22);
}
#line 847 "parser.c"
        break;
      case 8: /* cond ::= prop LIKE STRING */
#line 72 "parser.y"
{ 
    yygotominor.yy8 = NewPredicateNode(yymsp[-2].minor.yy44, LIKE, SI_StringValC(strdup(yymsp[0].minor.yy0.strval)));
}
#line 854 "parser.c"
        break;
      case 9: /* cond ::= prop IS TK_NULL */
#line 77 "parser.y"
{ 
    yygotominor.yy8 = NewPredicateNode(yymsp[-2].minor.yy44, IS, SI_NullVal());
}
#line 861 "parser.c"
        break;
      case 10: /* cond ::= prop IN vallist */
#line 81 "parser.y"
{ 
    /* Terminal condition of a single IN predicate */
    yygotominor.yy8 = NewInPredicateNode(yymsp[-2].minor.yy44, IN, yymsp[0].minor.yy27);
}
#line 869 "parser.c"
        break;
      case 11: /* cond ::= LP cond RP */
#line 86 "parser.y"
{ 
  yygotominor.yy8 = yymsp[-1].minor.yy8;
}
#line 876 "parser.c"
        break;
      case 12: /* cond ::= cond AND cond */
#line 90 "parser.y"
{
  yygotominor.yy8 = NewConditionNode(yymsp[-2].minor.yy8, AND, yymsp[0].minor.yy8);
}
#line 883 "parser.c"
        break;
      case 13: /* cond ::= cond OR cond */
#line 94 "parser.y"
{
  yygotominor.yy8 = NewConditionNode(yymsp[-2].minor.yy8, OR, yymsp[0].minor.yy8);
}
#line 890 "parser.c"
        break;
      case 14: /* value ::= INTEGER */
#line 102 "parser.y"
{  yygotominor.yy22 = SI_LongVal(yymsp[0].minor.yy0.intval); }
#line 895 "parser.c"
        break;
      case 15: /* value ::= STRING */
#line 103 "parser.y"
{  yygotominor.yy22 = SI_StringValC(strdup(yymsp[0].minor.yy0.strval)); }
#line 900 "parser.c"
        break;
      case 16: /* value ::= FLOAT */
#line 104 "parser.y"
{  yygotominor.yy22 = SI_DoubleVal(yymsp[0].minor.yy0.dval); }
#line 905 "parser.c"
        break;
      case 17: /* value ::= TRUE */
#line 105 "parser.y"
{ yygotominor.yy22 = SI_BoolVal(1); }
#line 910 "parser.c"
        break;
      case 18: /* value ::= FALSE */
#line 106 "parser.y"
{ yygotominor.yy22 = SI_BoolVal(0); }
#line 915 "parser.c"
        break;
      case 19: /* value ::= timestamp */
#line 107 "parser.y"
{ yygotominor.yy22 = SI_TimeVal(yymsp[0].minor.yy23); }
#line 920 "parser.c"
        break;
      case 20: /* vallist ::= LP multivals RP */
#line 114 "parser.y"
{
    yygotominor.yy27 = yymsp[-1].minor.yy27;
    
}
#line 928 "parser.c"
        break;
      case 21: /* multivals ::= value COMMA value */
#line 118 "parser.y"
{
      yygotominor.yy27 = SI_NewValueVector(2);
      SIValueVector_Append(&yygotominor.yy27, yymsp[-2].minor.yy22);
      SIValueVector_Append(&yygotominor.yy27, yymsp[0].minor.yy22);
}
#line 937 "parser.c"
        break;
      case 22: /* multivals ::= multivals COMMA value */
#line 124 "parser.y"
{
    SIValueVector_Append(&yymsp[-2].minor.yy27, yymsp[0].minor.yy22);
    yygotominor.yy27 = yymsp[-2].minor.yy27;
}
#line 945 "parser.c"
        break;
      case 23: /* prop ::= ENUMERATOR */
#line 139 "parser.y"
{ yygotominor.yy44.id = yymsp[0].minor.yy0.intval; yygotominor.yy44.name = NULL;  }
#line 950 "parser.c"
        break;
      case 24: /* prop ::= IDENT */
#line 140 "parser.y"
{ yygotominor.yy44.name = yymsp[0].minor.yy0.strval; yygotominor.yy44.id = 0;  }
#line 955 "parser.c"
        break;
      case 25: /* timestamp ::= NOW */
#line 144 "parser.y"
{
    yygotominor.yy23 = time(NULL);
}
#line 962 "parser.c"
        break;
      case 26: /* timestamp ::= TODAY */
#line 148 "parser.y"
{
    time_t t = time(NULL);
    yygotominor.yy23 = t - t % 86400;
}
#line 970 "parser.c"
        break;
      case 27: /* timestamp ::= TIME LP INTEGER RP */
      case 28: /* timestamp ::= UNIXTIME LP INTEGER RP */ yytestcase(yyruleno==28);
#line 153 "parser.y"
{
    yygotominor.yy23 = (time_t)yymsp[-1].minor.yy0.intval;
}
#line 978 "parser.c"
        break;
      case 29: /* timestamp ::= TIME_ADD LP timestamp COMMA duration RP */
#line 161 "parser.y"
{
    yygotominor.yy23 = yymsp[-3].minor.yy23 + yymsp[-1].minor.yy64;
}
#line 985 "parser.c"
        break;
      case 30: /* timestamp ::= TIME_SUB LP timestamp COMMA duration RP */
#line 165 "parser.y"
{
    yygotominor.yy23 = yymsp[-3].minor.yy23 - yymsp[-1].minor.yy64;
}
#line 992 "parser.c"
        break;
      case 31: /* duration ::= DAYS LP INTEGER RP */
#line 171 "parser.y"
{
    yygotominor.yy64 = yymsp[-1].minor.yy0.intval * 86400;
}
#line 999 "parser.c"
        break;
      case 32: /* duration ::= HOURS LP INTEGER RP */
#line 174 "parser.y"
{
    yygotominor.yy64 = yymsp[-1].minor.yy0.intval * 3600;
}
#line 1006 "parser.c"
        break;
      case 33: /* duration ::= MINUTES LP INTEGER RP */
#line 177 "parser.y"
{
    yygotominor.yy64 = yymsp[-1].minor.yy0.intval * 60;
}
#line 1013 "parser.c"
        break;
      case 34: /* duration ::= SECONDS LP INTEGER RP */
#line 180 "parser.y"
{
    yygotominor.yy64 = yymsp[-1].minor.yy0.intval;
}
#line 1020 "parser.c"
        break;
      default:
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 11 "parser.y"
  

    //yyerror(yytext);

    int len =strlen(yytext)+100; 
    char msg[len];

    snprintf(msg, len, "Syntax error in WHERE line %d near '%s'", yylineno, yytext);

    ctx->ok = 0;
    ctx->errorMsg = strdup(msg);
#line 1094 "parser.c"
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
#line 184 "parser.y"


  /* Definitions of flex stuff */
 // extern FILE *yyin;
  typedef struct yy_buffer_state *YY_BUFFER_STATE;
  int             yylex( void );
  YY_BUFFER_STATE yy_scan_string( const char * );
  YY_BUFFER_STATE yy_scan_bytes( const char *, size_t );
  void            yy_delete_buffer( YY_BUFFER_STATE );
  
  


ParseNode *ParseQuery(const char *c, size_t len, char **err)  {

    //printf("Parsing query %s\n", c);
    yy_scan_bytes(c, len);
    void* pParser = ParseAlloc (malloc);        
    int t = 0;

    parseCtx ctx = {.root = NULL, .ok = 1, .errorMsg = NULL };
    //ParseNode *ret = NULL;
    //ParserFree(pParser);
    while (ctx.ok && 0 != (t = yylex())) {
        Parse(pParser, t, tok, &ctx);                
    }
    if (ctx.ok) {
        Parse (pParser, 0, tok, &ctx);
    }
    ParseFree(pParser, free);
    if (err) {
        *err = ctx.errorMsg;
    }
    return ctx.root;
  }
   


#line 1324 "parser.c"
