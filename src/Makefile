all:
	@lex SmallPascalCompiler.l;
	@yacc -d SmallPascalCompiler.y;
	@cc -o SmallPascalCompiler y.tab.c lex.yy.c functions.c translate.c semantic.c -ll -ly -lm;
	@rm y.tab.h y.tab.c lex.yy.c
	@echo executable file "SmallPascalCompiler" has been successfully created!
