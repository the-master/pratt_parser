#pragma once
#include "Tokenizer.h"
#include "FunctionContext.h"
typedef struct {
	TokenStream keys;
	TokenStream values;
	FunctionContext* functions;
	void* up;
}Context;

Context* new_context(void);
void add_fun(Context* context, char* key, CCFunction* f);
int has_fun(Context* context, char* key);
CCFunction* get_fun(Context* context, char* key);
int get_value(Context* context, char* key);
int has_key(Context* context, char* key);
int set_value(Context* con, char* key, int val);
void print_context(Context* c);