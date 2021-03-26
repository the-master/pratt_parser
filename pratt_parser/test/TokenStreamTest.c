#include <stdlib.h>
#include "TestCollector.h"
#include "Tokenizer.h"
#include "util.h"
static void read_and_write_onethousand(void) {
	name_test();
	TokenStream stream = new_TokenStream();
	char buffer[100];
	int i = 1000;
	while(i-->0)
		push(&stream,copy_string(_itoa(i,buffer,10)));
	i = 1000;
	while (has_next(&stream))
		assert(equals_string,next(&stream), copy_string(_itoa(i--, buffer, 10)));
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



void tests_TokenStream(void) {
	register_tests(&read_and_write_onethousand, &size_test);
	
}