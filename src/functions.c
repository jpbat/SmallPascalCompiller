#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

/* start */
is_start *insert_start(is_ID id, is_block *block) {
	
	is_start *is = (is_start *) malloc(sizeof(is_start));
	is->id = id;
	is->block = block;
	
	return is;
}

/* block */
is_block *insert_block(is_varDeclaration_list *vdl, is_functionDecOrDef_list *fdodl, is_statement_list *sl) {
	
	is_block *ib = (is_block *) malloc(sizeof(is_block));
	ib->varDeclarationList = vdl;
	ib->functionDecOrDefList = fdodl;
	ib->statementList = sl;
	
	return ib;
}

/* functionDecOrDefList */
is_functionDecOrDef_list *insert_functionDecOrDef_Dec_list(is_functionDecOrDef_list *list, is_functionDeclaration *fd) {
	
	is_functionDecOrDef_list* fdodl = (is_functionDecOrDef_list *) malloc(sizeof(is_functionDecOrDef_list));
	fdodl->disc_d = d_functionDec;
	fdodl->data_functionDecOrDef_list.functionDeclaration = fd;
		
	if (list == NULL)
		return fdodl;
		
	is_functionDecOrDef_list *aux;
			
	for (aux=list; aux->next != NULL; aux=aux->next);
	aux->next = fdodl;
	
	return list;
}

is_functionDecOrDef_list *insert_functionDecOrDef_Def_list(is_functionDecOrDef_list *list, is_functionDefinition *fd) {
	
	is_functionDecOrDef_list* fdodl = (is_functionDecOrDef_list *) malloc(sizeof(is_functionDecOrDef_list));
	fdodl->disc_d = d_functionDef;
	fdodl->data_functionDecOrDef_list.functionDefinition = fd;
		
	if (list == NULL)
		return fdodl;
		
	is_functionDecOrDef_list *aux;
			
	for (aux=list; aux->next != NULL; aux=aux->next);
	aux->next = fdodl;
	
	return list;
}

/* variableDeclarationList */
is_varDeclaration_list *insert_varDeclaration_list(is_varDeclaration_list *list, is_varDeclaration *vd) {
	
	is_varDeclaration_list* ivdl = (is_varDeclaration_list *) malloc(sizeof(is_varDeclaration_list));
	ivdl->varDeclaration = vd;
		
	if (list == NULL)
		return ivdl;
		
	is_varDeclaration_list *aux;
			
	for (aux=list; aux->next != NULL; aux=aux->next);
	aux->next = ivdl;
	
	return list;
}

/* variableDeclaration */
is_varDeclaration *insert_varDeclaration_with(is_id_list *il, is_DIGSEQ d1, is_DIGSEQ d2, is_ID id) {
	
	is_varDeclaration *ivd = (is_varDeclaration *) malloc(sizeof(is_varDeclaration));
	ivd->disc_d = d_with;
	ivd->idList = il;
	ivd->digseq1 = d1;
	ivd->digseq2 = d2;
	ivd->id = id;
	
	return ivd;
}

is_varDeclaration *insert_varDeclaration_without(is_id_list *il, is_ID id) {
	
	is_varDeclaration *ivd = (is_varDeclaration *) malloc(sizeof(is_varDeclaration));
	ivd->disc_d = d_without;
	ivd->idList = il;
	ivd->id = id;
	
	return ivd;
}

/* idList */
is_id_list *insert_id_list(is_id_list *list, is_ID id) {
	
	is_id_list* il = (is_id_list *) malloc(sizeof(is_id_list));
	il->id = id;
		
	if (list == NULL)
		return il;
		
	is_id_list *aux;
			
	for (aux=list; aux->next != NULL; aux=aux->next);
	aux->next = il;
	
	return list;
}

/* functionDeclaration */
is_functionDeclaration *insert_functionDeclaration(is_functionHeading *fh) {
	
	is_functionDeclaration *ifd = (is_functionDeclaration *) malloc(sizeof(is_functionDeclaration));
	ifd->functionHeading = fh;
		
	return ifd;
}

/* functionDefinition */
is_functionDefinition *insert_functionDefinition(is_functionHeading *fh, is_functionBlock *fb) {
	
	is_functionDefinition *ifd = (is_functionDefinition *) malloc(sizeof(is_functionDefinition));
	ifd->functionHeading = fh;
	ifd->functionBlock = fb;
		
	return ifd;
}

/* functionHeading */
is_functionHeading *insert_functionHeading(is_ID id1, is_formalArgs_list *fal, is_ID id2) {
	
	is_functionHeading *ifh = (is_functionHeading *) malloc(sizeof(is_functionHeading));
	ifh->id1 = id1;
	ifh->id2 = id2;
	ifh->formalArgsList = fal;
	
	return ifh;
}

/* fh1 */
is_formalArgs_list *insert_formalArgs_list(is_formalArgs_list *list, is_formalArgs *fa) {
	
	is_formalArgs_list* ifal = (is_formalArgs_list *) malloc(sizeof(is_formalArgs_list));
	ifal->formalArgs = fa;
		
	if (list == NULL)
		return ifal;
		
	is_formalArgs_list *aux;
			
	for (aux=list; aux->next != NULL; aux=aux->next);
	aux->next = ifal;
	
	return list;
}

/* formalArgs */
is_formalArgs *insert_formalArgs(is_id_list *idl, is_ID id, bool var, bool arrayOf) {
	
	is_formalArgs *ifa = (is_formalArgs *) malloc(sizeof(is_formalArgs));
	ifa->idList = idl;
	ifa->id = id;
	ifa->var = var;
	ifa->arrayOf = arrayOf;
	
	return ifa;
}

/* functionBlock */
is_functionBlock *insert_functionBlock(is_varDeclaration_list *vdl, is_statement_list *sl) {
	
	is_functionBlock *ifb = (is_functionBlock *) malloc(sizeof(is_functionBlock));
	ifb->varDeclarationList = vdl;
	ifb->statementList = sl;
	
	return ifb;
}

/* statementList */
is_statement_list *insert_statement_list(is_statement_list *list, is_statement *s) {
	
	is_statement_list *isl = (is_statement_list *) malloc(sizeof(is_statement_list));
	isl->statement = s;
	
	if (list == NULL)
		return isl;
		
	is_statement_list *aux;
			
	for (aux=list; aux->next != NULL; aux=aux->next);
	aux->next = isl;
	
	return list;
}

/* statement */
is_statement *insert_statement_beginEnd(is_beginEnd *be) {
	
	is_statement *is = (is_statement *) malloc(sizeof(is_statement));
	is->disc_d = d_beginEnd;
	is->data_statement.beginEnd = be;
	
	return is;
}

is_statement *insert_statement_assignExp(is_assignExp *ae) {
	
	is_statement *is = (is_statement *) malloc(sizeof(is_statement));
	is->disc_d = d_assignExp;
	is->data_statement.assignExp = ae;
	
	return is;
}

is_statement *insert_statement_ifThen(is_ifThen *it) {
	
	is_statement *is = (is_statement *) malloc(sizeof(is_statement));
	is->disc_d = d_ifThen;
	is->data_statement.ifThen = it;
	
	return is;
}

is_statement *insert_statement_whileDo(is_whileDo *wd) {
	
	is_statement *is = (is_statement *) malloc(sizeof(is_statement));
	is->disc_d = d_whileDo;
	is->data_statement.whileDo = wd;
	
	return is;
}

is_statement *insert_statement_for(is_for *f) {
	
	is_statement *is = (is_statement *) malloc(sizeof(is_statement));
	is->disc_d = d_for;
	is->data_statement.for2 = f;
	
	return is;
}

is_statement *insert_statement_valParamstr(is_valParamstr *vp) {
	
	is_statement *is = (is_statement *) malloc(sizeof(is_statement));
	is->disc_d = d_valParamstr;
	is->data_statement.valParamstr = vp;
	
	return is;
}

is_statement *insert_statement_writeln(is_writeln *w) {
	
	is_statement *is = (is_statement *) malloc(sizeof(is_statement));
	is->disc_d = d_writeln;
	is->data_statement.writeln = w;
	
	return is;
}

/* beginEnd */
is_beginEnd *insert_beginEnd(is_statement_list *sl) {
	
	is_beginEnd *ibe = (is_beginEnd *) malloc(sizeof(is_beginEnd));
	ibe->statementList = sl;
	
	return ibe;
}

/* assignExp */
is_assignExp *insert_assignExp(is_ID id, is_expression *e1, is_expression *e2) {
	
	is_assignExp *iae = (is_assignExp *) malloc(sizeof(is_assignExp));
	iae->id = id;
	iae->expression1 = e1;
	iae->expression2 = e2;
	
	return iae;
}

/* ifThen */
is_ifThen *insert_ifThen(is_expression *e, is_statement *is, is_statement *es, bool iselse) {
	
	is_ifThen *it = (is_ifThen *) malloc(sizeof(is_ifThen));
	it->expression = e;
	it->ifStatement = is;
	it->elseStatement = es;
	it->iselse = iselse;
	
	return it;
}

/* whileDo */
is_whileDo *insert_whileDo(is_expression *e, is_statement *s) {
	
	is_whileDo *wd = (is_whileDo *) malloc(sizeof(is_whileDo));
	wd->expression = e;
	wd->statement = s;
	
	return wd;
}

/* for */
is_for *insert_for_to(is_ID id, is_expression *e1, is_expression *e2, is_statement *s) {
	
	is_for *f = (is_for *) malloc(sizeof(is_for));
	f->disc_d = d_to;
	f->id = id;
	f->expression1 = e1;
	f->expression2 = e2;
	f->statement = s;
	
	return f;
}


is_for *insert_for_downto(is_ID id, is_expression *e1, is_expression *e2, is_statement *s) {
	
	is_for *f = (is_for *) malloc(sizeof(is_for));
	f->disc_d = d_downto;
	f->id = id;
	f->expression1 = e1;
	f->expression2 = e2;
	f->statement = s;
	
	return f;
}

/* valParamstr */
is_valParamstr *insert_valParamstr(is_expression *e, is_ID id) {
	
	is_valParamstr *vp = (is_valParamstr *) malloc(sizeof(is_valParamstr));
	vp->expression = e;
	vp->id = id;
	
	return vp;
}


/* writeln */
is_writeln *insert_writeln(is_expression *e) {
	
	is_writeln *w = (is_writeln *) malloc(sizeof(is_writeln));
	w->expression = e;
	
	return w;
}

/* expression */
is_expression *insert_expression_operators(is_operators *op) {
	
	is_expression *ie = (is_expression *) malloc(sizeof(is_expression));
	ie->disc_d = d_operators;
	ie->data_expression.operators = op;
	
	return ie;
}

is_expression *insert_expression_arrayExp(is_arrayExp *ae) {
	
	is_expression *ie = (is_expression *) malloc(sizeof(is_expression));
	ie->disc_d = d_arrayExp;
	ie->data_expression.arrayExp = ae;
	
	return ie;
}

is_expression *insert_expression_numberExp(is_numberExp *ne) {
	
	is_expression *ie = (is_expression *) malloc(sizeof(is_expression));
	ie->disc_d = d_numberExp;
	ie->data_expression.numberExp = ne;
	
	return ie;
}

is_expression *insert_expression_notExp(is_notExp *ne) {
	
	is_expression *ie = (is_expression *) malloc(sizeof(is_expression));
	ie->disc_d = d_notExp;
	ie->data_expression.notExp = ne;
	
	return ie;
}

is_expression *insert_expression_funcExp(is_funcExp *fe) {
	
	is_expression *ie = (is_expression *) malloc(sizeof(is_expression));
	ie->disc_d = d_funcExp;
	ie->data_expression.funcExp = fe;
	
	return ie;
}

/* operators */
is_operators *insert_operators_op1(is_OP1 op1, is_expression *e1, is_expression *e2) {
	
	is_operators *op = (is_operators *) malloc(sizeof(is_operators));
	op->disc_d = d_op1;
	op->data_operators.op1 = op1;
	op->expression1 = e1;
	op->expression2 = e2;
	
	return op;
}

is_operators *insert_operators_op2(is_OP2 op2, is_expression *e1, is_expression *e2) {
	
	is_operators *op = (is_operators *) malloc(sizeof(is_operators));
	op->disc_d = d_op2;
	op->data_operators.op2 = op2;
	op->expression1 = e1;
	op->expression2 = e2;
	
	return op;
}

is_operators *insert_operators_op3(is_OP3 op3, is_expression *e1, is_expression *e2) {
	
	is_operators *op = (is_operators *) malloc(sizeof(is_operators));
	op->disc_d = d_op3;
	op->data_operators.op3 = op3;
	op->expression1 = e1;
	op->expression2 = e2;
	
	return op;
}

is_operators *insert_operators_op4(is_OP4 op4, is_expression *e1, is_expression *e2) {
	
	is_operators *op = (is_operators *) malloc(sizeof(is_operators));
	op->disc_d = d_op4;
	op->data_operators.op4 = op4;
	op->expression1 = e1;
	op->expression2 = e2;
	
	return op;
}

/* numberExp */
is_numberExp *insert_numberExp_digseq(is_DIGSEQ digseq) {
	
	is_numberExp *ne = (is_numberExp *) malloc(sizeof(is_numberExp));
	ne->disc_d = d_digseq;
	ne->data_numberExp.digseq = digseq;
	
	return ne;
}

is_numberExp *insert_numberExp_realnumber(is_REALNUMBER realnumber) {
	
	is_numberExp *ne = (is_numberExp *) malloc(sizeof(is_numberExp));
	ne->disc_d = d_realnumber;
	ne->data_numberExp.realnumber = realnumber;
	
	return ne;
}

/* arrayExp */
is_arrayExp *insert_arrayExp(is_ID id, is_expression *e) {
	
	is_arrayExp *ie = (is_arrayExp *) malloc(sizeof(is_arrayExp));
	ie->id = id;
	ie->expression = e;
	
	return ie;
}

/* notExp */
is_notExp *insert_notExp(is_expression *e) {
	
	is_notExp *ne = (is_notExp *) malloc(sizeof(is_notExp));
	ne->expression = e;
	
	return ne;
}

/* funcExp */
is_funcExp *insert_funcExp(is_ID id, is_expression_list *el) {
	
	is_funcExp *fe = (is_funcExp *) malloc(sizeof(is_funcExp));
	fe->id = id;
	fe->expressionList = el;
	
	return fe;
}

/* expressionList */
is_expression_list *insert_expression_list(is_expression_list *list, is_expression *e) {
	
	is_expression_list* el = (is_expression_list *) malloc(sizeof(is_expression_list));
	el->expression = e;
		
	if (list == NULL)
		return el;
		
	is_expression_list *aux;
			
	for (aux=list; aux->next != NULL; aux=aux->next);
	aux->next = el;
	
	return list;
}
