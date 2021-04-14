%locations
%{
    #include<stdio.h>
    #include<stdarg.h>
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

    struct ErrorNode{
        int Linenumber;
        char ErrorType;
        char *Information;
        struct ErrorNode* next;
    };

    union TreeVal{
        int i;
        float f;
        char *str;
    };
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

    char *token_map[] = {"Program","ExtDecList","ExtDef","Specifier","FunDec","CompSt",
                         "VarDec","ExtDefList","StructSpecifier",
                         "OptTag","DefList","Tag","VarList","ParamDec",
                         "StmtList","Stmt","Exp","Def","DecList","Dec","Args","error"};
    char *token2_map[] = {"SEMI","COMMA","ASSIGNOP","PLUS",
                          "MINUS","STAR","DIV","AND","OR","NOT","DOT","TYPE","LP","RP","LB","RB" ,"LC","RC","STRUCT","RETURN",
                          "IF","ELSE","WHILE","INT","FLOAT","ID","RELOP","SUB","LOWER_THAN_ELSE"};

    struct ErrorNode *ErrorHead=NULL;
    int HaveErrors=0;
    struct GrammarTree *root=NULL;

    void print_Node(struct ErrorNode* node);
    void print_Errors();
    void insert_Error(char errorType,int linenumber,char* information);
    void insert(struct GrammarTree *t1,struct GrammarTree *t2);
    struct GrammarTree *createnode(int type,int line,void *value);
    void insertall(struct GrammarTree *parent,int num,...);
    void __DFS(struct GrammarTree *n,int depth);
    void print_tree();
%}

%union{
    union {
        struct GrammarTree * t;
        int i;
        float f;
        char *str;
    }type_treenode;
}

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
%token <type_treenode> SUB LOWER_THAN_ELSE

%type <type_treenode> Program ExtDecList ExtDef Specifier FunDec CompSt VarDec ExtDefList
%type <type_treenode> StructSpecifier OptTag DefList Tag
%type <type_treenode> VarList ParamDec
%type <type_treenode> StmtList Stmt Exp
%type <type_treenode> Def DecList Dec
%type <type_treenode> Args


%right ASSIGNOP
%left AND OR 
%left RELOP
%left PLUS SUB
%left STAR DIV
%right NOT
%left MINUS
%left LP RP LB RB DOT

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
Program : ExtDefList {
        $$.t = createnode(Program,@$.first_line,NULL);
        insertall($$.t,1,$1.t);
        root = $$.t;}
    ; 
ExtDefList : ExtDef ExtDefList {
        $$.t = createnode(ExtDefList,@$.first_line,NULL);
        insertall($$.t,2,$1.t,$2.t);}
    | {$$.t = createnode(ExtDefList,@$.first_line,NULL);}
    ;
ExtDef : Specifier ExtDecList SEMI {
        $$.t = createnode(ExtDef,@$.first_line,NULL);
        $3.t = createnode(SEMI,@3.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | Specifier SEMI {
        $$.t = createnode(ExtDef,@$.first_line,NULL);
        $2.t = createnode(SEMI,@2.first_line,NULL);
        insertall($$.t,2,$1.t,$2.t);}
    | Specifier FunDec CompSt {
        $$.t = createnode(ExtDef,@$.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);} 
    |Specifier error{
        $$.t = createnode(error,@$.first_line,NULL);
        HaveErrors++;
        char *tmp="Syntax error";
		insert_Error('B',$$.t->line,tmp);
    }
    | Specifier error SEMI
    {
        $$.t = createnode(error,@$.first_line,NULL);
        HaveErrors++;
        char *tmp="Syntax error";
		insert_Error('B',$$.t->line,tmp);
    }  
    ;
ExtDecList : VarDec {
        $$.t = createnode(ExtDecList,@$.first_line,NULL);
        insertall($$.t,1,$1.t);}
    | VarDec COMMA ExtDecList {
        $$.t = createnode(ExtDecList,@$.first_line,NULL);
        $2.t = createnode(COMMA,@2.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    ;

Specifier : TYPE {
        $$.t = createnode(Specifier,@$.first_line,NULL);
        $1.t = createnode(TYPE,@1.first_line,(void *)&$1.str);
        insertall($$.t,1,$1.t);}
    | StructSpecifier {$$.t = createnode(Specifier,@$.first_line,NULL);
        insertall($$.t,1,$1.t);}
    ;
StructSpecifier : STRUCT OptTag LC DefList RC {
        $$.t = createnode(StructSpecifier,@$.first_line,NULL);
        $1.t = createnode(STRUCT,@1.first_line,NULL);
        $3.t = createnode(LC,@3.first_line,NULL);
        $5.t = createnode(RC,@5.first_line,NULL);
        insertall($$.t,5,$1.t,$2.t,$3.t,$4.t,$5.t);}
    | STRUCT Tag { 
        $$.t = createnode(StructSpecifier,@$.first_line,NULL);
        $1.t = createnode(STRUCT,@1.first_line,NULL);
        insertall($$.t,2,$1.t,$2.t);}
    ;
OptTag : ID {
        $$.t = createnode(OptTag,@$.first_line,NULL);
        $1.t = createnode(ID,@1.first_line,(void *)&$1.str);
        insertall($$.t,1,$1.t);}
    |  {$$.t = createnode(OptTag,@$.first_line,NULL);}
    ;
Tag : ID {$$.t = createnode(Tag,@$.first_line,NULL);
        $1.t = createnode(ID,@1.first_line,(void *)&$1.str);
        insertall($$.t,1,$1.t);}

VarDec : ID {$$.t = createnode(VarDec,@$.first_line,NULL);
        $1.t = createnode(ID,@1.first_line,(void *)&$1.str);
        insertall($$.t,1,$1.t);}
    | VarDec LB INT RB {$$.t = createnode(VarDec,@$.first_line,NULL);
        $2.t = createnode(LB,@2.first_line,NULL);
        $3.t = createnode(INT,@3.first_line,(void *)&$3.i);
        $4.t = createnode(RB,@4.first_line,NULL);
        insertall($$.t,4,$1.t,$2.t,$3.t,$4.t);}
    | VarDec error RB {
        $$.t = createnode(error,@$.first_line,NULL);
        HaveErrors++;
        char *tmp="Wrong Definition";
		insert_Error('B',$$.t->line,tmp);
        //printf("Error type B at line %d:Wrong Definition.\n",$$.t->line);
        }
    ;
FunDec : ID LP VarList RP {$$.t = createnode(FunDec,@$.first_line,NULL);
        $1.t = createnode(ID,@1.first_line,(void *)&$1.str);
        $2.t = createnode(LP,@2.first_line,NULL);
        $4.t = createnode(RP,@4.first_line,NULL);
        insertall($$.t,4,$1.t,$2.t,$3.t,$4.t);}
    | ID LP RP {$$.t = createnode(FunDec,@$.first_line,NULL);
        $1.t = createnode(ID,@1.first_line,(void *)&$1.str);
        $2.t = createnode(LP,@2.first_line,NULL);
        $3.t = createnode(RP,@3.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    |ID LP error RP{
        $$.t = createnode(error,@$.first_line,NULL);
        HaveErrors=HaveErrors+1;
        char *tmp="Wrong Function Definition";
		insert_Error('B',$$.t->line,tmp);
        //printf("Error type B at line %d:Wrong Function Definition.\n",$$.t->line);
    }
    ;
VarList : ParamDec COMMA VarList {$$.t = createnode(VarList,@$.first_line,NULL);
        $2.t = createnode(COMMA,@2.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | ParamDec {$$.t = createnode(VarList,@$.first_line,NULL);
        insertall($$.t,1,$1.t);}
    ;
ParamDec : Specifier VarDec {$$.t = createnode(ParamDec,@$.first_line,NULL);
        insertall($$.t,2,$1.t,$2.t);}
    ;
CompSt : LC DefList StmtList RC {$$.t = createnode(CompSt,@$.first_line,NULL);
        $1.t = createnode(LC,@1.first_line,NULL);
        $4.t = createnode(RC,@4.first_line,NULL);
        insertall($$.t,4,$1.t,$2.t,$3.t,$4.t);}
    ;
StmtList : Stmt StmtList {$$.t = createnode(StmtList,@$.first_line,NULL);
        insertall($$.t,2,$1.t,$2.t);}
    | {$$.t = createnode(StmtList,@$.first_line,NULL);}
    ;
Stmt : Exp SEMI {$$.t = createnode(Stmt,@$.first_line,NULL);
        $2.t = createnode(SEMI,@2.first_line,NULL);
        insertall($$.t,2,$1.t,$2.t);}
    | CompSt {$$.t = createnode(Stmt,@$.first_line,NULL);
        insert($$.t,$1.t);}
    | RETURN Exp SEMI {$$.t = createnode(Stmt,@$.first_line,NULL);
        $1.t = createnode(RETURN,@1.first_line,NULL);
        $3.t = createnode(SEMI,@3.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {$$.t = createnode(Stmt,@$.first_line,NULL);
        $1.t = createnode(IF,@1.first_line,NULL);
        $2.t = createnode(LP,@2.first_line,NULL);
        $4.t = createnode(RP,@4.first_line,NULL);
        insertall($$.t,5,$1.t,$2.t,$3.t,$4.t,$5.t);}
    | IF LP Exp RP Stmt ELSE Stmt {$$.t = createnode(Stmt,@$.first_line,NULL);
        $1.t = createnode(IF,@1.first_line,NULL);
        $2.t = createnode(LP,@2.first_line,NULL);
        $4.t = createnode(RP,@4.first_line,NULL);
        $6.t = createnode(ELSE,@6.first_line,NULL);
        insertall($$.t,7,$1.t,$2.t,$3.t,$4.t,$5.t,$6.t,$7.t);}
    | WHILE LP Exp RP Stmt {$$.t = createnode(Stmt,@$.first_line,NULL);
        $1.t = createnode(WHILE,@1.first_line,NULL);
        $2.t = createnode(LP,@2.first_line,NULL);
        $4.t = createnode(RP,@4.first_line,NULL);
        insertall($$.t,5,$1.t,$2.t,$3.t,$4.t,$5.t);}
    | IF LP Exp RP error ELSE Stmt {
        $$.t = createnode(error,@$.first_line,NULL);
        HaveErrors++;
        char *tmp="Wrong statement after if(...)";
		insert_Error('B',$$.t->line,tmp);
        //printf("Error type B at line %d:Wrong statement after \'if(...)\'.\n",$$.t->line); 
    }
    | WHILE error RP Stmt {
        $$.t = createnode(error,@$.first_line,NULL);
        HaveErrors++;
        char *tmp="Unexpectd Expression";
		insert_Error('B',$$.t->line,tmp);
        //printf("Error type B at line %d:Unexpectd Expression.\n",$$.t->line);
    }
    | Exp error {
        $$.t = createnode(error,@$.first_line,NULL);
        HaveErrors++;
        char *tmp="Exexpectd \';\'";
		insert_Error('B',$$.t->line,tmp);
        //printf("Error type B at line %d:Expected \';\'.\n",$$.t->line); 
    }

    |RETURN Exp error{
        $$.t = createnode(error,@$.first_line,NULL);
        HaveErrors++;
        char *tmp="Exexpectd \';\'";
		insert_Error('B',$$.t->line,tmp);
        //printf("Error type B at line %d:Expected \';\'.\n",$$.t->line);         
    }
    ;
DefList : Def DefList {$$.t = createnode(DefList,@$.first_line,NULL);
        insertall($$.t,2,$1.t,$2.t);}
    | {$$.t = createnode(DefList,@$.first_line,NULL);}
    | error SEMI{
        $$.t = createnode(error,@$.first_line,NULL);
        HaveErrors++;
        char *tmp="Syntax error";
		insert_Error('B',$$.t->line,tmp);
        //printf("Error type B at line %d:Syntax error.\n",$$.t->line);   
    }
    ;
Def : Specifier DecList SEMI {$$.t = createnode(Def,@$.first_line,NULL);
        $3.t = createnode(SEMI,@3.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
DecList : Dec {$$.t = createnode(DecList,@$.first_line,NULL);
        insertall($$.t,1,$1.t);}
    | Dec COMMA DecList {$$.t = createnode(DecList,@$.first_line,NULL);
        $2.t = createnode(COMMA,@2.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    ;
Dec : VarDec {$$.t = createnode(Dec,@$.first_line,NULL);
        insertall($$.t,1,$1.t);}
    | VarDec ASSIGNOP Exp {$$.t = createnode(Dec,@$.first_line,NULL);
        $2.t = createnode(ASSIGNOP,@2.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    ;

Exp : Exp ASSIGNOP Exp {$$.t = createnode(Exp,@$.first_line,NULL);
        $2.t = createnode(ASSIGNOP,@2.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | Exp AND Exp {$$.t = createnode(Exp,@$.first_line,NULL);
        $2.t = createnode(AND,@2.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | Exp OR Exp {$$.t = createnode(Exp,@$.first_line,NULL);
        $2.t = createnode(OR,@2.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | Exp RELOP Exp {$$.t = createnode(Exp,@$.first_line,NULL);
        $2.t = createnode(RELOP,@2.first_line,(void *)&$2.i);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | Exp PLUS Exp {$$.t = createnode(Exp,@$.first_line,NULL);
        $2.t = createnode(PLUS,@2.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | Exp MINUS Exp %prec SUB{$$.t = createnode(Exp,@$.first_line,NULL);
        $2.t = createnode(SUB,@2.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | Exp STAR Exp {$$.t = createnode(Exp,@$.first_line,NULL);
        $2.t = createnode(STAR,@2.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | Exp DIV Exp {$$.t = createnode(Exp,@$.first_line,NULL);
        $2.t = createnode(DIV,@2.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | LP Exp RP {$$.t = createnode(Exp,@$.first_line,NULL);
        $1.t = createnode(LP,@1.first_line,NULL);
        $3.t = createnode(RP,@3.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | MINUS Exp{$$.t = createnode(Exp,@$.first_line,NULL);
        $1.t = createnode(MINUS,@1.first_line,NULL);
        insertall($$.t,2,$1.t,$2.t);}
    | NOT Exp {$$.t = createnode(Exp,@$.first_line,NULL);
        $1.t = createnode(NOT,@1.first_line,NULL);
        insertall($$.t,2,$1.t,$2.t);}
    | ID LP Args RP {$$.t = createnode(Exp,@$.first_line,NULL);
        $1.t = createnode(ID,@1.first_line,(void *)&$1.str);
        $2.t = createnode(LP,@2.first_line,NULL);
        $4.t = createnode(RP,@4.first_line,NULL);
        insertall($$.t,4,$1.t,$2.t,$3.t,$4.t);}
    | ID LP RP {$$.t = createnode(Exp,@$.first_line,NULL);
        $1.t = createnode(ID,@1.first_line,(void *)&$1.str);
        $2.t = createnode(LP,@2.first_line,NULL);
        $3.t = createnode(RP,@3.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | Exp LB Exp RB {$$.t = createnode(Exp,@$.first_line,NULL);
        $2.t = createnode(LB,@2.first_line,NULL);
        $4.t = createnode(RB,@4.first_line,NULL);
        insertall($$.t,4,$1.t,$2.t,$3.t,$4.t);}
    | Exp DOT ID {$$.t = createnode(Exp,@$.first_line,NULL);
        $2.t = createnode(DOT,@2.first_line,NULL);
        $3.t = createnode(ID,@3.first_line,(void *)&$3.str);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | ID {$$.t = createnode(Exp,@$.first_line,NULL);
        $1.t = createnode(ID,@1.first_line,(void *)&$1.str);
        insertall($$.t,1,$1.t);}
    | INT {$$.t = createnode(Exp,@$.first_line,NULL);
        $1.t = createnode(INT,@1.first_line,(void *)&$1.i);
        insertall($$.t,1,$1.t);}
    | FLOAT {$$.t = createnode(Exp,@$.first_line,NULL);
        $1.t = createnode(FLOAT,@1.first_line,(void *)&$1.f);
        insertall($$.t,1,$1.t);}
    | Exp LB error RB{
        $$.t = createnode(error,@$.first_line,NULL);
        HaveErrors++;
        char* tmp="Unexpected operation after \'[\'";
		insert_Error('B',$$.t->line,tmp);
        //printf("Error type B at line %d:Unexpected operation after \'[\'.\n",$$.t->line);    
        }
    | ID LP error RP{
        $$.t = createnode(error,@$.first_line,NULL);
        HaveErrors++;
        char *tmp="Unexpected varlist after \'(\'";
		insert_Error('B',$$.t->line,tmp);
        //printf("Error type B at line %d:Unexpected varlist after \'(\'.\n",$$.t->line); 
    }
    ;
Args : Exp COMMA Args {$$.t = createnode(Args,@$.first_line,NULL);
        $2.t = createnode(COMMA,@2.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    | Exp {$$.t = createnode(Args,@$.first_line,NULL);
        insertall($$.t,1,$1.t);}
    ;
%%

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
    if(HaveErrors==0 && root!=NULL)
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

void insertall(struct GrammarTree *parent,int num,...){
    va_list ap;
    va_start(ap,num);
    for(int i = 0;i < num;i++)
    {
        struct GrammarTree *tmp = va_arg(ap,struct GrammarTree *);
        insert(parent,tmp);
    }
    va_end(ap);
}