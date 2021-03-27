%locations
%{
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
    char *token2_map[] = {"MULTI_LINE_NOTES_BEGIN","MULTI_LINE_NOTES_END","SEMI","COMMA","ASSIGNOP","PLUS",
                          "MINUS","STAR","DIV","AND","OR","NOT","DOT","TYPE","LP","RP","LB","RB" ,"LC","RC","STRUCT","RETURN",
                          "IF","ELSE","WHILE","INT","FLOAT","ID","RELOP","SUB","LOWER_THAN_ELSE"};
    union TreeVal{
        int i;
        float f;
        char *str;
    };
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
    void insert(struct GrammarTree *t1,struct GrammarTree *t2){
        struct ListNode *old_head = t1->head;
        t1->head =(struct ListNode *)malloc(sizeof(struct ListNode));
        t1->head->val = t2;
        t1->head->next = old_head;
    }
    struct GrammarTree *root;
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
                for(int i = 0;i < depth;i++)
                    printf("  ");
                printf("%s\n",token2_map[n->type - BASE_NUM]);
                return ;
        }
    }
    void print_tree(){
        //if(HaveErrors==0)
         __DFS(root,0);
    }
%}

%union{
    union {
        struct GrammarTree * t;
        int i;
        float f;
        char *str;
    }type_treenode;
}

%token <type_treenode> MULTI_LINE_NOTES_BEGIN MULTI_LINE_NOTES_END
%token <type_treenode> SEMI COMMA
%token <type_treenode> ASSIGNOP
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
%token <type_treenode> RELOP 

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
        $$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Program; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        root = $$.t;}
    ; 
ExtDefList : ExtDef ExtDefList {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = ExtDefList; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);}
    | {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = ExtDefList; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;}
    ;
ExtDef : Specifier ExtDecList SEMI {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = ExtDef; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);
        $3.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3.t->type = SEMI;
        $3.t->line = @3.first_line;
        $3.t->head = NULL;
        insert($$.t,$3.t);}
    | Specifier SEMI {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = ExtDef; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = SEMI;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);}
    | Specifier FunDec CompSt {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = ExtDef; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);
        insert($$.t,$3.t);}   
    ;
ExtDecList : VarDec {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = ExtDecList; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);}
    | VarDec COMMA ExtDecList {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = ExtDecList; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = COMMA;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);}
    ;

Specifier : TYPE {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Specifier; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = TYPE;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        insert($$.t,$1.t);}
    | StructSpecifier {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Specifier; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);}
    ;
StructSpecifier : STRUCT OptTag LC DefList RC {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = StructSpecifier; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = STRUCT;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);
        $3.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3.t->type = LC;
        $3.t->line = @3.first_line;
        $3.t->head = NULL;
        insert($$.t,$3.t);
        insert($$.t,$4.t);
        $5.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $5.t->type = RC;
        $5.t->line = @5.first_line;
        $5.t->head = NULL;
        insert($$.t,$5.t);}
    | STRUCT Tag {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = StructSpecifier; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = STRUCT;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);}
    ;
OptTag : ID {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = OptTag; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        char *tmp = $1.str;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = ID;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        $1.t->val.str = tmp;
        insert($$.t,$1.t);}
    |  {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = OptTag; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;}
    ;
Tag : ID {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Tag; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        char *tmp = $1.str;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = ID;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        $1.t->val.str = tmp;
        insert($$.t,$1.t);}

VarDec : ID {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = VarDec; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        char *tmp = $1.str;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = ID;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        $1.t->val.str = tmp;
        insert($$.t,$1.t);}
    | VarDec LB INT RB {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = VarDec; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = LB;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        $3.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3.t->type = INT;
        $3.t->line = @3.first_line;
        $3.t->head = NULL;
        insert($$.t,$3.t);
        $4.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4.t->type = RB;
        $4.t->line = @4.first_line;
        $4.t->head = NULL;
        insert($$.t,$4.t);}
    ;
FunDec : ID LP VarList RP {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = FunDec; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        char *tmp = $1.str;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = ID;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        $1.t->val.str = tmp;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = LP;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);
        $4.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4.t->type = RP;
        $4.t->line = @4.first_line;
        $4.t->head = NULL;
        insert($$.t,$4.t);}
    | ID LP RP {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = FunDec; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        char *tmp = $1.str;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = ID;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        $1.t->val.str = tmp;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = LP;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        $3.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3.t->type = RP;
        $3.t->line = @3.first_line;
        $3.t->head = NULL;
        insert($$.t,$3.t);}
    ;
VarList : ParamDec COMMA VarList {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = VarList; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = COMMA;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);}
    | ParamDec {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = VarList; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);}
    ;
ParamDec : Specifier VarDec {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = ParamDec; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);}
    ;
CompSt : LC DefList StmtList RC {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = CompSt; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = LC;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);
        insert($$.t,$3.t);
        $4.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4.t->type = RC;
        $4.t->line = @4.first_line;
        $4.t->head = NULL;
        insert($$.t,$4.t);}
    ;
StmtList : Stmt StmtList {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = StmtList; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);}
    | {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = StmtList; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;}
    ;
Stmt : Exp SEMI {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Stmt; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = SEMI;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);}
    | CompSt {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Stmt; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);}
    | RETURN Exp SEMI {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Stmt; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = RETURN;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);
        $3.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3.t->type = SEMI;
        $3.t->line = @3.first_line;
        $3.t->head = NULL;
        insert($$.t,$3.t);}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Stmt; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = IF;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = LP;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);
        $4.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4.t->type = RP;
        $4.t->line = @4.first_line;
        $4.t->head = NULL;
        insert($$.t,$4.t);
        insert($$.t,$5.t);}
    | IF LP Exp RP Stmt ELSE Stmt {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Stmt; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = IF;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = LP;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);
        $4.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4.t->type = RP;
        $4.t->line = @4.first_line;
        $4.t->head = NULL;
        insert($$.t,$4.t);
        insert($$.t,$5.t);
        $6.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $6.t->type = ELSE;
        $6.t->line = @6.first_line;
        $6.t->head = NULL;
        insert($$.t,$6.t);
        insert($$.t,$7.t);}
    | WHILE LP Exp RP Stmt {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Stmt; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = WHILE;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = LP;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);
        $4.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4.t->type = RP;
        $4.t->line = @4.first_line;
        $4.t->head = NULL;
        insert($$.t,$4.t);
        insert($$.t,$5.t);}
    | IF LP Exp RP error ELSE Stmt {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = error; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        printf("Error type B at line %d:Wrong statement.\n",yylineno);}
    ;
DefList : Def DefList {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = DefList; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);}
    | {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = DefList; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;}
    ;
Def : Specifier DecList SEMI {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Def; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);
        $3.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3.t->type = SEMI;
        $3.t->line = @3.first_line;
        $3.t->head = NULL;
        insert($$.t,$3.t);}
DecList : Dec {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = DecList; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);}
    | Dec COMMA DecList {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = DecList; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = COMMA;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);}
    ;
Dec : VarDec {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Dec; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);}
    | VarDec ASSIGNOP Exp {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Dec; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = ASSIGNOP;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);}
    ;

Exp : Exp ASSIGNOP Exp {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = ASSIGNOP;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);}
    | Exp AND Exp {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = AND;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);}
    | Exp OR Exp {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = OR;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);}
    | Exp RELOP Exp {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        int tmp = $2.i;
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = RELOP;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        $2.t->val.i = tmp;
        insert($$.t,$2.t);
        insert($$.t,$3.t);}
    | Exp PLUS Exp {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = PLUS;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);}
    | Exp MINUS Exp {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = MINUS;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);}
    | Exp STAR Exp {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = STAR;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);}
    | Exp DIV Exp {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = DIV;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);}
    | LP Exp RP {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = LP;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);
        $3.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3.t->type = RP;
        $3.t->line = @3.first_line;
        $3.t->head = NULL;
        insert($$.t,$3.t);}
    | MINUS Exp {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = MINUS;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);}
    | NOT Exp {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = NOT;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        insert($$.t,$1.t);
        insert($$.t,$2.t);}
    | ID LP Args RP {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        char *tmp = $1.str;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = ID;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        $1.t->val.str = tmp;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = LP;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);
        $4.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4.t->type = RP;
        $4.t->line = @4.first_line;
        $4.t->head = NULL;
        insert($$.t,$4.t);}
    | ID LP RP {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        char *tmp = $1.str;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = ID;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        $1.t->val.str = tmp;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = LP;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        $3.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3.t->type = RP;
        $3.t->line = @3.first_line;
        $3.t->head = NULL;
        insert($$.t,$3.t);}
    | Exp LB Exp RB {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = LB;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);
        $4.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $4.t->type = RB;
        $4.t->line = @4.first_line;
        $4.t->head = NULL;
        insert($$.t,$4.t);}
    | Exp DOT ID {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        char *tmp = $3.str;
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = DOT;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        $3.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $3.t->type = ID;
        $3.t->line = @3.first_line;
        $3.t->head = NULL;
        $3.t->val.str = tmp;
        insert($$.t,$3.t);}
    | ID {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        char *tmp = $1.str;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = ID;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        $1.t->val.str = tmp;
        insert($$.t,$1.t);}
    | INT {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        int tmp = $1.i;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = INT;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        $1.t->val.i = tmp;
        insert($$.t,$1.t);}
    | FLOAT {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Exp; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        float tmp = $1.f;
        $1.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $1.t->type = FLOAT;
        $1.t->line = @1.first_line;
        $1.t->head = NULL;
        $1.t->val.f = tmp;
        insert($$.t,$1.t);}
    | Exp error Exp {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = error; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        HaveErrors=HaveErrors+1;
        printf("Error type B at line %d: Unexpected operation.\n",yylineno);
        } 
    ;
Args : Exp COMMA Args {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Args; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);
        $2.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $2.t->type = COMMA;
        $2.t->line = @2.first_line;
        $2.t->head = NULL;
        insert($$.t,$2.t);
        insert($$.t,$3.t);}
    | Exp {$$.t = (struct GrammarTree *)malloc(sizeof(struct GrammarTree));
        $$.t->type = Args; 
        $$.t->line = @$.first_line; 
        $$.t->head = NULL;
        insert($$.t,$1.t);}
    ;
%%
yyerror(char* msg){

}