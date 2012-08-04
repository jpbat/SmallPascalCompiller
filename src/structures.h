#ifndef _STRUCTURES_
#define _STRUCTURES_

#include <stdbool.h>

typedef char *is_ID, *is_OP1, *is_OP2, *is_OP3, *is_OP4;
typedef int is_DIGSEQ;
typedef double is_REALNUMBER;

/* start */
typedef struct _is_start {
	is_ID id;
	struct _is_block *block;
} is_start;


/* block */
typedef struct _is_block {
	struct _is_varDeclaration_list *varDeclarationList; /* nullable */
	struct _is_functionDecOrDef_list *functionDecOrDefList; /* nullable */
	struct _is_statement_list *statementList;
} is_block;


/* functionDecOrDefList */
typedef enum {d_functionDec, d_functionDef} disc_functionDecOrDef_list;

typedef struct _is_functionDecOrDef_list {
	disc_functionDecOrDef_list disc_d;
	
	union {
		struct _is_functionDeclaration *functionDeclaration;
		struct _is_functionDefinition *functionDefinition;
	} data_functionDecOrDef_list;
	
	struct _is_functionDecOrDef_list *next;
} is_functionDecOrDef_list;


/* variableDeclarationList */
typedef struct _is_varDeclaration_list {
	struct _is_varDeclaration *varDeclaration;
	struct _is_varDeclaration_list *next;
} is_varDeclaration_list;


/* variableDeclaration */
typedef enum {d_with, d_without} disc_varDeclaration;

typedef struct _is_varDeclaration {
	disc_varDeclaration disc_d;
	
	struct _is_id_list *idList;
	is_DIGSEQ digseq1;
	is_DIGSEQ digseq2;
	is_ID id;
} is_varDeclaration;


/* idList */
typedef struct _is_id_list {
	is_ID id;
	struct _is_id_list *next;
} is_id_list;


/* functionDeclaration */
typedef struct _is_functionDeclaration {
	struct _is_functionHeading *functionHeading;
} is_functionDeclaration;


/* functionDefinition */
typedef struct _is_functionDefinition {
	struct _is_functionHeading *functionHeading;
	struct _is_functionBlock *functionBlock;	
} is_functionDefinition;


/* functionHeading */
typedef struct _is_functionHeading {
	is_ID id1;
	struct _is_formalArgs_list *formalArgsList; /* nullable */
	is_ID id2;
} is_functionHeading;


/* formalArgsList */
typedef struct _is_formalArgs_list {
	struct _is_formalArgs *formalArgs;
	struct _is_formalArgs_list *next;	
} is_formalArgs_list;


/* formalArgs */
typedef struct _is_formalArgs {
	bool var, arrayOf;
	struct _is_id_list *idList;
	is_ID id;
} is_formalArgs;


/* functionBlock */
typedef struct _is_functionBlock {
	struct _is_varDeclaration_list *varDeclarationList; /* nullable */
	struct _is_statement_list *statementList;
} is_functionBlock;


/* statementList */
typedef struct _is_statement_list {
	struct _is_statement *statement; /* nullable */
	struct _is_statement_list *next;
} is_statement_list;


/* statement */
typedef enum {d_beginEnd, d_assignExp, d_ifThen, d_whileDo, d_for, d_valParamstr, d_writeln} disc_statement;

typedef struct _is_statement {
	disc_statement disc_d;
	union {
		struct _is_beginEnd *beginEnd;
		struct _is_assignExp *assignExp;
		struct _is_ifThen *ifThen;
		struct _is_whileDo *whileDo;
		struct _is_for *for2;
		struct _is_valParamstr *valParamstr;
		struct _is_writeln *writeln;
	} data_statement;
} is_statement;

typedef struct _is_beginEnd {
	struct _is_statement_list *statementList;
} is_beginEnd;

typedef struct _is_assignExp {
	is_ID id;
	struct _is_expression *expression1; /* nullable */
	struct _is_expression *expression2;
} is_assignExp;

typedef struct _is_ifThen {
	bool iselse;
	struct _is_expression *expression;
	struct _is_statement *ifStatement; /* nullable */
	struct _is_statement *elseStatement; /* nullable */
} is_ifThen;

typedef struct _is_whileDo {
	struct _is_expression *expression;
	struct _is_statement *statement; /* nullable */
} is_whileDo;
	
typedef enum {d_to, d_downto} disc_for;

typedef struct _is_for {
	disc_for disc_d;
	
	is_ID id;
	struct _is_expression *expression1;
	struct _is_expression *expression2;
	struct _is_statement *statement; /* nullable */
} is_for;

typedef struct _is_valParamstr {
	struct _is_expression *expression;
	is_ID id;
} is_valParamstr;

typedef struct _is_writeln {
	struct _is_expression *expression;
} is_writeln;


/* expression */
typedef enum {d_operators, d_numberExp, d_arrayExp, d_notExp, d_funcExp} disc_expression;

typedef struct _is_expression {
	disc_expression disc_d;
	union {
		struct _is_operators *operators;
		struct _is_arrayExp *arrayExp;
		struct _is_numberExp *numberExp;
		struct _is_notExp *notExp;
		struct _is_funcExp *funcExp;
	} data_expression;
} is_expression;

typedef enum {d_op1, d_op2, d_op3, d_op4} disc_operators;

typedef struct _is_operators {
	disc_operators disc_d;
	union {
		is_OP1 op1;
		is_OP2 op2;
		is_OP3 op3;
		is_OP4 op4;
	} data_operators;
	struct _is_expression *expression1; /* nullable */
	struct _is_expression *expression2;
} is_operators;

typedef enum {d_digseq, d_realnumber} disc_numberExp; 

typedef struct _is_numberExp {
	disc_numberExp disc_d;
	union {
		is_DIGSEQ digseq;
		is_REALNUMBER realnumber;
	} data_numberExp;
} is_numberExp;

typedef struct _is_arrayExp {
	is_ID id;
	struct _is_expression *expression; /* nullable */
} is_arrayExp;

typedef struct _is_notExp {
	struct _is_expression *expression;
} is_notExp;

typedef struct _is_funcExp {
	is_ID id;
	struct _is_expression_list *expressionList; /* nullable */
} is_funcExp;

typedef struct _is_expression_list {
	struct _is_expression *expression;
	struct _is_expression_list *next;
} is_expression_list;

#endif
