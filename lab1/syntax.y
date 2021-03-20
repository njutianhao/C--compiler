%{
    #include<stdio.h>
    int yycolumn = 1;
    #define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;
%}

%union{
    int type_int;
    float type_float;
    double type_double;
}

%token MULTI_LINE_NOTES_BEGIN MULTI_LINE_NOTES_END
%token SEMI COMMA
%token ASSIGNOP RELOP 
%token PLUS MINUS STAR DIV
%token AND OR NOT
%token DOT
%token TYPE
%token LP RP LB RB LC RC 
%token STRUCT
%token RETURN
%token IF ELSE WHILE 
%token <type_int> INT
%token <type_float> FLOAT 
%token ID

%right ASSIGNOP
%left AND OR 
%left L LE G GE EQ NEQ /*TODO:differ RELOP */
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
