%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#include "structures.h"
	#include "functions.h"

	#include "symbol_table.h"
	#include "semantic.h"

	#include "translate.h"
	
	int line;
	char *yytext;

	is_start *tree_root = NULL;
%}

%token<id>			ID
%token<op>			OP1A OP1B OP2 OP3 OP4
%token<integer>		DIGSEQ
%token<real>		REALNUMBER

%token ARRAY
%token ASSIGN
%token BEGIN2
%token COLON
%token COMMA
%token DO
%token DOT
%token DOTDOT
%token DOWNTO
%token ELSE
%token END
%token FOR
%token FORWARD
%token FUNCTION
%token IF
%token LBRAC
%token LPAREN
%token NOT
%token OF
%token PARAMSTR
%token PROGRAM
%token RBRAC
%token RPAREN
%token SEMICOLON
%token THEN
%token TO
%token VAL
%token VAR
%token WHILE
%token WRITELN
%token RESERVED

%nonassoc OP2
%left OP3 OP1B
%left OP4 OP1A
%right NOT
%right IF THEN ELSE
%left LPAREN

%union {
	char *id;
	char *op;
	int integer;
	double real;

	struct _is_start					*start_;
	struct _is_block					*block_;
	struct _is_functionDecOrDef_list	*functionDecOrDefList_;
	struct _is_functionDeclaration		*functionDeclaration_;
	struct _is_functionDefinition		*functionDefinition_;
	struct _is_varDeclaration_list		*varDeclarationList_;
	struct _is_varDeclaration			*varDeclaration_;
	struct _is_id_list				*idList_;
	struct _is_functionHeading		*functionHeading_;
	struct _is_formalArgs_list		*formalArgsList_;
	struct _is_formalArgs			*formalArgs_;
	struct _is_functionBlock		*functionBlock_;
	struct _is_statement_list		*statementList_;
	struct _is_statement		*statement_;
	struct _is_expression		*expression_;
	struct _is_expression_list	*expressionList_;
}

%start start

%type<start_> start
%type<block_> block
%type<functionDecOrDefList_> functionDecOrDefList
%type<functionDeclaration_> functionDeclaration
%type<functionDefinition_> functionDefinition
%type<varDeclarationList_> variableDeclarationList
%type<varDeclaration_> variableDeclaration
%type<idList_> idList
%type<functionHeading_> functionHeading
%type<formalArgsList_> formalArgsList
%type<formalArgs_> formalArgs
%type<functionBlock_> functionBlock
%type<statementList_> statementList
%type<statement_> statement
%type<expression_> expression
%type<expressionList_> expressionList

%%

start: 	PROGRAM ID SEMICOLON block DOT { $$ = tree_root = insert_start($2, $4);}
	;

block: 	VAR variableDeclarationList functionDecOrDefList BEGIN2 statementList END { $$ = insert_block($2, $3, $5); }
	|	functionDecOrDefList BEGIN2 statementList END { $$ = insert_block(NULL, $1, $3); }
	;

variableDeclarationList:	variableDeclaration { $$ = insert_varDeclaration_list(NULL, $1); }
						| 	variableDeclarationList variableDeclaration { $$ = insert_varDeclaration_list($1, $2); }
						;

variableDeclaration:	idList COLON ARRAY LBRAC DIGSEQ DOTDOT DIGSEQ RBRAC OF ID SEMICOLON { $$ = insert_varDeclaration_with($1, $5, $7, $10); }
					|	idList COLON ID SEMICOLON { $$ = insert_varDeclaration_without($1, $3); }
					;

idList: ID				{ $$ = insert_id_list(NULL, $1); }
	|	idList COMMA ID { $$ = insert_id_list($1, $3); }
	;

functionDecOrDefList:	functionDecOrDefList functionDeclaration { $$ = insert_functionDecOrDef_Dec_list($1, $2); }
					|	functionDecOrDefList functionDefinition { $$ = insert_functionDecOrDef_Def_list($1, $2); }
					|	{ $$ = NULL; }
					;

functionDeclaration: functionHeading SEMICOLON FORWARD SEMICOLON { $$ = insert_functionDeclaration($1); }
					;

functionDefinition: functionHeading SEMICOLON functionBlock SEMICOLON { $$ = insert_functionDefinition($1, $3); }
					;

functionHeading:	FUNCTION ID LPAREN formalArgsList RPAREN COLON ID { $$ = insert_functionHeading($2, $4, $7); }
				|	FUNCTION ID LPAREN RPAREN COLON ID { $$ = insert_functionHeading($2, NULL, $6); }
				;

formalArgsList:	formalArgs { $$ = insert_formalArgs_list(NULL, $1); }
			|	formalArgsList SEMICOLON formalArgs { $$ = insert_formalArgs_list($1, $3); }
			;

formalArgs: VAR idList COLON ARRAY OF ID 	{ $$ = insert_formalArgs($2, $6, true, true); }
		|	VAR idList COLON ID				{ $$ = insert_formalArgs($2, $4, true, false); }
		|	idList COLON ARRAY OF ID		{ $$ = insert_formalArgs($1, $5, false, true); }
		|	idList COLON ID					{ $$ = insert_formalArgs($1, $3, false, false); }
		;

functionBlock: 	VAR variableDeclarationList BEGIN2 statementList END { $$ = insert_functionBlock($2, $4); }
			|	BEGIN2 statementList END { $$ = insert_functionBlock(NULL, $2); }
			;

statementList: 	statement { if ($1) $$ = insert_statement_list(NULL, $1); else $$ = NULL; }
			|	statementList SEMICOLON statement { if ($1) $$ = insert_statement_list($1, $3); else $$ = NULL; }
			;

statement:	BEGIN2 statementList END { if ($2 != NULL) $$ = insert_statement_beginEnd(insert_beginEnd($2)); else $$ = NULL; }
		|	ID LBRAC expression RBRAC ASSIGN expression { $$ = insert_statement_assignExp(insert_assignExp($1, $3, $6)); }
		|	ID ASSIGN expression { $$ = insert_statement_assignExp(insert_assignExp($1, NULL, $3)); }
		|	IF expression THEN statement ELSE statement { $$ = insert_statement_ifThen(insert_ifThen($2, $4, $6, true)); }
		|	IF expression THEN statement { $$ = insert_statement_ifThen(insert_ifThen($2, $4, NULL, false)); }
		|	WHILE expression DO statement { $$ = insert_statement_whileDo(insert_whileDo($2, $4)); }
		|	FOR ID ASSIGN expression TO expression DO statement { $$ = insert_statement_for(insert_for_to($2, $4, $6, $8)); }
		|	FOR ID ASSIGN expression DOWNTO expression DO statement { $$ = insert_statement_for(insert_for_downto($2, $4, $6, $8)); }
		|	VAL LPAREN PARAMSTR LPAREN expression RPAREN COMMA ID RPAREN { $$ = insert_statement_valParamstr(insert_valParamstr($5, $8));}
		|	WRITELN LPAREN expression RPAREN { $$ = insert_statement_writeln(insert_writeln($3)); }
		|	{ $$ = NULL; }
		;

expression: expression OP1A expression	{ $$ = insert_expression_operators(insert_operators_op1($2, $1, $3)); }
		|	expression OP1B expression	{ $$ = insert_expression_operators(insert_operators_op1($2, $1, $3)); }
		|	expression OP2 expression	{ $$ = insert_expression_operators(insert_operators_op2($2, $1, $3)); }
		|	expression OP3 expression	{ $$ = insert_expression_operators(insert_operators_op3($2, $1, $3)); }
		|	expression OP4 expression	{ $$ = insert_expression_operators(insert_operators_op4($2, $1, $3)); }
		|	OP3 expression				{ $$ = insert_expression_operators(insert_operators_op3($1, NULL, $2)); }
		|	LPAREN expression RPAREN	{ $$ = $2; }
		|	DIGSEQ						{ $$ = insert_expression_numberExp(insert_numberExp_digseq($1)); }
		|	REALNUMBER					{ $$ = insert_expression_numberExp(insert_numberExp_realnumber($1)); }
		|	ID LBRAC expression RBRAC	{ $$ = insert_expression_arrayExp(insert_arrayExp($1, $3)); }
		|	ID							{ $$ = insert_expression_arrayExp(insert_arrayExp($1, NULL)); }
		|	NOT expression				{ $$ = insert_expression_notExp(insert_notExp($2)); }
		|	ID LPAREN expressionList RPAREN	{ $$ = insert_expression_funcExp(insert_funcExp($1, $3)); }
		|	ID LPAREN RPAREN			{ $$ = insert_expression_funcExp(insert_funcExp($1, NULL)); }
		;

expressionList:	expression { $$ = insert_expression_list(NULL, $1); }
			|	expressionList COMMA expression { $$ = insert_expression_list($1, $3); }
			;

%%

int yyerror(char *s) {
	printf("Line %d: %s: %s\n", line, s, yytext);
}


int main(int argc, char** argv) {	
	line = 1;

	if (yyparse() != 0)
		return 0;

	if (tree_root)
		check_start(tree_root);

	if (tree_root)
		translate_start(tree_root);

	return 0;
}

