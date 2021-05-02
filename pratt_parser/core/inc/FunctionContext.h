#pragma once
#include "Tokenizer.h"
#include "FileParser.h"
#include "FileParser.h"
typedef struct {
	TokenStream keys;
	TokenStream values;
}FunctionContext;

FunctionContext* new_function_context(void);
CCFunction* get_function(FunctionContext* context, char* key);
CCFunction* set_function(FunctionContext* context, char* key,CCFunction* fun);
int has_function(FunctionContext* context, char* key);
//int set_value(FunctionContext* con, char* key, int val);
//void print_context(FunctionContext* c);