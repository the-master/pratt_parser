#include "Operators.h"
#include "Testing.h"
#include "TestCollector.h"
#include "repl.h"

//#define _CRT_SECURE_NO_WARNINGS 1
/*
todo:	split tokenicer.c => tokenizer.c & stream.c
		tests[eval]  [parser][context][ast]

		add 
		  *if
		  *while 
		  *array
		  *types
		  * function
		code coverage
*/
int main(void) {
	init_operator_module();
	prepare_tests();
	//run_tests();
	repl();
	return 1;
}
