#ifndef _FRAME_
#define _FRAME_

typedef struct _frame {
	struct _frame* 	parent;		/* frame pointer - ambiente da função chamante */
	void* 		locals[64];		/* espaço de endereçamento para variáveis locais */
	void* 	  outgoing[32];		/* espaço de endereçamento para argumentos de funções chamadas */
	void*	    temp[1024];
	void*	   returnValue;
	int 	return_address;		/* endereço do código na função chamante */
} frame;

#endif
