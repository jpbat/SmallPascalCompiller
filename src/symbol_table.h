#ifndef _SYMBOL_TABLE_
#define _SYMBOL_TABLE_

typedef enum {integer, real, boolean, arrayI, arrayR, arrayB, reservedID, function, program} basic_type;

/*lista ligada de simbolos - um ambiente/registo de activação*/
typedef struct _table_element {
	basic_type	type;	
	char 		*name;
	int 		offset;		/*futura posição na frame, caso seja uma variavel -1, se for uma procedure.*/
	char		param;

	struct _table_element *next;
} table_element;


/*lista de funcoes definidos no programa*/
typedef struct _environment_list {
	char			*name;
	table_element	*locals;
	char			defined;
	basic_type		returnType;
	
	struct _environment_list *next;
} environment_list;

/*Estrutura que guarda TODOS os simbolos de um programa: o ambiente "global" e a lista de ambientes*/
typedef struct _prog_env {
	table_element		*global;
	environment_list	*funcs;
} prog_env;

#endif
