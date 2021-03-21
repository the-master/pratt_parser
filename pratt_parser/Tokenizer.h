#pragma once
typedef struct {
	int pos;
	int token_count;
	char** tokens;
}TokenStream;
char* next(TokenStream* tokens);
char* peek(TokenStream* tokens);
int has_next(TokenStream* tokens);
TokenStream tokenize(char* source);
void print_all(TokenStream tokens);
//token_iter tokenise(char* source,char* tokens);