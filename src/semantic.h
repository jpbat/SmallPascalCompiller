#ifndef _SEMANTIC_
#define _SEMANTIC_

#include "symbol_table.h"

int global_offset;
int function_offset;
table_element *statTable;
prog_env *pe;

typedef enum {localScope, globalScope} scope;

void show_table();
char *toLower(char *str);
const char *typeToString(basic_type type);
basic_type check_op1(is_OP1 op1, is_expression *e1, is_expression *e2);
basic_type check_op2(is_OP2 op2, is_expression *e1, is_expression *e2);
basic_type check_op3(is_OP3 op3, is_expression *e1, is_expression *e2);
basic_type check_op4(is_OP4 op4, is_expression *e1, is_expression *e2);
void check_start(is_start *s);
void check_block(is_block *b);
void check_functionDecOrDef_list(is_functionDecOrDef_list *fdodl);
void check_varDeclaration_list(is_varDeclaration_list *vdl, scope s, table_element *table);
void check_varDeclaration(is_varDeclaration *vd, scope s, table_element *table);
void check_id_list(is_id_list *idl);
void check_functionDeclaration(is_functionDeclaration *fd);
void check_functionDefinition(is_functionDefinition *fd);
void check_functionHeading(is_functionHeading *fh, char defined);
void check_functionArgs(is_functionHeading *fh, environment_list *el);
void check_formalArgs_list(is_formalArgs_list *fal, table_element *table);
void check_formalArgs(is_formalArgs *fa, table_element *table);
void check_functionBlock(is_functionBlock *fb, table_element *table);
void check_statement_list(is_statement_list *sl);
void check_statement(is_statement *s);
void check_beginEnd(is_beginEnd *be);
void check_assignExp(is_assignExp *ae);
void check_ifThen(is_ifThen *ae);
void check_whileDo(is_whileDo *wd);
void check_for(is_for *f);
void check_valParamstr(is_valParamstr *vp);
void check_writeln(is_writeln *w);
basic_type check_expression(is_expression *e);
basic_type check_operators(is_operators *op);
basic_type check_numberExp(is_numberExp *ne);
basic_type check_arrayExp(is_arrayExp *ae);
basic_type check_notExp(is_notExp *ne);
basic_type check_funcExp(is_funcExp *fe);
void check_expression_list(is_expression_list *elist, environment_list *el);

table_element *create_symbol(int offset, char *name, basic_type type, char param);
table_element *lookup(table_element *table, char *str);
environment_list *lookupFunction(char *str);

#endif
