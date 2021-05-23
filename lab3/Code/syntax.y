%locations
%{
    #include<stdio.h>
    #include<stdarg.h>
    #include"lex.yy.c"
    #include"GrammarTree.h"
    #include"Error.h"
    extern int yyerror();
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
%token <type_treenode> SUB UMINUS LOWER_THAN_ELSE

%type <type_treenode> Program ExtDecList ExtDef Specifier FunDec CompSt VarDec ExtDefList
%type <type_treenode> StructSpecifier OptTag DefList Tag
%type <type_treenode> VarList ParamDec
%type <type_treenode> StmtList Stmt Exp
%type <type_treenode> Def DecList Dec
%type <type_treenode> Args

%right ASSIGNOP
%left AND OR 
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left UMINUS
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
    | Specifier FunDec SEMI {
        $$.t = createnode(ExtDef,@$.first_line,NULL);
        $3.t = createnode(SEMI,@3.first_line,NULL);
        insertall($$.t,3,$1.t,$2.t,$3.t);}
    |Specifier error{
        $$.t = createnode(error,@$.first_line,NULL);
        char *tmp="Syntax error";
		insert_Error("B",$$.t->line,tmp);
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
    | VarDec error RB {$$.t = createnode(VarDec,@$.first_line,NULL);
        $$.t = createnode(error,@$.first_line,NULL);
        char *tmp="Wrong Definition";
		insert_Error("B",$$.t->line,tmp);
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
        char *tmp="Wrong Function Definition";
		insert_Error("B",$$.t->line,tmp);
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
        char *tmp="Wrong statement after if(...)";
		insert_Error("B",$$.t->line,tmp);
        //printf("Error type B at line %d:Wrong statement after \'if(...)\'.\n",$$.t->line); 
    }
    | WHILE error RP Stmt {
        $$.t = createnode(error,@$.first_line,NULL);
        char *tmp="Unexpectd Expression";
		insert_Error("B",$$.t->line,tmp);
        //printf("Error type B at line %d:Unexpectd Expression.\n",$$.t->line);
    }
    | Exp error {
        $$.t = createnode(error,@$.first_line,NULL);
        char *tmp="Exexpectd \';\'";
		insert_Error("B",$$.t->line,tmp);
        //printf("Error type B at line %d:Expected \';\'.\n",$$.t->line); 
    }

    |RETURN Exp error{
        $$.t = createnode(error,@$.first_line,NULL);
        char *tmp="Exexpectd \';\'";
		insert_Error("B",$$.t->line,tmp);
        //printf("Error type B at line %d:Expected \';\'.\n",$$.t->line);         
    }
    ;
DefList : Def DefList {$$.t = createnode(DefList,@$.first_line,NULL);
        insertall($$.t,2,$1.t,$2.t);}
    | {$$.t = createnode(DefList,@$.first_line,NULL);}
    | error SEMI{
        $$.t = createnode(error,@$.first_line,NULL);
        char *tmp="Syntax error";
		insert_Error("B",$$.t->line,tmp);
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
    | Exp MINUS Exp{$$.t = createnode(Exp,@$.first_line,NULL);
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
    | MINUS Exp %prec UMINUS{$$.t = createnode(Exp,@$.first_line,NULL);
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
        char* tmp="Unexpected operation after \'[\'";
		insert_Error("B",$$.t->line,tmp);
        //printf("Error type B at line %d:Unexpected operation after \'[\'.\n",$$.t->line);    
        }
    | ID LP error RP{
        $$.t = createnode(error,@$.first_line,NULL);
        char *tmp="Unexpected varlist after \'(\'";
		insert_Error("B",$$.t->line,tmp);
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
