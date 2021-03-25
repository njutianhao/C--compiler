%locations
%{
    #include<stdio.h>
    #include"lex.yy.c"
    enum RELOP{
        L = 0,LE,G,GE
    };
    union TreeVal{
        int i;
        float f;
        char c;
        char *str;
        enum RELOP r;
    };
    struct GrammarTree;
    struct ListNode{
        struct GrammarTree *val;
        struct ListNode *next;
    };
    struct GrammarTree{
        int line;
        int column;
        union TreeVal val;
        enum yytokentype type;
        struct ListNode *head;
    };
    void insert(struct GrammarTree *t1,struct GrammarTree *t2){
        struct ListNode *old_head = t1->head;
        t1->head =(struct ListNode *)malloc(sizeof(struct ListNode));
        t1->head->val = t2;
        t1->head->next = old_head;
    }
%}

%union{
    int type_int;
    float type_float;
    double type_double;
    char * type_str;
}

%token <GrammarTree> MULTI_LINE_NOTES_BEGIN MULTI_LINE_NOTES_END
%token <GrammarTree> SEMI COMMA
%token <GrammarTree> ASSIGNOP RELOP 
%token <GrammarTree> PLUS MINUS STAR DIV
%token <GrammarTree> AND OR NOT
%token <GrammarTree> DOT
%token <GrammarTree> TYPE
%token <GrammarTree> LP RP LB RB LC RC 
%token <GrammarTree> STRUCT
%token <GrammarTree> RETURN
%token <GrammarTree> IF ELSE WHILE 
%token <GrammarTree> INT
%token <GrammarTree> FLOAT 
%token <GrammarTree> ID

%right ASSIGNOP
%left AND OR 
%left RELOP
%left PLUS SUB /*TODO:differ sub and minus*/
%left STAR DIV
%right MINUS NOT
%left LP RP LB RB DOT

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
Program : ExtDefList
    ;
ExtDefList : ExtDef ExtDefList 
    | 
    ;
ExtDef : Specifier ExtDecList SEMI
    | Specifier SEMI
    | Specifier FunDec CompSt
    ;
ExtDecList : VarDec
    | VarDec COMMA ExtDecList  
    ;

Specifier : TYPE
    | StructSpecifier
    ;
StructSpecifier : STRUCT OptTag LC DefList RC
    | STRUCT Tag
    ;
OptTag : ID
    | 
    ;
Tag : ID

VarDec : ID
    | VarDec LB INT RB
    ;
FunDec : ID LP VarList RP 
    | ID LP RP
    ;
VarList : ParamDec COMMA VarList   
    | ParamDec
    ;
ParamDec : Specifier VarDec

CompSt : LC DefList StmtList RC
StmtList : Stmt StmtList
    | 
    ;
Stmt : Exp SEMI
    | CompSt
    | RETURN Exp SEMI
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE
    | IF LP Exp RP Stmt ELSE Stmt 
    | WHILE LP Exp RP Stmt
    ;

DefList : Def DefList
    |
    ;
Def : Specifier DecList SEMI
DecList : Dec
    | Dec COMMA DecList
    ;
Dec : VarDec
    | VarDec ASSIGNOP Exp
    ;

Exp : Exp ASSIGNOP Exp 
    | Exp AND Exp 
    | Exp OR Exp
    | Exp RELOP Exp 
    | Exp PLUS Exp
    | Exp MINUS Exp 
    | Exp STAR Exp 
    | Exp DIV Exp 
    | LP Exp RP
    | MINUS Exp 
    | NOT Exp 
    | ID LP Args RP 
    | ID LP RP
    | Exp LB Exp RB
    | Exp DOT ID
    | ID 
    | INT 
    | FLOAT 
    ;
Args : Exp COMMA Args
    | Exp
    ;
%%
