

#include <stdio.h>
#include <stdlib.h>
#include "Operators.h"
#include "Testing.h"
#include "TestCollector.h"
#include "FileParser.h"
#include "Context.h"
#define _CRT_SECURE_NO_WARNINGS 1
#define Xabra float
#include "Source.h"
//allows itoa
/*
todo:	split tokenicer.c => tokenizer.c & stream.c

		add 
		  *types
		  *array
		  *function		done
		  *structs
		code coverage

*/
int main(void) {
	//printf("blub %i \n",f(3,4));
	init_operator_module();
	repl2("C:\\Users\\joosw\\Desktop\\blub.cc");
	char* buffer = malloc(100000);
	//print_to_buffer_as_c_file("C:\\Users\\joosw\\Desktop\\blub.cc", buffer);


	prepare_tests();
//	run_tests();
	return 1;
}
