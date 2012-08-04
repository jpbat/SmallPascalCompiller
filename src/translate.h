#ifndef _TRANSLATE_
#define _TRANSLATE_

void st(char *str);
basic_type translate_op1(is_OP1 op1, is_expression *e1, is_expression *e2);
basic_type translate_op2(is_OP2 op2, is_expression *e1, is_expression *e2);
basic_type translate_op3(is_OP3 op3, is_expression *e1, is_expression *e2);
basic_type translate_op4(is_OP4 op4, is_expression *e1, is_expression *e2);
void translate_start(is_start *s);
void translate_block(is_block *b);
void translate_globalVarDeclaration_list(is_varDeclaration_list *vdl);
void translate_globalVarDeclaration(is_varDeclaration *vd);
void translate_varDeclaration_list(is_varDeclaration_list *vdl, table_element *table);
void translate_varDeclaration(is_varDeclaration *vd, table_element *table);
void translate_functionDecOrDef_list(is_functionDecOrDef_list *fdodl);
void translate_functionDefinition(is_functionDefinition *fd);
void translate_functionArgs(is_functionHeading *fh, environment_list *el);
void translate_functionHeading(is_functionHeading *fh);
void translate_formalArgs_list(is_formalArgs_list *fal, table_element *table);
void translate_formalArgs(is_formalArgs *fa, table_element *table);
void translate_functionBlock(is_functionBlock *fb, table_element *table);
void translate_statement_list(is_statement_list *sl);
void translate_statement(is_statement *s);
void translate_beginEnd(is_beginEnd *be);
void translate_assignExp(is_assignExp *ae);
void translate_ifThen(is_ifThen *ae);
void translate_whileDo(is_whileDo *wd);
void translate_for(is_for *f);
void translate_valParamstr(is_valParamstr *vp);
void translate_writeln(is_writeln *w);
basic_type translate_expression(is_expression *e);
basic_type translate_operators(is_operators *op);
basic_type translate_numberExp(is_numberExp *ne);
basic_type translate_arrayExp(is_arrayExp *ae);
basic_type translate_notExp(is_notExp *ne);
basic_type translate_funcExp(is_funcExp *fe);
void translate_expression_list(is_expression_list *elist, environment_list *el);

#endif
