#include "TestRunner.h"
#include "Tokenizer.h"
#include "util.h"

void add_many() {
	register_test(__func__);
	TokenStream stream = new_TokenStream();
	char buffer[100];
	int i = 1000;
	while(i-->0)
		push(&stream,copy_string(itoa(i,buffer,10)));
	i = 1000;
	//while (has_next(&stream))
	//	assert(equals_string,2,next(&stream), copy_string(itoa(i--, buffer, 10)));
	assert(equals_int, 3, 4);
}
void size_test() {
	register_test(__func__);
	TokenStream stream = new_TokenStream();
	char buffer[100];
	int i = 1000;
	while (i-- > 0)
		push(&stream, copy_string(itoa(i, buffer, 10)));
	assert(equals_int, stream.token_count, 1000);
}

void size_test2() {
	register_test(__func__);
	TokenStream stream = new_TokenStream();
	char buffer[100];
	int i = 1000;
	while (i-- > 0)
		push(&stream, copy_string(itoa(i, buffer, 10)));
	assert(equals_int,stream.token_count, 1000+1);
}

void tests_TokenStream() {
	register_tests(&add_many, &size_test,&size_test2);
	
}