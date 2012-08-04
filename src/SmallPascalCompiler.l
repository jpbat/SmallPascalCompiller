%x COMMENT

%{
	#include "y.tab.h"
	#include <string.h>

	char* mystrdup(const char *s);

	extern int line;
	int comment = 0;
%}

A [aA]
B [bB]
C [cC]
D [dD]
E [eE]
F [fF]
G [gG]
H [hH]
I [iI]
J [jJ]
K [kK]
L [lL]
M [mM]
N [nN]
O [oO]
P [pP]
Q [qQ]
R [rR]
S [sS]
T [tT]
U [uU]
V [vV]
W [wW]
X [xX]
Y [yY]
Z [zZ]

%%

"(*"						{ BEGIN COMMENT; comment=1; }
<COMMENT>"*)"				{ BEGIN 0; comment=0; }
<COMMENT>\n					{ line++; }
<COMMENT>.					{ ; }

{A}{R}{R}{A}{Y}				{ return ARRAY; }
{B}{E}{G}{I}{N}				{ return BEGIN2; }
{D}{O}						{ return DO; }
{D}{O}{W}{N}{T}{O}			{ return DOWNTO; }
{E}{L}{S}{E}				{ return ELSE; }
{E}{N}{D}					{ return END; }
{F}{O}{R}					{ return FOR; } 
{F}{O}{R}{W}{A}{R}{D}		{ return FORWARD; }
{F}{U}{N}{C}{T}{I}{O}{N}	{ return FUNCTION; }
{I}{F}						{ return IF; }
{N}{O}{T}					{ return NOT; }
{O}{F}						{ return OF; }
{P}{R}{O}{G}{R}{A}{M}		{ return PROGRAM; }
{T}{H}{E}{N}				{ return THEN; }
{T}{O}						{ return TO; }
{V}{A}{R}					{ return VAR; }
{W}{H}{I}{L}{E}				{ return WHILE; }

{P}{A}{R}{A}{M}{S}{T}{R}	{ return PARAMSTR; }
{V}{A}{L}					{ return VAL; }
{W}{R}{I}{T}{E}{L}{N}		{ return WRITELN; }

{C}{A}{S}{E}				|
{C}{O}{N}{S}{T}				|
{E}{X}{T}{E}{R}{N}			|
{E}{X}{T}{E}{R}{N}{A}{L}	|
{G}{O}{T}{O}				|
{I}{N}						|
{L}{A}{B}{E}{L}				|
{N}{I}{L}					|
{O}{T}{H}{E}{R}{W}{I}{S}{E}	|
{P}{A}{C}{K}{E}{D}			|
{F}{I}{L}{E}				|
{P}{R}{O}{C}{E}{D}{U}{R}{E}	|
{R}{E}{C}{O}{R}{D}			|
{R}{E}{P}{E}{A}{T}			|
{S}{E}{T}					|
{T}{Y}{P}{E}				|
{U}{N}{T}{I}{L}				|
{W}{I}{T}{H}				{ return RESERVED; }

{A}{N}{D} 					{ yylval.op = (char*) mystrdup(yytext); return OP1A; }
{O}{R}						{ yylval.op = (char*) mystrdup(yytext); return OP1B; }

"<" 						|
">" 						|
"="							|
"<>"						|
"<="						|
">="						{ yylval.op = (char*) mystrdup(yytext); return OP2; }

"+" 						|
"-"							{ yylval.op = (char*) mystrdup(yytext); return OP3; }

"*"							|
"/"							|
{M}{O}{D}					|
{D}{I}{V}					{ yylval.op = (char*) mystrdup(yytext); return OP4; }

":="						{ return ASSIGN; }
","							{ return COMMA; }
":"							{ return COLON; }
";"							{ return SEMICOLON; }
".."						{ return DOTDOT; }
"."							{ return DOT; }

"["							{ return LBRAC; }
"("							{ return LPAREN; }
"]"							{ return RBRAC; }
")"							{ return RPAREN; }


[a-zA-Z]([a-zA-Z0-9_])*		{ yylval.id = (char*) mystrdup(yytext); return ID; }
[0-9]+						{ yylval.integer = atoi(yytext); return DIGSEQ; } 
[0-9]+"."[0-9]+				{ yylval.real = atof(yytext); return REALNUMBER; }

[ \t]						{ ; }
\n							{ line++; }
.							{ printf("Line %d: illegal character ('%c')\n", line, yytext[0]); }

%%

char* mystrdup(const char *s) {
	char *d = malloc (strlen (s) + 1);
	if (d != NULL)
		strcpy (d,s);
	return d;
}

int yywrap()
{
	if (comment)
		printf("Line %d: unexpected EOF inside comment\n", line);
	return 1;
}

