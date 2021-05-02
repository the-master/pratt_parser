#include <string.h>
#include "FunctionContext.h"
#include "Tokenizer.h"

FunctionContext* new_function_context(void) {
	FunctionContext* rv = malloc(sizeof(FunctionContext));
	rv->keys = new_TokenStream();
	rv->values = new_TokenStream();
	return rv;
}
CCFunction* get_function(FunctionContext* context, char* key) {

	TokenStream keys = context->keys;
	TokenStream values = context->values;
	while (has_next(&keys)) {
		char* current_key = next(&keys);
		next(&values);
		if (strcmp(key, current_key) == 0)
			return (CCFunction*)values.tokens[values.pos - 1];
	}
	return 0;
}
int has_function(FunctionContext* context, char* key) {
	TokenStream keys = context->keys;
	while (has_next(&keys)) {
		char* current_key = next(&keys);
		if (strcmp(key, current_key) == 0)
			return 1;
	}
	return 0;
}

CCFunction* set_function(FunctionContext* con, char* key, CCFunction* val) {
	TokenStream keys = con->keys;
	TokenStream values = con->values;

	while (has_next(&keys)) {
		char* current_key = next(&keys);
		next(&values);
		if (strcmp(key, current_key) == 0)
			return (CCFunction*)(values.tokens[values.pos - 1] = (char*)val);
	}
	push(&con->keys, key);
	push(&con->values, (char*)val);
	return val;
}






//int has_key(FunctionContext* context, char* key);
//int set_value(FunctionContext* con, char* key, int val);
//void print_context(FunctionContext* c);