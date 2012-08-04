#ifndef _FUNCTIONS_
#define _FUNCTIONS_

is_start *insert_start(is_ID id, is_block *block);
is_block *insert_block(is_varDeclaration_list *vdl, is_functionDecOrDef_list *fdodl, is_statement_list *sl);
is_functionDecOrDef_list *insert_functionDecOrDef_Dec_list(is_functionDecOrDef_list *list, is_functionDeclaration *fd);
is_functionDecOrDef_list *insert_functionDecOrDef_Def_list(is_functionDecOrDef_list *list, is_functionDefinition *fd);
is_varDeclaration_list *insert_varDeclaration_list(is_varDeclaration_list *list, is_varDeclaration *vd);
is_varDeclaration *insert_varDeclaration_with(is_id_list *il, is_DIGSEQ d1, is_DIGSEQ d2, is_ID id);
is_varDeclaration *insert_varDeclaration_without(is_id_list *il, is_ID id);
is_id_list *insert_id_list(is_id_list *list, is_ID id);
is_functionDeclaration *insert_functionDeclaration(is_functionHeading *fh);
is_functionDefinition *insert_functionDefinition(is_functionHeading *fh, is_functionBlock *fb);
is_functionHeading *insert_functionHeading(is_ID id1, is_formalArgs_list *fal, is_ID id2);
is_formalArgs_list *insert_formalArgs_list(is_formalArgs_list *list, is_formalArgs *fa);
is_formalArgs *insert_formalArgs(is_id_list *idl, is_ID id, bool var, bool arrayOf);
is_functionBlock *insert_functionBlock(is_varDeclaration_list *vdl, is_statement_list *sl);
is_statement_list *insert_statement_list(is_statement_list *list, is_statement *s);
is_statement *insert_statement_beginEnd(is_beginEnd *be);
is_statement *insert_statement_assignExp(is_assignExp *ae);
is_statement *insert_statement_ifThen(is_ifThen *it);
is_statement *insert_statement_whileDo(is_whileDo *wd);
is_statement *insert_statement_for(is_for *f);
is_statement *insert_statement_valParamstr(is_valParamstr *vp);
is_statement *insert_statement_writeln(is_writeln *w);
is_beginEnd *insert_beginEnd(is_statement_list *sl);
is_assignExp *insert_assignExp(is_ID id, is_expression *e1, is_expression *e2);
is_ifThen *insert_ifThen(is_expression *e, is_statement *is, is_statement *es, bool iselse);
is_whileDo *insert_whileDo(is_expression *e, is_statement *s);
is_for *insert_for_to(is_ID id, is_expression *e1, is_expression *e2, is_statement *s);
is_for *insert_for_downto(is_ID id, is_expression *e1, is_expression *e2, is_statement *s);
is_valParamstr *insert_valParamstr(is_expression *e, is_ID id);
is_writeln *insert_writeln(is_expression *e);
is_expression *insert_expression_operators(is_operators *op);
is_expression *insert_expression_arrayExp(is_arrayExp *ae);
is_expression *insert_expression_numberExp(is_numberExp *ne);
is_expression *insert_expression_notExp(is_notExp *ne);
is_expression *insert_expression_funcExp(is_funcExp *fe);
is_operators *insert_operators_op1(is_OP1 op1, is_expression *e1, is_expression *e2);
is_operators *insert_operators_op2(is_OP2 op2, is_expression *e1, is_expression *e2);
is_operators *insert_operators_op3(is_OP3 op3, is_expression *e1, is_expression *e2);
is_operators *insert_operators_op4(is_OP4 op4, is_expression *e1, is_expression *e2);
is_numberExp *insert_numberExp_digseq(is_DIGSEQ digseq);
is_numberExp *insert_numberExp_realnumber(is_REALNUMBER realnumber);
is_arrayExp *insert_arrayExp(is_ID id, is_expression *e);
is_notExp *insert_notExp(is_expression *e);
is_funcExp *insert_funcExp(is_ID id, is_expression_list *el);
is_expression_list *insert_expression_list(is_expression_list *list, is_expression *e);

#endif
