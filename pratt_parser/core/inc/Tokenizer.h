#pragma once
//typedef struct {
//	char* str;
//	char* origin;
//	char*  source;
//	int len;
//} Token;
typedef struct {
	int pos;
	int token_count;
	char** tokens;
}TokenStream;
char* next(TokenStream* tokens);
char* peek(TokenStream* tokens);
int has_next(TokenStream* tokens);
TokenStream tokenize(char* source,char* tokens_string);
void print_all(TokenStream tokens);

TokenStream tokenize_by(TokenStream source, char* token, int discard_token, TokenStream all_tokens);

TokenStream new_TokenStream(void);
void push(TokenStream* iter, char* token);
//token_iter tokenise(char* source,char* tokens);