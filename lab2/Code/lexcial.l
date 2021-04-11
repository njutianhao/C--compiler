%{
	#include"syntax.tab.h"
	#include<string.h>
	#include"Error.h"
	#define L 1
	#define LE 2
	#define G 3
	#define GE 4
	#define EQ 5
	#define NEQ 6
    int yycolumn = 1;
    #define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;
%}
letter [a-zA-Z]
digit [0-9]
%option yylineno
%%
"//" {  
	char c=input();
	while(c!='\n') c=input(); 
	yycolumn=1;      
     }
"/*" {
	int lineno= yylineno;
	char c=input();
	char perc=c;
	while(perc!='*' || c!='/'){
		if(c==EOF){
			insert_Error("B",lineno,"Ambiguous characters /*");
			HaveErrors++;
			break;
		}
		if(c=='\n') yycolumn=1;
		perc=c;
		c=input();
	}
     }
\n { yycolumn = 1; }
[\t\r ] { }
";" { return SEMI; }
"," {  return COMMA; }
">=" {
	yylval.type_treenode.i = GE;
	return RELOP;
}
"<=" {
	yylval.type_treenode.i = LE;
	return RELOP;
}
"==" {
	yylval.type_treenode.i = EQ;
	return RELOP;
}
"!=" {
	yylval.type_treenode.i = NEQ;
	return RELOP;
}
">" {
	yylval.type_treenode.i = G;
	return RELOP;
}
"<" {
	yylval.type_treenode.i = L;
	return RELOP;
}
"=" { return ASSIGNOP; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return STAR; }
"/" { return DIV; }
"&&" { return AND; }
"||" { return OR; }
"." { return DOT; }
"!" { return NOT; }
(int)|(float) { 
	yylval.type_treenode.str=(char *)malloc(yyleng*sizeof(char)); 
	for(int i=0;i<yyleng;i++)
		yylval.type_treenode.str[i]=yytext[i];
	return TYPE; 
 }
"(" { return LP; }
")" { return RP; }
"[" { return LB; }
"]" { return RB; }
"{" { return LC; }
"}" { return RC; }
(struct) { return STRUCT; }
(return) { return RETURN; }
(if) { return IF; }
(else) { return ELSE; }
(while) { return WHILE; }
([1-9]{digit}*)|(0) { yylval.type_treenode.i=atoi(yytext); return INT; }
((([1-9]{digit}*)|(0))(\.)({digit}+)) { yylval.type_treenode.f=atof(yytext); return FLOAT; }
({letter}|(_))({letter}|{digit}|_)* {
	yylval.type_treenode.str=(char *)malloc(yyleng*sizeof(char)); 
	for(int i=0;i<yyleng;i++)
		yylval.type_treenode.str[i]=yytext[i];
	return ID;
 }
. { printf("Error type A at line %d:Mysterious characters \'%s\'.\n",yylineno,yytext);
	HaveErrors++;}
%%


