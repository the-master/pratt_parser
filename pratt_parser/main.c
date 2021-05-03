
#include <stdio.h>
#include "Operators.h"
#include "Testing.h"
#include "TestCollector.h"
#include "FileParser.h"
#include "Context.h"
//allows itoa
#define _CRT_SECURE_NO_WARNINGS 1
/*
todo:	split tokenicer.c => tokenizer.c & stream.c

		add 
		  *types
		  *array
		  *function
		  *structs
		code coverage

*/
int main(void) {
	init_operator_module();
	repl2("C:\\Users\\Suus\\Desktop\\Dieter\\muhlang\\blub.cc");



	prepare_tests();
	run_tests();
	//repl();
	return 1;
}
