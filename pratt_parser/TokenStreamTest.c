#include "TestRunner.h"
#include "Tokenizer.h"
#include "util.h"

void add_many() {
	name(__func__);
	TokenStream stream = new_TokenStream();
	char buffer[100];
	int i = 1000;
	while(i-->0)
		push(&stream,copy_string(itoa(i,buffer,10)));
	i = 1000;
	while (has_next(&stream))
		assert(equals_string, copy_string(itoa(i--, buffer, 10)));
}
void size_test() {
	name(__func__);
	TokenStream stream = new_TokenStream();
	char buffer[100];
	int i = 1000;
	while (i-- > 0)
		push(&stream, copy_string(itoa(i, buffer, 10)));
	assert(equals_int, stream.token_count, 1000);
}

void tests_TokenStream() {
	register_tests(add_many);
	
}