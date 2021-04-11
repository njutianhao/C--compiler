#ifndef GRAMMARTREE_H
#define GRAMMARTREE_H
#include<stdio.h>
#include<stdarg.h>
#include"SymbolTable.h"
#include<stdlib.h>
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
union SDDVal{
    Type t;
    char *str;
    FieldList f;
};
struct GrammarTree;
struct ListNode{
    struct GrammarTree *val;
    struct ListNode *next;
};
struct GrammarTree{
    int line;
    union TreeVal val;
    union SDDVal syn;
    union SDDVal inh;
    int type;
    struct ListNode *head;
};
struct ErrorNode{
    int Linenumber;
    char* ErrorType;
    char *Information;
    struct ErrorNode* next;
};
struct GrammarTree *root;
extern char *token_map[];
extern char *token2_map[];

struct ErrorNode *ErrorHead;
int HaveErrors;
void print_Errors();
void insert_Error(char*errorType,int linenumber,char* information);

void print_Node(struct ErrorNode* node);
void insert(struct GrammarTree *t1,struct GrammarTree *t2);
struct GrammarTree *createnode(int type,int line,void *value);
void insertall(struct GrammarTree *parent,int num,...);
void __DFS(struct GrammarTree *n,int depth);
void print_tree();



int try_insert(Type type_in,int line,char* name);
struct GrammarTree *get_child(struct GrammarTree *node,int index);
void SDT();
void SDT_DFS(struct GrammarTree *node);
void handle_ExtDefList(struct GrammarTree *node);
void handle_ExtDef(struct GrammarTree *node);
int handle_Specifier(struct GrammarTree *node);
int handle_StructSpecifier(struct GrammarTree *node);
void handle_OptTag(struct GrammarTree *node);
int handle_VarList(struct GrammarTree *node);
void handle_DefList(struct GrammarTree *node);
void handle_Def(struct GrammarTree *node);
void handle_DecList(struct GrammarTree *node);
int handle_Dec(struct GrammarTree *node);
int handle_VarDec(struct GrammarTree *node);
int handle_FunDec(struct GrammarTree *node);
void handle_CompSt(struct GrammarTree *node);
void handle_ID(struct GrammarTree *node);
int handle_VarList(struct GrammarTree *node);
int handle_ParamDec(struct GrammarTree *node);
void handle_StmtList(struct GrammarTree *node);
void handle_Stmt(struct GrammarTree *node);
void handle_ExtDecList(struct GrammarTree *node);
int handle_Exp(struct GrammarTree *node);
#endif