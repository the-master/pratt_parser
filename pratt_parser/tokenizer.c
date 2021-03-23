
#include "Tokenizer.h"
#include "util.h"

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
TokenStream new_TokenStream() {
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
	TokenStream rv = new_TokenStream();
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
contains_token(TokenStream all_tokens,char* str) {
	while (has_next(&all_tokens)) {
		if (strcmp(next(&all_tokens), str) == 0)
			return 1;
	}
	return 0;
}
 TokenStream tokenize_by(TokenStream source, char* token,int discard_token,TokenStream all_tokens) {
	TokenStream rv = new_TokenStream();
	int keep_token;
	while (has_next(&source)) {
		char* source_str = next(&source);
		if (contains_token(all_tokens, source_str)){
			push(&rv, source_str);
			continue;
		}
		int source_length = strlen(source_str);
		char* location;
		char* probe = source_str;
		while (location = index_of(probe, token)) {
			*location = 0;
			if (*probe)
				push(&rv, copy_string(probe));
			if (!discard_token)
				push(&rv, copy_string(token));

			probe = location + strlen(token);
		}
		if(strlen(probe))
			push(&rv, copy_string(probe));
	}
	return rv;
}

 TokenStream tokenise2(TokenStream input, TokenStream tokens) {
	 TokenStream rv = input;
	 TokenStream all_tokens = tokens;
	 while (has_next(&tokens)) {
		 //print_all(rv),printf("\n");
		 rv = tokenize_by(rv, next(&tokens),0,all_tokens);
		/* printf("\n");
		 print_all(rv), printf("\n");*/
	 }
	 return rv;
 }
 TokenStream scrub_spaces(TokenStream tokens)
 {
	 return tokenize_by(tokens,copy_string(" "), 1,new_TokenStream());
 }
 TokenStream tokenize(char* input, char* tokens_string) {
	 TokenStream temp = new_TokenStream();
	 push(&temp, input);

	 temp = scrub_spaces(temp);

	 TokenStream tokens = tokenise(tokens_string);
	 return tokenise2(temp, tokens);
 }
