#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "semantic.h"

char *toLower(char *str) {
	int i, len = strlen(str);
	char *str2 = (char *) malloc(len+1);
	
	for (i=0; i<len; i++)
		str2[i] = tolower(str[i]);
	str2[i] = '\0';
		
	return str2;
}

basic_type check_type(char *str, char array) {
	char *str2 = toLower(str);
	if (array) {
		if (strcmp(str2, "integer") == 0)
			return arrayI;
		if (strcmp(str2, "real") == 0)
			return arrayR;
		if (strcmp(str2, "boolean") == 0)
			return arrayB;
	} else {
		if (strcmp(str2, "integer") == 0)
			return integer;
		if (strcmp(str2, "real") == 0)
			return real;
		if (strcmp(str2, "boolean") == 0)
			return boolean;
	}
	free(str2);
	return -1;
}

const char *typeToString(basic_type type) {
	switch(type) {
		case integer:
			return "integer";
			
		case real:
			return "real";
			
		case boolean:
			return "boolean";
			
		case arrayI:
		case arrayR:
		case arrayB:
			return "array";
			
		case reservedID:
			return "reserved id";
			
		case function:
			return "function";
			
		case program:
			return "program";
			
		default:
			return "unknown type";
	}
}

const char *typeToString2(basic_type type) {
	switch(type) {
		case integer:
			return "integer";
			
		case real:
			return "real";
			
		case boolean:
			return "boolean";
			
		case arrayI:
			return "array of integer";
		
		case arrayR:
			return "array of real";
			
		case arrayB:
			return "array of boolean";
			
		case reservedID:
			return "reserved id";
			
		case function:
			return "function";
			
		case program:
			return "program";
			
		default:
			return "unknown type";
	}
}

void show_table() {
	table_element *aux;
	environment_list *aux2;
	
	printf("===== Global Symbol Table =====\n");
	for (aux=pe->global; aux; aux=aux->next)
		printf("%s\t%s\t%d\n", aux->name, typeToString2(aux->type), aux->offset);
		
	for (aux2=pe->funcs; aux2; aux2=aux2->next) {
		printf("===== Function %s Symbol Table =====\n", aux2->name);
		for (aux=aux2->locals; aux; aux=aux->next)
			printf("%s\t%s%s\t%d\n", aux->name, typeToString2(aux->type), aux->param?"\tparam":"", aux->offset);
	}
}

/* op1 */
basic_type check_op1(is_OP1 op1, is_expression *e1, is_expression *e2) {
	basic_type type1 = check_expression(e1);
	basic_type type2 = check_expression(e2);
	
	if (type1 == arrayB || type1 == arrayI || type1 == arrayR || type2 == arrayB || type2 == arrayI || type2 == arrayR) {
		printf("Incompatible type (got array, required boolean)\n");
		exit(0);
	}
	
	if (type1 != boolean || type2 != boolean) {
		printf("Operator %s cannot be applied to types %s, %s\n", op1, typeToString(type1), typeToString(type2));
		exit(0);
	} else if (type1 == boolean && type2 == boolean)
		return boolean;
	
	printf("Operator %s cannot be applied to types %s, %s\n", op1, typeToString(type1), typeToString(type2));
	exit(0);
}

/* op2 */
basic_type check_op2(is_OP2 op2, is_expression *e1, is_expression *e2) {
	basic_type type1 = check_expression(e1);
	basic_type type2 = check_expression(e2);
	
	if (type1 == arrayB || type1 == arrayI || type1 == arrayR || type2 == arrayB || type2 == arrayI || type2 == arrayR) {
		printf("Incompatible type (got array, required boolean or integer or real)\n");
		exit(0);
	}
	
	if (type1 == boolean && type2 != boolean) {
		printf("Operator %s cannot be applied to types %s, %s\n", op2, typeToString(type1), typeToString(type2));
		exit(0);
	} else if (type1 == boolean && type2 == boolean)
		return boolean;
	
	if (type1 == integer) {
		if (type2 != integer && type2 != real) {
			printf("Operator %s cannot be applied to types %s, %s\n", op2, typeToString(type1), typeToString(type2));
			exit(0);
		}
		return boolean;
	}
	
	if (type1 == real) {
		if (type2 != integer && type2 != real) {
			printf("Operator %s cannot be applied to types %s, %s\n", op2, typeToString(type1), typeToString(type2));
			exit(0);
		}
		return boolean;
	}
	
	printf("Operator %s cannot be applied to types %s, %s\n", op2, typeToString(type1), typeToString(type2));
	exit(0);
}

/* op3 */
basic_type check_op3(is_OP3 op3, is_expression *e1, is_expression *e2) {
	basic_type type1 = -1;
	if (e1)
		type1 = check_expression(e1);
	basic_type type2 = check_expression(e2);
	
	if (type1 == arrayB || type1 == arrayI || type1 == arrayR || type2 == arrayB || type2 == arrayI || type2 == arrayR) {
		printf("Incompatible type (got array, required boolean or integer or real)\n");
		exit(0);
	}
	
	if (e1) {
		if (type1 == integer) {
			if (type2 != integer && type2 != real) {
				printf("Operator %s cannot be applied to types %s, %s\n", op3, typeToString(type1), typeToString(type2));
				exit(0);
			} else
				return type2;
		}
		
		if (type1 == real) {
			if (type2 != integer && type2 != real) {
				printf("Operator %s cannot be applied to types %s, %s\n", op3, typeToString(type1), typeToString(type2));
				exit(0);
			} else
				return type1;
		}
		
		if (type1 == boolean && type2 != boolean) {
			printf("Operator %s cannot be applied to types %s, %s\n", op3, typeToString(type1), typeToString(type2));
			exit(0);
		} else if (type1 == boolean && type2 == boolean)
			return boolean;
		
		printf("Operator %s cannot be applied to types %s, %s\n", op3, typeToString(type1), typeToString(type2));
		exit(0);
			
	} else {
		if (type2 != integer && type2 != real) {
			printf("Operator %s cannot be applied to type %s\n", op3, typeToString(type2));
			exit(0);
		} else
			return type2;
	}
}

/* op4 */
basic_type check_op4(is_OP4 op4, is_expression *e1, is_expression *e2) {
	char *str = toLower(op4);
	basic_type type1 = check_expression(e1);
	basic_type type2 = check_expression(e2);
	
	if (strcmp(str, "mod") == 0 || strcmp(str, "div") == 0) {
		if (type1 == arrayB || type1 == arrayI || type1 == arrayR || type2 == arrayB || type2 == arrayI || type2 == arrayR) {
			printf("Incompatible type (got array, required integer)\n");
			exit(0);
		}
		
		if (type1 == integer && type2 == integer) {
			return integer;
		} else {
			printf("Operator %s cannot be applied to types %s, %s\n", op4, typeToString(type1), typeToString(type2));
			exit(0);
		}
	}
	
	else {
		if (type1 == arrayB || type1 == arrayI || type1 == arrayR || type2 == arrayB || type2 == arrayI || type2 == arrayR) {
			printf("Incompatible type (got array, required boolean or integer or real)\n");
			exit(0);
		}
		
		if (type1 == integer) {
			if (type2 != integer && type2 != real) {
				printf("Operator %s cannot be applied to types %s, %s\n", op4, typeToString(type1), typeToString(type2));
				exit(0);
			} else if (strcmp(str, "/") == 0)
				return real;
			else
				return type2;
		}
		
		if (type1 == real) {
			if (type2 != integer && type2 != real) {
				printf("Operator %s cannot be applied to types %s, %s\n", op4, typeToString(type1), typeToString(type2));
				exit(0);
			} else if (strcmp(str, "/") == 0)
				return real;
			else
				return type1;
		}
		
		if (type1 == boolean && type2 != boolean) {
			printf("Operator %s cannot be applied to types %s, %s\n", op4, typeToString(type1), typeToString(type2));
			exit(0);
		} else if (type1 == boolean && type2 == boolean)
			return boolean;
		
		printf("Operator %s cannot be applied to types %s, %s\n", op4, typeToString(type1), typeToString(type2));
		exit(0);
	}
}

/* start */
void check_start(is_start *s) {

	table_element *aux, *aux2;

	global_offset = 0;
	pe = (prog_env *) malloc(sizeof(prog_env));
	
	pe->global= create_symbol(global_offset++, "integer", reservedID, 0);
	aux = pe->global;
	aux->next = create_symbol(global_offset++, "real", reservedID, 0);
	aux = aux->next;
	aux->next = create_symbol(global_offset++, "boolean", reservedID, 0);
	aux = aux->next;
	aux->next = create_symbol(global_offset++, "true", reservedID, 0);
	aux = aux->next;
	aux->next = create_symbol(global_offset++, "false", reservedID, 0);
	aux = aux->next;
	aux->next = create_symbol(global_offset++, "paramcount", integer, 0);
	aux = aux->next;
	
	aux2 = lookup(pe->global, s->id);
	if (aux2) {
		printf("Symbol %s already defined\n", aux2->name);
		exit(0);
	}
	else
		aux->next = create_symbol(global_offset++, s->id, program, 0);
	
	check_block(s->block);
}

void check_undefined_functions() {
	environment_list *aux;
	for (aux=pe->funcs; aux; aux=aux->next)
		if (!aux->defined) {
			printf("Function %s declared but not defined\n", aux->name);
			exit(0);
		}
}

/* block */
void check_block(is_block *b) {
	
	if (b->varDeclarationList)
		check_varDeclaration_list(b->varDeclarationList, globalScope, pe->global);

	if (b->functionDecOrDefList)
		check_functionDecOrDef_list(b->functionDecOrDefList);
	
	check_undefined_functions();
	
	if (b->statementList) {
		statTable = pe->global;
		check_statement_list(b->statementList);
	}
}

/* variableDeclarationList */
void check_varDeclaration_list(is_varDeclaration_list *vdl, scope s, table_element *table) {
	
	is_varDeclaration_list *aux;
	for(aux = vdl; aux != NULL; aux=aux->next)
		check_varDeclaration(aux->varDeclaration, s, table);
}

/* varDeclaration */
void check_varDeclaration(is_varDeclaration *vd, scope s, table_element *table) {
	
	basic_type t;
	table_element *te;
	
	t = check_type(vd->id, vd->disc_d == d_with ? 1 : 0);
	
	if (vd->disc_d == d_with)
		if (vd->digseq1 > vd->digseq2) {
			printf("First index cannot be greater than last index\n");
			exit(0);
		}
	
	is_id_list *aux;
	for(aux = vd->idList; aux; aux=aux->next) {
		te = lookup(table, aux->id);
		if (te) {
			printf("Symbol %s already defined\n", te->name);
			exit(0);
		}
		
		else {
			for (te=table; te->next; te=te->next);
			te->next = create_symbol((s == globalScope) ? global_offset++ : function_offset++, aux->id, t, 0);
		}
	}
	
	if (t == -1) {
		printf("Unknown type %s\n", vd->id);
		exit(0);
	}
}

/* functionDecOrDefList */
void check_functionDecOrDef_list(is_functionDecOrDef_list *fdodl) {
	
	is_functionDecOrDef_list *aux;
	for(aux = fdodl; aux; aux=aux->next) {
		if (aux->disc_d == d_functionDec)
			check_functionDeclaration(aux->data_functionDecOrDef_list.functionDeclaration);
		else
			check_functionDefinition(aux->data_functionDecOrDef_list.functionDefinition);
	}
}

/* functionDeclaration */
void check_functionDeclaration(is_functionDeclaration *fd) {

	check_functionHeading(fd->functionHeading, 0);
}

/* functionDefinition */
void check_functionDefinition(is_functionDefinition *fd) {

	/* check if there is already a declaration */
	environment_list *el;
	el = lookupFunction(fd->functionHeading->id1);
	
	if (el != NULL && !el->defined) {
		check_functionArgs(fd->functionHeading, el);
	} else
		check_functionHeading(fd->functionHeading, 1);
	
	el = lookupFunction(fd->functionHeading->id1);
	check_functionBlock(fd->functionBlock, el->locals);
}

void check_functionArgs(is_functionHeading *fh, environment_list *el) {

	int n1 = 0, n2 = 0;
	table_element *aux;
	is_formalArgs_list *aux2;
	is_id_list *aux3;
	
	for (aux=el->locals->next; aux; aux=aux->next)
		n1++;
		
	for (aux2 = fh->formalArgsList; aux2; aux2=aux2->next)
		for (aux3 = aux2->formalArgs->idList; aux3; aux3=aux3->next)
			n2++;
			
	if (n1 != n2) {
		printf("Incompatible number of formal arguments in function definition %s (got %d, required %d)\n", el->name, n2, n1);
		exit(0);
	}
	
	basic_type type;
	bool var1, var2;
	int n = 0;
	
	aux = el->locals;
	for (aux2 = fh->formalArgsList; aux2; aux2=aux2->next) {
	
		type = check_type(aux2->formalArgs->id, aux2->formalArgs->arrayOf);
		var1 = aux2->formalArgs->var;
		
		for (aux3 = aux2->formalArgs->idList; aux3; aux3=aux3->next) {
			aux = aux->next;
			n++;
			var2 = (aux->type == arrayB || aux->type == arrayI || aux->type == arrayR);
			
			if (var1 != var2) {
				printf("Incompatible passing of formal arg %d in function definition %s\n", n, el->name);
				exit(0);
			}
			
			if (strcmp(aux->name, aux3->id) != 0) {
				printf("Incompatible name in formal arg %d in function definition %s (got %s, required %s)\n", n, el->name, aux3->id, aux->name);
				exit(0);
			}
			
			if (type != aux->type) {
				printf("Incompatible type in formal arg %d in function definition %s (got %s, required %s)\n", n, el->name, typeToString2(type), typeToString2(aux->type));
				exit(0);
			}
		}
	}
	
	type = check_type(fh->id2, 0);
	if (el->returnType != type) {
		printf("Incompatible return type in function definition %s (got %s, required %s)\n", el->name, typeToString(type), typeToString(el->returnType));
		exit(0);
	}
	
	el->defined = 1;	
}

/* functionHeading */
void check_functionHeading(is_functionHeading *fh, char defined) {
	
	table_element *te;
	environment_list *el, *aux;
	basic_type returnType;
	function_offset = 0;
	
	te = lookup(pe->global, fh->id1);
	if (te) {
		printf("Symbol %s already defined\n", te->name);
		exit(0);
	}
	
	returnType = check_type(fh->id2, 0);
	if (returnType == -1) {
		printf("Unknown type %s\n", fh->id2);
		exit(0);
	}
	
	el = (environment_list *) malloc(sizeof(environment_list));
	
	for (te=pe->global; te->next; te=te->next);
	te->next = create_symbol(-1, fh->id1, function, 0);

	el->name = toLower(fh->id1);
	el->defined = defined;
	el->returnType = returnType;
	
	el->locals = (table_element *) malloc(sizeof(table_element));
	el->locals = create_symbol(function_offset++, fh->id1, returnType, 0);
	
	if (fh->formalArgsList)
		check_formalArgs_list(fh->formalArgsList, el->locals);
	
	if (pe->funcs) {
		for (aux=pe->funcs; aux->next; aux=aux->next);
		aux->next = el;
	} else
		pe->funcs = el;
	
}

/* formalArgsList */
void check_formalArgs_list(is_formalArgs_list *fal, table_element *table) {
		
	is_formalArgs_list *aux;
	for(aux = fal; aux; aux=aux->next)
		check_formalArgs(aux->formalArgs, table);
}

/* formalArgs */
void check_formalArgs(is_formalArgs *fa, table_element *table) {
	
	basic_type t;
	table_element *te;
	
	if (fa->var && !fa->arrayOf) {
		printf("Non-array parameters must be passed by value\n");
		exit(0);
	}
	
	if (!fa->var && fa->arrayOf) {
		printf("Array parameters must be passed by reference\n");
		exit(0);
	}
	
	t = check_type(fa->id, fa->arrayOf);
	
	is_id_list *aux;
	for(aux = fa->idList; aux; aux=aux->next) {
		te = lookup(table, aux->id);
		if (te) {
			printf("Symbol %s already defined\n", te->name);
			exit(0);
		}
		
		else {
			for (te=table; te->next; te=te->next);
			te->next = create_symbol(function_offset++, aux->id, t, 1);
		}
	}
	
	if (t == -1) {
		printf("Unknown type %s\n", fa->id);
		exit(0);
	}
}

/* functionBlock */
void check_functionBlock(is_functionBlock *fb, table_element *table) {

	if (fb->varDeclarationList)
		check_varDeclaration_list(fb->varDeclarationList, localScope, table);
	
	if (fb->statementList) {
		statTable = table;
		check_statement_list(fb->statementList);
	}
}

/* statementList */
void check_statement_list(is_statement_list *sl) {
	
	is_statement_list *aux;
	for(aux = sl; aux != NULL; aux=aux->next) {
		check_statement(aux->statement);
	}
}

/* statement */
void check_statement(is_statement *s) {
	
	if (s) {
		switch (s->disc_d) {
			case d_beginEnd:
				check_beginEnd(s->data_statement.beginEnd);
				break;
			
			case d_assignExp:
				check_assignExp(s->data_statement.assignExp);
				break;
			
			case d_ifThen:
				check_ifThen(s->data_statement.ifThen);
				break;
				
			case d_whileDo:
				check_whileDo(s->data_statement.whileDo);
				break;
				
			case d_for:
				check_for(s->data_statement.for2);
				break;
				
			case d_valParamstr:
				check_valParamstr(s->data_statement.valParamstr);
				break;
				
			case d_writeln:
				check_writeln(s->data_statement.writeln);
				break;
		}
	}
}

/* beginEnd */
void check_beginEnd(is_beginEnd *be) {
	if(be->statementList)
		check_statement_list(be->statementList);
}

/* assignExp */
void check_assignExp(is_assignExp *ae) {
	
	basic_type type;
	table_element *te = lookup(statTable, ae->id);
	if (!te) {
		te = lookup(pe->global, ae->id);
		if (!te) {			
			printf("Symbol %s not defined\n", ae->id);
			exit(0);
		}
	}

	if (ae->expression1) {
		if (!(te->type == arrayB || te->type == arrayI || te->type == arrayR)) {
			printf("Incompatible type (got %s, required array)\n", typeToString(te->type));
			exit(0);
		}
		
		type = check_expression(ae->expression1);
		if (type != integer) {
			printf("Incompatible type (got %s, required integer)\n", typeToString(type));
			exit(0);
		}
		
	} else if (te->type == arrayB || te->type == arrayI || te->type == arrayR) {
		printf("Cannot assign to type array\n");
		exit(0);
	}
	
	if (te->type == function || te->type == program || te->type == reservedID) {
		printf("Cannot assign to type %s\n", typeToString(te->type));
		exit(0);
	}
	
	type = check_expression(ae->expression2);
	if (ae->expression1) {
		if (te->type == arrayI && type != integer) {
			printf("Incompatible type (got %s, required integer)\n", typeToString(type));
			exit(0);
		}
		
		if (te->type == arrayR && type != integer && type != real) {
			printf("Incompatible type (got %s, required real)\n", typeToString(type));
			exit(0);
		}
		
		if (te->type == arrayB && type != boolean) {
			printf("Incompatible type (got %s, required boolean)\n", typeToString(type));
			exit(0);
		}
	}
	else if (te->type != type && !(te->type == real && type == integer)) {
		printf("Incompatible type (got %s, required %s)\n", typeToString(type), typeToString(te->type));
		exit(0);
	}
}

/* ifThen */
void check_ifThen(is_ifThen *ae) {
	basic_type type = check_expression(ae->expression);
	
	if (type != boolean) {
		printf("Incompatible type (got %s, required boolean)\n", typeToString(type));
		exit(0);
	}
	
	check_statement(ae->ifStatement);
	if (ae->iselse)
		check_statement(ae->elseStatement);
}

/* whileDo */
void check_whileDo(is_whileDo *wd) {
	
	basic_type type = check_expression(wd->expression);
	
	if (type != boolean) {
		printf("Incompatible type (got %s, required boolean)\n", typeToString(type));
		exit(0);
	}
	
	check_statement(wd->statement);

}

/* for */
void check_for(is_for *f) {
	
	basic_type type;
	table_element *te = lookup(statTable, f->id);
	if (!te) {
		te = lookup(pe->global, f->id);
		if (!te) {			
			printf("Symbol %s not defined\n", f->id);
			exit(0);
		}
	}
	
	if (te->type != integer) {
		printf("Incompatible type (got %s, required integer)\n", typeToString(te->type));
		exit(0);
	}
	
	type = check_expression(f->expression1);
	if (type != integer) {
		printf("Incompatible type (got %s, required integer)\n", typeToString(type));
		exit(0);
	}
	
	type = check_expression(f->expression2);
	if (type != integer) {
		printf("Incompatible type (got %s, required integer)\n", typeToString(type));
		exit(0);
	}
	
	check_statement(f->statement);
}

/* valParamstr */
void check_valParamstr(is_valParamstr *vp) {
	basic_type type = check_expression(vp->expression);
	if (type != integer) {
		printf("Incompatible type (got %s, required integer)\n", typeToString(type));
		exit(0);
	}
	
	table_element *te = lookup(statTable, vp->id);
	if (!te) {
		te = lookup(pe->global, vp->id);
		if (!te) {		
			printf("Symbol %s not defined\n", vp->id);
			exit(0);
		}
	}
	
	if (te->type != integer && te->type != real) {
		printf("Incompatible type (got %s, required integer or real)\n", typeToString(te->type));
		exit(0);
	}
}

/* writeln */
void check_writeln(is_writeln *w) {
	basic_type type = check_expression(w->expression);
	if (type != integer && type != real && type != boolean) {
		printf("Incompatible type (got %s, required boolean or integer or real)\n", typeToString(type));
		exit(0);
	}
}

/* expression */
basic_type check_expression(is_expression *e) {
	switch (e->disc_d) {
		case d_operators:
			return check_operators(e->data_expression.operators);
		
		case d_numberExp:
			return check_numberExp(e->data_expression.numberExp);
			
		case d_arrayExp:
			return check_arrayExp(e->data_expression.arrayExp);
		
		case d_notExp:
			return check_notExp(e->data_expression.notExp);
			
		case d_funcExp:
			return check_funcExp(e->data_expression.funcExp);
	}
}

/* operators */
basic_type check_operators(is_operators *op) {
	switch (op->disc_d) {
		case d_op1:
			return check_op1(op->data_operators.op1, op->expression1, op->expression2);
			
		case d_op2:
			return check_op2(op->data_operators.op1, op->expression1, op->expression2);
			
		case d_op3:
			return check_op3(op->data_operators.op1, op->expression1, op->expression2);
			
		case d_op4:
			return check_op4(op->data_operators.op1, op->expression1, op->expression2);
	}
}

/* numberExp */
basic_type check_numberExp(is_numberExp *ne) {
	return ne->disc_d == d_digseq ? integer : real;
}

/* arrayExp */
basic_type check_arrayExp(is_arrayExp *ae) {
	
	basic_type type;
	table_element *te = lookup(statTable, ae->id);
	if (!te) {
		te = lookup(pe->global, ae->id);
		if (!te) {		
			printf("Symbol %s not defined\n", ae->id);
			exit(0);
		}
	}
	
	if (ae->expression) {
		if (te->type != arrayB && te->type != arrayI && te->type != arrayR) {
			printf("Incompatible type (got %s, required array)\n", typeToString(te->type));
			exit(0);
		}
		
		type = check_expression(ae->expression);
		if (type != integer) {
			printf("Incompatible type (got %s, required integer)\n", typeToString(type));
			exit(0);
		}
	}

	char *str2 = toLower(ae->id);
	if (strcmp(str2, "true") == 0 || strcmp(str2, "false") == 0) {
		free(str2);
		return boolean;
	}
	free(str2);
	
	if (ae->expression) {
		if (te->type == arrayB)
			return boolean;
		if (te->type == arrayI)
			return integer;
		if (te->type == arrayR)
			return real;
	}
	
	return te->type;
}

/* notExp */
basic_type check_notExp(is_notExp *ne) {
	basic_type type = check_expression(ne->expression);
	if (type != boolean) {
		printf("Operator not cannot be applied to type %s\n", typeToString(type));
		exit(0);
	}
	return type;
}

/* funcExp */
basic_type check_funcExp(is_funcExp *fe) {
	
	table_element *te = lookup(pe->global, fe->id);
	if (!te) {			
		printf("Symbol %s not defined\n", fe->id);
		exit(0);
	}
	
	if (te != NULL && te->type != function) {
		printf("Cannot call %s\n", fe->id);
		exit(0);
	}
	
	environment_list *el = lookupFunction(fe->id);
	if (fe->expressionList, el)
		check_expression_list(fe->expressionList, el);

	return el->returnType;
}

/* expressionList */
void check_expression_list(is_expression_list *elist, environment_list *el) {
	basic_type type;
	is_expression_list *aux;
	table_element *te;
	int n = 0, n1 = 0, n2 = 0;
	
	for (aux = elist; aux; aux=aux->next)
		n1++;
		
	for (te = el->locals->next; te; te=te->next)
		if (te->param)
			n2++;
		else
			break;
		
	if (n1 != n2) {
		printf("Incompatible number of parameters in call to function %s (got %d, required %d)\n", el->name, n1, n2);
		exit(0);
	}
	
	for (aux = elist, te = el->locals->next; aux; aux=aux->next, te = te->next) {
		n++;
		type = check_expression(aux->expression);
		
		if (te->type == real && type == integer)
			continue;
		
		if (type != te->type) {
			printf("Incompatible type of parameter %d in call to function %s (got %s, required %s)\n", n, el->name, typeToString(type), typeToString(te->type));
			exit(0);
		}
	}
}

/* auxiliares */
/* Criação de uma estrutura table_element */
table_element *create_symbol(int offset, is_ID name, basic_type type, char param) {
	
	table_element *tel = (table_element *) malloc(sizeof(table_element));
	
	tel->name = toLower(name);
	tel->type = type;
	tel->next = NULL;
	tel->offset = offset;
	tel->param = param;
	
	return tel;
}

/* Procura um identificador, devolve null caso nao exista */
table_element *lookup(table_element *table, char *str)
{
	table_element *aux;
	char *str2 = toLower(str);
	
	for (aux=table; aux; aux=aux->next)
		if (strcmp(aux->name, str2) == 0) {
			free(str2);
			return aux;
		}
	
	free(str2);
	return NULL;
}

environment_list *lookupFunction(char *str) {
	environment_list *aux;
	char *str2 = toLower(str);
	
	for (aux=pe->funcs; aux; aux=aux->next) {
		if (strcmp(aux->name, str2) == 0) {
			free(str2);
			return aux;
		}
	}
	
	free(str2);
	return NULL;
}
