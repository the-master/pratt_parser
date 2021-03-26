#include <stdlib.h>
#include "TestCollector.h"
#include "Tokenizer.h"
#include "util.h"
static void add_many(void) {
	name_test();
	TokenStream stream = new_TokenStream();
	char buffer[100];
	int i = 1000;
	while(i-->0)
		push(&stream,copy_string(_itoa(i,buffer,10)));
	i = 1000;
	//while (has_next(&stream))
	//	assert(equals_string,2,next(&stream), copy_string(itoa(i--, buffer, 10)));
	assert(equals_int, 3, 4);
}
static void size_test(void) {
	name_test();
	TokenStream stream = new_TokenStream();
	char buffer[100];
	int i = 1000;
	while (i-- > 0)
		push(&stream, copy_string(_itoa(i, buffer, 10)));
	assert(equals_int, stream.token_count, 1000);
}

static void size_test2(void) {
	name_test();
	TokenStream stream = new_TokenStream();
	char buffer[100];
	int i = 1000;
	while (i-- > 0)
		push(&stream, copy_string(_itoa(i, buffer, 10)));
	assert(equals_int,stream.token_count, 1000+1);
}

void tests_TokenStream(void) {
	register_tests(&add_many, &size_test,&size_test2);
	
}