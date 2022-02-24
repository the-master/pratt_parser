#pragma once
#include "Tokenizer.h"
#include "FunctionContext.h"
#include "basetype_operators.h"
typedef struct {
	TokenStream keys;
	TokenStream values;
	FunctionContext* functions;
	void* up;
	int alive;

	value_container result;
}Context;

Context* new_context(void);
void add_fun(Context* context, char* key, CCFunction* f);
int has_fun(Context* context, char* key);
CCFunction* get_fun(Context* context, char* key);
value_container get_value(Context* context, char* key);
int has_key(Context* context, char* key);
value_container set_value(Context* con, char* key, value_container value_container);
void print_context(Context* c);