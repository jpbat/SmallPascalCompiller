#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "symbol_table.h"
#include "semantic.h"
#include "translate.h"

int returncounter = 0;
int tempcounter = 0;
int ifcounter = 0;
int whilecounter = 0;
int forcounter = 0;

const char *typeToTypeC(basic_type type) {
	return type == integer || type == arrayI ? "int" : type == real || type == arrayR ? "double" : "char";
}

/* op1 */
basic_type translate_op1(is_OP1 op1, is_expression *e1, is_expression *e2) {
	char *str = toLower(op1);

	translate_expression(e1);
	int t1 = tempcounter-1;
	
	translate_expression(e2);
	int t2 = tempcounter-1;

	printf("*((char *) sp->temp[%d]) = *((char *) sp->temp[%d]) %s *((char *) sp->temp[%d]);\n", getTemp(boolean), t1, strcmp(str, "and") == 0 ? "&&" : "||", t2);
	return boolean;
}

/* op2 */
basic_type translate_op2(is_OP2 op2, is_expression *e1, is_expression *e2) {
	basic_type type1 = translate_expression(e1);
	int t1 = tempcounter-1;
	
	basic_type type2 = translate_expression(e2);
	int t2 = tempcounter-1;

	printf("*((char *) sp->temp[%d]) = *((%s *) sp->temp[%d]) %s *((%s *) sp->temp[%d]);\n", getTemp(boolean), typeToTypeC(type1), t1, strcmp(op2, "=") == 0 ? "==" : strcmp(op2, "<>") == 0 ? "!=" : op2, typeToTypeC(type2), t2);
	return boolean;
}

/* op3 */
basic_type translate_op3(is_OP3 op3, is_expression *e1, is_expression *e2) {
	int t1, t2;
	basic_type type1 = -1, type2;
	
	if (e1)
		type1 = translate_expression(e1);
	t1 = tempcounter-1;
	
	type2 = translate_expression(e2);
	t2 = tempcounter-1;
	
	if (e1) {
		printf("*((%s *) sp->temp[%d]) = *((%s *) sp->temp[%d]) %s *((%s *) sp->temp[%d]);\n", type1 == real || type2 == real ? "double" : "int", getTemp(type1 == real || type2 == real ? real : integer), typeToTypeC(type1), t1, op3, typeToTypeC(type2), t2);
		return type1 == real || type2 == real ? real : integer;
			
	} else {
		printf("*((%s *) sp->temp[%d]) = %s*((%s *) sp->temp[%d]);\n", typeToTypeC(type2), getTemp(type2), op3, typeToTypeC(type2), t2);
		return type2;
	}
}

/* op4 */
basic_type translate_op4(is_OP4 op4, is_expression *e1, is_expression *e2) {
	char *str = toLower(op4);
	
	basic_type type1 = translate_expression(e1);
	int t1 = tempcounter-1;
	
	basic_type type2 = translate_expression(e2);
	int t2 = tempcounter-1;
	
	if (strcmp(str, "mod") == 0 || strcmp(str, "div") == 0) {
		printf("*((int *) sp->temp[%d]) = *((int *) sp->temp[%d]) %s *((int *) sp->temp[%d]);\n", getTemp(integer), t1, strcmp(str, "mod") == 0 ? "%" : "/", t2);
		return integer;
	}
	
	else {
		if (strcmp(str, "/") == 0) {
			printf("*((double *) sp->temp[%d]) = 1.0 * (*((%s *) sp->temp[%d])) / (*((%s *) sp->temp[%d]));\n", getTemp(real), typeToTypeC(type1), t1, typeToTypeC(type2), t2);
			return real;
		}
		else {
			printf("*((%s *) sp->temp[%d]) = (*((%s *) sp->temp[%d])) * (*((%s *) sp->temp[%d]));\n", type1 == real || type2 == real ? "double" : "int", getTemp(type1 == real || type2 == real ? real : integer), typeToTypeC(type1), t1, typeToTypeC(type2), t2);
			return type1 == real || type2 == real ? real : integer;
		}
	}
}

/* start */
void translate_start(is_start *s) {

	/* header */
	printf("#include <stdio.h>\n");
	printf("#include <stdlib.h>\n");
	printf("#include \"frame.h\"\n\n");

	/* main */
	printf("int main(int argc, char **argv) {\n");
	printf("\n/* Pointers */\n");
	printf("frame *sp = (frame *) malloc(sizeof(frame));\n"); 
	printf("frame *fp = NULL;\n");
	printf("int _ra;\n");
	
	/* bloco main */
	translate_block(s->block);
	
	/* retornos */
	printf("\n/* Redirectores */\n");
	printf("goto exit;\n");
	printf("redirector:\n");
	
	int i;
	for (i=0; i<returncounter; i++)
		printf("if (_ra == %d) goto return%d;\n", i, i);
	printf("exit:\nreturn 0;\n");
	printf("}\n\n");
}

/* block */
void translate_block(is_block *b) {
	
	if (b->varDeclarationList)
		translate_globalVarDeclaration_list(b->varDeclarationList);

	if (b->functionDecOrDefList)
		translate_functionDecOrDef_list(b->functionDecOrDefList);
	
	if (b->statementList) {
		printf("\n/* Main statments */\n");
		statTable = pe->global;
		translate_statement_list(b->statementList);
	}
}

/* variableDeclarationList (global) */
void translate_globalVarDeclaration_list(is_varDeclaration_list *vdl) {
	
	printf("\n/* Vars. globais */\n");
	
	is_varDeclaration_list *aux;
	for(aux = vdl; aux != NULL; aux=aux->next)
		translate_globalVarDeclaration(aux->varDeclaration);
}

/* varDeclaration (global) */
void translate_globalVarDeclaration(is_varDeclaration *vd) {
		
	if (strcmp(vd->id, "integer") == 0)
		printf("int ");
	else if (strcmp(vd->id, "boolean") == 0)
		printf("char ");
	else
		printf("double ");
	
	table_element *te;
	is_id_list *aux;
	int i;
	for(aux = vd->idList, i=0; aux; aux=aux->next, i++) {
		te = lookup(pe->global, aux->id);
		printf("%sg%d", i==0?"":", ", te->offset);
		if (vd->disc_d == d_with) {
			printf("[%d]", vd->digseq2 - vd->digseq1 + 1);
		}
	}
	
	printf(";\n");
}

/* variableDeclarationList */
void translate_varDeclaration_list(is_varDeclaration_list *vdl, table_element *table) {
	
	printf("\n/* Vars. locais */\n");
	is_varDeclaration_list *aux;
	for(aux = vdl; aux != NULL; aux=aux->next)
		translate_varDeclaration(aux->varDeclaration, table);
}

/* variableDeclaration */
void translate_varDeclaration(is_varDeclaration *vd, table_element *table) {
	
	table_element *te;
	is_id_list *aux;
	for(aux = vd->idList; aux; aux=aux->next) {
		te = lookup(table, aux->id);
		switch (te->type) {
			case integer:
				printf("sp->locals[%d] = (int *) malloc(sizeof(int));\t\t/* %s */\n", te->offset, aux->id);
				break;
			case real:
				printf("sp->locals[%d] = (double *) malloc(sizeof(double));\t/* %s */\n", te->offset, aux->id);
				break;
			case boolean:
				printf("sp->locals[%d] = (char *) malloc(sizeof(char));\t\t/* %s */\n", te->offset, aux->id);
				break;
				
			case arrayI:
				printf("sp->locals[%d] = (int *) malloc(%d*sizeof(int));\t\t/* %s */\n", te->offset, (vd->digseq2-vd->digseq1+1), aux->id);
				break;
			case arrayR:
				printf("sp->locals[%d] = (double *) malloc(%d*sizeof(double));\t/* %s */\n", te->offset, (vd->digseq2-vd->digseq1+1), aux->id);
				break;
			case arrayB:
				printf("sp->locals[%d] = (char *) malloc(%d*sizeof(char));\t/* %s */\n", te->offset, (vd->digseq2-vd->digseq1+1), aux->id);
				break;
		}
	}
}

/* functionDecOrDefList */
void translate_functionDecOrDef_list(is_functionDecOrDef_list *fdodl) {
	
	is_functionDecOrDef_list *aux;
	for(aux = fdodl; aux; aux=aux->next) {
		if (aux->disc_d == d_functionDef)
			translate_functionDefinition(aux->data_functionDecOrDef_list.functionDefinition);
	}
}

/* functionDefinition */
void translate_functionDefinition(is_functionDefinition *fd) {

	/* argumentos */
	translate_functionHeading(fd->functionHeading);
	
	/* body da funcao */
	environment_list *el = lookupFunction(fd->functionHeading->id1);
	translate_functionBlock(fd->functionBlock, el->locals);
	
	/* epilogo */
	printf("\n/* Epilogo */\n");
	printf("_ra = sp->return_address;\n");
	printf("sp = sp->parent;\n");
	printf("fp = sp->parent;\n");
	printf("goto redirector;\n");
	printf("%s_skip: ;\n", fd->functionHeading->id1);
}

/* functionHeading */
void translate_functionHeading(is_functionHeading *fh) {
	
	/* Prologo  da funcao */
	printf("\n/* Funcao %s */\n", fh->id1);
	printf("/* Prologo */\n");
	printf("goto %s_skip;\n", fh->id1);
	printf("%s:\n", fh->id1);
	printf("fp = sp;\n");
	printf("sp = (frame *) malloc(sizeof(frame));\n");
	printf("sp->parent = fp;\n");
	printf("sp->return_address = _ra;\n");
	
	/* Function name var */
	table_element *te;
	environment_list *el = lookupFunction(fh->id1);
	printf("\n/* Return var (%s) */\n", fh->id1);
	printf("sp->locals[0] = (%s *) malloc(sizeof(%s));\n", typeToTypeC(el->locals->type), typeToTypeC(el->locals->type));
	
	/* Formal args */
	printf("\n/* Formal args */\n");
	for (te=el->locals->next; te && te->param; te=te->next) {
		switch (te->type) {
			case integer:
				printf("sp->locals[%d] = (int *) malloc(sizeof(int));\t\t/* %s */\n", te->offset, te->name);
				printf("*((int *) sp->locals[%d]) = *((int *) sp->parent->outgoing[%d]);\n", te->offset, te->offset-1);
				break;
			case real:
				printf("sp->locals[%d] = (double *) malloc(sizeof(double));\t/* %s */\n", te->offset, te->name);
				printf("*((double *) sp->locals[%d]) = *((double *) sp->parent->outgoing[%d]);\n", te->offset, te->offset-1);
				break;
			case boolean:
				printf("sp->locals[%d] = (char *) malloc(sizeof(char));\t\t/* %s */\n", te->offset, te->name);
				printf("*((char *) sp->locals[%d]) = *((char *) sp->parent->outgoing[%d]);\n", te->offset, te->offset-1);
				break;
				
			case arrayI:
			case arrayR:
			case arrayB:
				printf("sp->locals[%d] = sp->parent->outgoing[%d];\n", te->offset, te->offset-1);
		}
	}
}

/* functionBlock */
void translate_functionBlock(is_functionBlock *fb, table_element *table) {

	if (fb->varDeclarationList)
		translate_varDeclaration_list(fb->varDeclarationList, table);
	
	printf("\n/* Function statements*/\n");
	if (fb->statementList) {
		statTable = table;
		translate_statement_list(fb->statementList);
	}
	
	/* Return value */
	printf("\n/* Return value */\n");
	switch (table->type) {
		case integer:
			printf("sp->parent->returnValue = (int *) malloc(sizeof(int));\n");
			printf("*((int *) sp->parent->returnValue) = *((int *) sp->locals[0]);\n");
			break;
		case real:
			printf("sp->parent->returnValue = (double *) malloc(sizeof(double));\n");
			printf("*((double *) sp->parent->returnValue) = *((double *) sp->locals[0]);\n");
			break;
		case boolean:
			printf("sp->parent->returnValue = (char *) malloc(sizeof(char));\n");
			printf("*((char *) sp->parent->returnValue) = *((char *) sp->locals[0]);\n");
			break;
	}
}

/* statementList */
void translate_statement_list(is_statement_list *sl) {
	is_statement_list *aux;
	for(aux = sl; aux != NULL; aux=aux->next)
		translate_statement(aux->statement);
}

/* statement */
void translate_statement(is_statement *s) {
	
	if (s) {
		switch (s->disc_d) {
			case d_beginEnd:
				translate_beginEnd(s->data_statement.beginEnd);
				break;
			
			case d_assignExp:
				translate_assignExp(s->data_statement.assignExp);
				break;
			
			case d_ifThen:
				translate_ifThen(s->data_statement.ifThen);
				break;
				
			case d_whileDo:
				translate_whileDo(s->data_statement.whileDo);
				break;
				
			case d_for:
				translate_for(s->data_statement.for2);
				break;
				
			case d_valParamstr:
				translate_valParamstr(s->data_statement.valParamstr);
				break;
				
			case d_writeln:
				translate_writeln(s->data_statement.writeln);
				break;
		}
	}
}

/* beginEnd */
void translate_beginEnd(is_beginEnd *be) {
	if(be->statementList)
		translate_statement_list(be->statementList);
}

/* assignExp */
void translate_assignExp(is_assignExp *ae) {
	
	int t1, t2;
	char global = 0;
	basic_type type1 = -1, type2;
	table_element *te = lookup(statTable, ae->id);
	if (!te) {
		te = lookup(pe->global, ae->id);
		global = 1;
	}
	
	if (ae->expression1)
		type1 = translate_expression(ae->expression1);
	t1 = tempcounter-1;
	
	type2 = translate_expression(ae->expression2);
	t2 = tempcounter-1;
	
	if (statTable == pe->global || global) {
		if (ae->expression1)
			printf("g%d[*((%s *) sp->temp[%d])] = *((%s *) sp->temp[%d]);\n", te->offset, typeToTypeC(type1), t1, typeToTypeC(type2), t2);
		else
			printf("g%d = *((%s *) sp->temp[%d]);\n", te->offset, typeToTypeC(type2), t2);
	} else {
		if (ae->expression1)
			printf("((%s *) sp->locals[%d])[*((%s *) sp->temp[%d])] = *((%s *) sp->temp[%d]);\n", typeToTypeC(te->type), te->offset, typeToTypeC(type1), t1, typeToTypeC(type2), t2);
		else
			printf("*((%s *) sp->locals[%d]) = *((%s *) sp->temp[%d]);\n", typeToTypeC(te->type), te->offset, typeToTypeC(type2), t2);
	}
}

/* ifThen */
void translate_ifThen(is_ifThen *ae) {
	
	int i = ifcounter++;
	printf("\n/* if%d */\n", i);
	
	translate_expression(ae->expression);
	int t = tempcounter-1;
	
	printf("if (!(*((char *) sp->temp[%d]))) goto else%d;\n", t, i);
	translate_statement(ae->ifStatement);
	printf("goto endif%d;\n", i);
	
	printf("else%d: ;\n", i);
	if (ae->iselse)
		translate_statement(ae->elseStatement);
		
	printf("endif%d: ;\n", i);
}

/* whileDo */
void translate_whileDo(is_whileDo *wd) {
	
	int w = whilecounter++;
	printf("\nwhile%d: ;\n", w);
	
	translate_expression(wd->expression);
	int t = tempcounter-1;
	
	printf("if (!(*((char *) sp->temp[%d]))) goto endwhile%d;\n", t, w);
	translate_statement(wd->statement);
	printf("goto while%d;\n", w);
	
	printf("endwhile%d: ;\n", w);
}

/* for */
void translate_for(is_for *f) {
	
	int fc = forcounter++;
	printf("\n/* for%d */\n", fc);
	
	char global = 0;
	table_element *te = lookup(statTable, f->id);
	if (!te) {
		te = lookup(pe->global, f->id);
		global = 1;
	}
	
	translate_expression(f->expression1);
	int t1 = tempcounter-1;
	
	if (statTable == pe->global || global)
		printf("g%d = *((int *) sp->temp[%d]);\n", te->offset, t1);
	else
		printf("*((%s *) sp->locals[%d]) = *((int *) sp->temp[%d]);\n", typeToTypeC(te->type), te->offset, t1);
	
	printf("for%d: ;\n", fc);
	
	translate_expression(f->expression2);
	int t2 = tempcounter-1;
	
	if (statTable == pe->global || global)
		printf("if (!(g%d %s *((int *) sp->temp[%d]))) goto endfor%d;\n", te->offset, f->disc_d == d_to ? "<=" : ">=", t2, fc);
	 else
		printf("if (!(*((%s *) sp->locals[%d]) %s *((int *) sp->temp[%d]))) goto endfor%d;\n", typeToTypeC(te->type), te->offset, f->disc_d == d_to ? "<=" : ">=", t2, fc);
	
	translate_statement(f->statement);
	
	if (statTable == pe->global || global)
		printf("g%d%s;\n", te->offset, f->disc_d == d_to ? "++" : "--");
	else
		printf("(*((%s *) sp->locals[%d]))%s;\n", typeToTypeC(te->type), te->offset, f->disc_d == d_to ? "++" : "--");
		
	printf("goto for%d;\n", fc);
	
	printf("endfor%d: ;\n", fc);
}

/* valParamstr */
void translate_valParamstr(is_valParamstr *vp) {
	
	int t;
	char global = 0;
	table_element *te = lookup(statTable, vp->id);
	if (!te) {
		te = lookup(pe->global, vp->id);
		global = 1;
	}
	
	translate_expression(vp->expression);
	t = tempcounter-1;
	
	if (statTable == pe->global || global) {
		if (te->type == integer)
			printf("sscanf(argv[*((int *) sp->temp[%d])], \"%%d\", &g%d);\n", t, te->offset);
		else
			printf("sscanf(argv[*((int *) sp->temp[%d])], \"%%lf\", &g%d);\n", t, te->offset);
	}
	
	else {
		if (te->type == integer)
			printf("sscanf(argv[*((int *) sp->temp[%d])], \"%%d\", (int *) sp->locals[%d]);\n", t, te->offset);
		else
			printf("sscanf(argv[*((int *) sp->temp[%d])], \"%%lf\", (double *) sp->locals[%d]);\n", t, te->offset);
	}
	
}

/* writeln */
void translate_writeln(is_writeln *w) {
	basic_type type = translate_expression(w->expression);
	int t = tempcounter-1;

	switch (type) {
		case integer:
		case arrayI:
			printf("printf(\"%%d\\n\", *((int*) sp->temp[%d]));\n", t);
			break;
		case real:
		case arrayR:
			printf("printf(\"%%f\\n\", *((double *) sp->temp[%d]));\n", t);
			break;
		case boolean:
		case arrayB:
		case reservedID:
			printf("if (*((char*) sp->temp[%d])) printf(\"true\\n\");\n", t);
			printf("if (!(*((char*) sp->temp[%d]))) printf(\"false\\n\");\n", t);
			break;
	}
}

/* expression */
basic_type translate_expression(is_expression *e) {
	switch (e->disc_d) {
		case d_operators:
			return translate_operators(e->data_expression.operators);
		
		case d_numberExp:
			return translate_numberExp(e->data_expression.numberExp);
			
		case d_arrayExp:
			return translate_arrayExp(e->data_expression.arrayExp);
		
		case d_notExp:
			return translate_notExp(e->data_expression.notExp);
			
		case d_funcExp:
			return translate_funcExp(e->data_expression.funcExp);
	}
}

/* operators */
basic_type translate_operators(is_operators *op) {
	switch (op->disc_d) {
		case d_op1:
			return translate_op1(op->data_operators.op1, op->expression1, op->expression2);
			
		case d_op2:
			return translate_op2(op->data_operators.op1, op->expression1, op->expression2);
			
		case d_op3:
			return translate_op3(op->data_operators.op1, op->expression1, op->expression2);
			
		case d_op4:
			return translate_op4(op->data_operators.op1, op->expression1, op->expression2);
	}
}

/* numberExp */
basic_type translate_numberExp(is_numberExp *ne) {

	if (ne->disc_d == d_digseq)
		printf("*((int *) sp->temp[%d]) = %d;\n", getTemp(integer), ne->data_numberExp.digseq);
	else
		printf("*((double *) sp->temp[%d]) = %f;\n", getTemp(real), ne->data_numberExp.realnumber);
	
	return ne->disc_d == d_digseq ? integer : real;
}

/* arrayExp */
basic_type translate_arrayExp(is_arrayExp *ae) {
	
	int t;
	char global = 0;
	basic_type type = -1;
	table_element *te = lookup(statTable, ae->id);
	if (!te) {
		te = lookup(pe->global, ae->id);
		global = 1;
	}
	
	if (ae->expression)
		type = translate_expression(ae->expression);
	else if (te->type == arrayB || te->type == arrayI || te->type == arrayR)
		return te->type;
		
	t = tempcounter-1;
	
	if (statTable == pe->global || global) {
		if (te->offset == 3 || te->offset == 4)
			printf("*((char *) sp->temp[%d]) = %d;\n", getTemp(boolean), te->offset == 3 ? 1 : 0);
		else if (te->offset == 5)
			printf("*((int *) sp->temp[%d]) = argc;\n", getTemp(integer));
		else if (ae->expression)
			printf("*((%s *) sp->temp[%d]) = g%d[*((%s *) sp->temp[%d])];\n", typeToTypeC(te->type), getTemp(te->type), te->offset, typeToTypeC(type), t);
		else
			printf("*((%s *) sp->temp[%d]) = g%d;\n", typeToTypeC(te->type), getTemp(te->type), te->offset);
	}
	
	else {
		if (ae->expression)
			printf("*((%s *) sp->temp[%d]) = ((%s *) sp->locals[%d])[*((%s *) sp->temp[%d])];\n", typeToTypeC(te->type), getTemp(te->type), typeToTypeC(te->type), te->offset, typeToTypeC(type), t);
		else
			printf("*((%s *) sp->temp[%d]) = *((%s *) sp->locals[%d]);\n", typeToTypeC(te->type), getTemp(te->type), typeToTypeC(te->type), te->offset);
	}
	
	return te->type;
}

/* notExp */
basic_type translate_notExp(is_notExp *ne) {
	translate_expression(ne->expression);
	int t = tempcounter-1;
	
	printf("*((char *) sp->temp[%d]) = !(*((char *) sp->temp[%d]));\n", getTemp(boolean), t);
	return boolean;
}

/* funcExp */
basic_type translate_funcExp(is_funcExp *fe) {

	environment_list *el = lookupFunction(fe->id);
	printf("\n/* Call %s */\n", fe->id);
	
	/* Passagem de parametros */
	if (fe->expressionList, el)
		translate_expression_list(fe->expressionList, el);
	
	printf("\n/* Endereco de retorno e chamada */\n");
	printf("_ra = %d;\n",returncounter);
	printf("goto %s;\n", fe->id);
	printf("return%d: ;\n", returncounter);
	returncounter++;
	
	/* Valor de retorno da funcao */
	printf("*((%s *) sp->temp[%d]) = *((%s *) sp->returnValue);\n", typeToTypeC(el->returnType), getTemp(el->returnType), typeToTypeC(el->returnType));
	
	return el->returnType;
}

/* expressionList */
void translate_expression_list(is_expression_list *elist, environment_list *el) {
	int i, t;
	char global;
	basic_type type;
	is_expression_list *aux;
	table_element *te, *aux2;

	printf("/* Passagem de parametros */\n");
	for (aux = elist, te = el->locals->next, i=0; aux; aux=aux->next, te = te->next, i++) {
		global = 0;
		type = translate_expression(aux->expression);
		t = tempcounter-1;
		
		switch (te->type) {
			case integer:
				printf("sp->outgoing[%d] = (int *) malloc(sizeof(int));\n", i);
				printf("*((int *) sp->outgoing[%d]) = *((%s *) sp->temp[%d]);\n", i, typeToTypeC(type), t);
				break;
			case real:
				printf("sp->outgoing[%d] = (double *) malloc(sizeof(double));\n", i);
				printf("*((double *) sp->outgoing[%d]) = *((%s *) sp->temp[%d]);\n", i, typeToTypeC(type), t);
				break;
			case boolean:
				printf("sp->outgoing[%d] = (char *) malloc(sizeof(char));\n", i);
				printf("*((char *) sp->outgoing[%d]) = *((%s *) sp->temp[%d]);\n", i, typeToTypeC(type), t);
				break;
				
			case arrayI:
			case arrayR:
			case arrayB:
				aux2 = lookup(statTable, aux->expression->data_expression.arrayExp->id);
				if (!aux2) {
					te = lookup(pe->global, aux->expression->data_expression.arrayExp->id);
					global = 1;
				}
				
				if (statTable == pe->global || global)
					printf("sp->outgoing[%d] = g%d;\n", i, aux2->offset);
				else
					printf("sp->outgoing[%d] = sp->locals[%d];\n", i, aux2->offset);
				break;
		}
	}
}

int getTemp(basic_type type) {
	printf("sp->temp[%d] = (%s *) malloc(sizeof(%s));\n", tempcounter, typeToTypeC(type), typeToTypeC(type));
	return tempcounter++;
}
