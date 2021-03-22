
#include "Tokenizer.h"
char* copy_string2(char* str) { return strcpy(malloc((strlen(str) + 1) * sizeof(char)), str); }

char* next(TokenStream* tokens) {
	if (has_next(tokens))
		return tokens->tokens[tokens->pos++];
	else
		return tokens->tokens[tokens->pos];
}

char* peek(TokenStream* tokens) { return tokens->tokens[tokens->pos]; }
char* index_of(char* haystack, char* needle) {
	return strstr(haystack, needle);
}
int has_next(TokenStream* tokens) { return tokens->pos < tokens->token_count; }
TokenStream new_token_iter() {
	TokenStream rv;
	rv.pos = 0;
	rv.token_count = 0;
	rv.tokens = malloc(0);
	return rv;
}
push(TokenStream* iter, char* token) {
	iter->token_count++;
	iter->tokens = realloc(iter->tokens, iter->token_count * sizeof(char*));
	iter->tokens[iter->token_count - 1] = token;
}
TokenStream tokenise(char* source) {
	TokenStream rv = new_token_iter();
	char* token = strtok(source, " ");
	do {
		 push(&rv,copy_string(token));
	} while (token = strtok(0, " "));
	return rv;
}
void print_all(TokenStream tokens) {
	while (has_next(&tokens))
		printf("%s, ",next(&tokens));
}
int final_tok(int source_length, char* source_str, char* left_token) {
	return	 source_length == (left_token - source_str) + strlen(left_token);
}
 TokenStream tokenize_by(TokenStream source, char* token,int discard_token) {
	TokenStream rv = new_token_iter();
	int keep_token;
	while (has_next(&source)) {
		char* source_str = next(&source);
		int source_length = strlen(source_str);
		char* location;
		char* finder = source_str;
		while (location = index_of(finder, token)) {
			*location = 0;
			if (*finder)
				push(&rv, copy_string(finder));
			if (!discard_token)
				push(&rv, copy_string(token));

			finder = location + strlen(token);
		}
		if(strlen(finder))
			push(&rv, copy_string(finder));
	}
	return rv;
}

 TokenStream tokenise2(TokenStream input, TokenStream tokens) {
	 TokenStream rv = input;
	 while (has_next(&tokens)) {
		 print_all(rv),printf("\n");
		 rv = tokenize_by(rv, next(&tokens),0);
		 printf("\n");
		 print_all(rv), printf("\n");
	 }
	 return rv;
 }
 TokenStream scrub_spaces(TokenStream tokens)
 {
	 return tokenize_by(tokens,copy_string2(" "), 1);
 }
 TokenStream tokenize(char* input, char* tokens_string) {
	 TokenStream temp = new_token_iter();
	 push(&temp, input);

	 temp = scrub_spaces(temp);

	 TokenStream tokens = tokenise(tokens_string);
	 return tokenise2(temp, tokens);
 }
