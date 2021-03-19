%{
	/*   */
%}
letter [a-zA-Z]
digit [0-9]
%option yylineno
%%
\/\/[^\n]* { printf("SINGLE-LINE NOTES\n"); }
"/*" { printf("MULTI-LINE NOTES BEGIN\n"); }
"*/" { printf("MULTI-LINE NOTES END\n"); }
[\t\r\n ] { }
";" { printf("SEMI\n"); }
"," { printf("COMMA\n"); }
"=" { printf("ASSIGNOP\n"); }
">"|"<"|">="|"<="|"=="|"!=" { printf("RELOP\n"); }
"+" { printf("PLUS\n"); }
"-" { printf("MINUS\n"); }
"*" { printf("STAR\n"); }
"/" { printf("DIV\n"); }
"&&" { printf("AND\n"); }
"||" { printf("OR\n"); }
"." { printf("DOT\n"); }
"!" { printf("NOT\n"); }
(int)|(float) { printf("TYPE\n"); }
"(" { printf("LP\n"); }
")" { printf("RP\n"); }
"[" { printf("LB\n"); }
"]" { printf("RB\n"); }
"{" { printf("LC\n"); }
"}" { printf("RC\n"); }
(struct) { printf("STRUCT\n"); }
(return) { printf("RETURN\n"); }
(if) { printf("IF\n"); }
(else) { printf("ELSE\n"); }
(while) { printf("WHILE\n"); }
([1-9]{digit}*)|(0) { printf("INT\n"); }
((([1-9]{digit}*)|(0))(\.)({digit}+)) { printf("FLOAT\n"); }
({letter}|(_))({letter}|{digit}|_)* { printf("ID\n"); }
. { printf("Error type A at line %d:Mysterious characters \'%s\'\n",yylineno,yytext); }
%%
int main(int argc,char** argv){
	if (argc>1){
		if(!(yyin=fopen(argv[1],"r"))){
			perror(argv[1]);
			return 1;
		}
	}
	while(yylex()!=0);
	return 0;
}

