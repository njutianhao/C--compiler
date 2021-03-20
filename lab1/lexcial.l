%{
	#include"syntax.tab.h"
	/*necessary include*/
%}
letter [a-zA-Z]
digit [0-9]
%option yylineno
%%
"//" {  
	char c=input();
	while(c!='\n') c=input();       
     }
"/*" { return MULTI_LINE_NOTES_BEGIN; }
"*/" { return MULTI_LINE_NOTES_END; }
\n { yycolumn = 1; }
[\t\r] { }
";" { return SEMI; }
"," {  return COMMA; }
"=" { return ASSIGNOP; }
">"|"<"|">="|"<="|"=="|"!=" { return RELOP; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return STAR; }
"/" { return DIV; }
"&&" { return AND; }
"||" { return OR; }
"." { return DOT; }
"!" { return NOT; }
(int)|(float) { return TYPE; }
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
([1-9]{digit}*)|(0) { return INT; }
((([1-9]{digit}*)|(0))(\.)({digit}+)) { return FLOAT; }
({letter}|(_))({letter}|{digit}|_)* { return ID; }
. { printf("Error type A at line %d:Mysterious characters \'%s\'\n",yylineno,yytext); }
%%


