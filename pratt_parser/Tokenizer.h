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

TokenStream tokenize_by(TokenStream source, char* token, int discard_token, TokenStream all_tokens);

TokenStream new_TokenStream();
push(TokenStream* iter, char* token);
//token_iter tokenise(char* source,char* tokens);