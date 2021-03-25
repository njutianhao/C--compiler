%locations
%{
    #include<stdio.h>
    #include"lex.yy.c"
    enum RELOP{
        L = 0,LE,G,GE
    };
    enum token{
        Program = 1, ExtDecList, ExtDef, Specifier, FunDec, CompSt, 
        VarDec, ExtDefList, StructSpecifier,
        OptTag, DefList, Tag, VarList, ParamDec,
        StmtList, Stmt, Exp, Def, DecList, Dec, Args
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
    struct GrammarTree *root;
%}

%union{
    int type_int;
    float type_float;
    double type_double;
    char * type_str;
    struct GrammarTree *type_treenode;
}

%token <type_treenode> MULTI_LINE_NOTES_BEGIN MULTI_LINE_NOTES_END
%token <type_treenode> SEMI COMMA
%token <type_treenode> ASSIGNOP RELOP 
%token <type_treenode> PLUS MINUS STAR DIV
%token <type_treenode> AND OR NOT
%token <type_treenode> DOT
%token <type_treenode> TYPE
%token <type_treenode> LP RP LB RB LC RC 
%token <type_treenode> STRUCT
%token <type_treenode> RETURN
%token <type_treenode> IF ELSE WHILE 
%token <type_treenode> INT
%token <type_treenode> FLOAT 
%token <type_treenode> ID

%type <type_treenode> Program ExtDecList ExtDef Specifier FunDec CompSt VarDec ExtDefList
%type <type_treenode> StructSpecifier OptTag DefList Tag
%type <type_treenode> VarList ParamDec
%type <type_treenode> StmtList Stmt Exp
%type <type_treenode> Def DecList Dec
%type <type_treenode> Args


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
Program : ExtDefList {
        $$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Program; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        root = $$;}
    ; 
ExtDefList : ExtDef ExtDefList {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = ExtDefList; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        insert($$,$2);}
    | {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = ExtDefList; 
        $$->line = @$.first_line; 
        $$->head = NULL;}
    ;
ExtDef : Specifier ExtDecList SEMI {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = ExtDef; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        insert($$,$2);
        $3 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3->type = SEMI;
        $3->line = @3.first_line;
        $3->head = NULL;
        insert($$,$3);}
    | Specifier SEMI {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = ExtDef; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = SEMI;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);}
    | Specifier FunDec CompSt {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = ExtDef; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        insert($$,$2);
        insert($$,$3);}
    ;
ExtDecList : VarDec {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = ExtDecList; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);}
    | VarDec COMMA ExtDecList {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = ExtDecList; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = COMMA;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);}
    ;

Specifier : TYPE {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Specifier; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = TYPE;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);}
    | StructSpecifier {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Specifier; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);}
    ;
StructSpecifier : STRUCT OptTag LC DefList RC {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = StructSpecifier; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = STRUCT;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        insert($$,$2);
        $3 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3->type = LC;
        $3->line = @3.first_line;
        $3->head = NULL;
        insert($$,$3);
        insert($$,$4);
        $5 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $5->type = RC;
        $5->line = @5.first_line;
        $5->head = NULL;
        insert($$,$5);}
    | STRUCT Tag {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = StructSpecifier; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = STRUCT;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        insert($$,$2);}
    ;
OptTag : ID {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = OptTag; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = ID;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);}
    |  {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = OptTag; 
        $$->line = @$.first_line; 
        $$->head = NULL;}
    ;
Tag : ID {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Tag; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = ID;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);}

VarDec : ID {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = VarDec; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = ID;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);}
    | VarDec LB INT RB {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = VarDec; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = LB;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        $3 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3->type = INT;
        $3->line = @3.first_line;
        $3->head = NULL;
        insert($$,$3);
        $4 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4->type = RB;
        $4->line = @4.first_line;
        $4->head = NULL;
        insert($$,$4);}
    ;
FunDec : ID LP VarList RP {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = FunDec; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = ID;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = LP;
        $2->line = @2.first_line;
        $2->head = LP;
        insert($$,$2);
        insert($$,$3);
        $4 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4->type = RP;
        $4->line = @4.first_line;
        $4->head = NULL;
        insert($$,$4);}
    | ID LP RP {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = FunDec; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = ID;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = LP;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        $3 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3->type = RP;
        $3->line = @3.first_line;
        $3->head = NULL;
        insert($$,$3);}
    ;
VarList : ParamDec COMMA VarList {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = VarList; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = COMMA;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);}
    | ParamDec {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = VarList; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);}
    ;
ParamDec : Specifier VarDec {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = ParamDec; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        insert($$,$2);}

CompSt : LC DefList StmtList RC {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = CompSt; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = LC;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        insert($$,$2);
        insert($$,$3);
        $4 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4->type = RC;
        $4->line = @4.first_line;
        $4->head = NULL;
        insert($$,$4);}
StmtList : Stmt StmtList {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = StmtList; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        insert($$,$2);}
    | {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = StmtList; 
        $$->line = @$.first_line; 
        $$->head = NULL;}
    ;
Stmt : Exp SEMI {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Stmt; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = SEMI;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);}
    | CompSt {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Stmt; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);}
    | RETURN Exp SEMI {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Stmt; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = RETURN;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        insert($$,$2);
        $3 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3->type = SEMI;
        $3->line = @3.first_line;
        $3->head = NULL;
        insert($$,$3);}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Stmt; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = IF;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = LP;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);
        $4 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4->type = RP;
        $4->line = @4.first_line;
        $4->head = NULL;
        insert($$,$4);
        insert($$,$5);}
    | IF LP Exp RP Stmt ELSE Stmt {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Stmt; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = IF;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = LP;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);
        $4 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4->type = RP;
        $4->line = @4.first_line;
        $4->head = NULL;
        insert($$,$4);
        insert($$,$5);
        $6 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $6->type = ELSE;
        $6->line = @6.first_line;
        $6->head = NULL;
        insert($$,$6);
        insert($$,$7);}
    | WHILE LP Exp RP Stmt {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Stmt; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = WHILE;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = LP;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);
        $4 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4->type = RP;
        $4->line = @4.first_line;
        $4->head = NULL;
        insert($$,$4);
        insert($$,$5);}
    ;

DefList : Def DefList {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = DefList; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        insert($$,$2);}
    | {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = DefList; 
        $$->line = @$.first_line; 
        $$->head = NULL;}
    ;
Def : Specifier DecList SEMI {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Def; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        insert($$,$2);
        $3 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3->type = SEMI;
        $3->line = @3.first_line;
        $3->head = NULL;
        insert($$,$3);}
DecList : Dec {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = DecList; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);}
    | Dec COMMA DecList {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = DecList; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = COMMA;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);}
    ;
Dec : VarDec {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Dec; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);}
    | VarDec ASSIGNOP Exp {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Dec; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = ASSIGNOP;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);}
    ;

Exp : Exp ASSIGNOP Exp {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = ASSIGNOP;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);}
    | Exp AND Exp {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = AND;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);}
    | Exp OR Exp {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = OR;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);}
    | Exp RELOP Exp {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = RELOP;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);}
    | Exp PLUS Exp {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = PLUS;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);}
    | Exp MINUS Exp {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = MINUS;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);}
    | Exp STAR Exp {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = STAR;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);}
    | Exp DIV Exp {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = DIV;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);}
    | LP Exp RP {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = LP;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        insert($$,$2);
        $3 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3->type = RP;
        $3->line = @3.first_line;
        $3->head = NULL;
        insert($$,$3);}
    | MINUS Exp {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = MINUS;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        insert($$,$2);}
    | NOT Exp {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = NOT;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        insert($$,$2);}
    | ID LP Args RP {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = ID;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = LP;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);
        $4 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4->type = RP;
        $4->line = @4.first_line;
        $4->head = NULL;
        insert($$,$4);}
    | ID LP RP {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = ID;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = LP;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        $3 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3->type = RP;
        $3->line = @3.first_line;
        $3->head = NULL;
        insert($$,$3);}
    | Exp LB Exp RB {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = LB;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);
        $4 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4->type = RB;
        $4->line = @4.first_line;
        $4->head = NULL;
        insert($$,$4);}
    | Exp DOT ID {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = DOT;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        $3 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3->type = ID;
        $3->line = @3.first_line;
        $3->head = NULL;
        insert($$,$3);}
    | ID {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = ID;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);}
    | INT {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = INT;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);}
    | FLOAT {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Exp; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        $1 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1->type = FLOAT;
        $1->line = @1.first_line;
        $1->head = NULL;
        insert($$,$1);}
    ;
Args : Exp COMMA Args {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Args; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);
        $2 = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2->type = COMMA;
        $2->line = @2.first_line;
        $2->head = NULL;
        insert($$,$2);
        insert($$,$3);}
    | Exp {$$ = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$->type = Args; 
        $$->line = @$.first_line; 
        $$->head = NULL;
        insert($$,$1);}
    ;
%%
