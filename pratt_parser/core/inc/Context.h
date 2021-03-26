#pragma once
#include "Tokenizer.h"
typedef struct {
	TokenStream keys;
	TokenStream values;
}Context;

Context* new_context(void);
int get_value(Context* context, char* key);
int has_key(Context* context, char* key);
int set_value(Context* con, char* key, int val);
void print_context(Context* c);