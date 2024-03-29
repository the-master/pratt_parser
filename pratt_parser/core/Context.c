#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Tokenizer.h"
#include "Context.h"
#include "util.h"
//UGLY MAP implementation
//char* to int
Context* new_context(void) {
	Context* rv = exit_on_null( malloc( sizeof(Context)));
	rv->keys = new_TokenStream();
	rv->values = new_TokenStream();
	rv->functions = new_function_context();
	rv->up = 0;
	rv->alive = 1;
	rv->result = (value_container){ int_b, -333 };
	return rv;
}
value_container get_value(Context* context, char* key) {
	//if (context->up)
	//	return get_value((Context*)context->up, key);
	//printf("lookiing up  %s :\n", key);
	TokenStream keys = context->keys;
	TokenStream values = context->values;
	while (has_next(&keys)) {
		char* current_key = next(&keys);
		next(&values);
		if (strcmp(key, current_key) == 0)
 			return *(value_container*)values.tokens[values.pos - 1];
	}
	//print_context(context);
	return (value_container) { int_b, -333 };
}

int has_key(Context* context, char* key) {
	TokenStream keys = context->keys;
	while (has_next(&keys)) {
		char* current_key = next(&keys);
		if (strcmp(key, current_key) == 0)
			return 1;
	}
	return 0;
}

value_container set_value(Context* con, char* key, value_container val) {
	TokenStream keys = con->keys;
	TokenStream values = con->values;
	//printf("assigning %i to %s\n", val, key);
	while (has_next(&keys)) {
		char* current_key = next(&keys);
		next(&values);
		if (strcmp(key, current_key) == 0)
			return  *((value_container*)values.tokens[values.pos - 1]) =  val;
	}
	push(&con->keys, key);
	value_container* V = malloc(sizeof(value_container));
	*V = val;
	push(&con->values, (char*)V);
	return val;
}

void print_context(Context* c) {
	TokenStream keys = c->keys;
	TokenStream values = c->values;
	while (has_next(&keys)) {
		printf("%s: %i\n", next(&keys), ((value_container*)next(&values))->i);
	}
}

int has_fun(Context* context,char*key) {
	return has_function(context->functions, key);
}
void add_fun(Context* context, char* key, CCFunction* f) {
	set_function(context->functions, key, f);
}
CCFunction* get_fun(Context* context, char* key) {
	return get_function(context->functions, key);
}
