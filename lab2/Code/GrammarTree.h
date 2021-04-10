#ifndef GRAMMARTREE_H
#define GRAMMARTREE_H
#include<stdio.h>
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
struct GrammarTree;
struct ListNode{
    struct GrammarTree *val;
    struct ListNode *next;
};
struct GrammarTree{
    int line;
    union TreeVal val;
    union TreeVal syn;
    union TreeVal inh;
    int type;
    struct ListNode *head;
};
char *token_map[];
char *token2_map[];
struct ErrorNode *ErrorHead;
int HaveErrors;
struct GrammarTree *root;
void print_Node(struct ErrorNode* node);
void print_Errors();
void insert_Error(char *errorType,int linenumber,char* information);
void insert(struct GrammarTree *t1,struct GrammarTree *t2);
struct GrammarTree *createnode(int type,int line,void *value);
void insertall(struct GrammarTree *parent,int num,...);
void __DFS(struct GrammarTree *n,int depth);
void print_tree();
void SDT();
void SDT_DFS(struct GrammarTree *node);
#endif