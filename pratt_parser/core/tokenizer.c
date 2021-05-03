
#include "Tokenizer.h"
#include "util.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
char* next(TokenStream* tokens) {
	if (has_next(tokens))
		return tokens->tokens[tokens->pos++];
	else
		return tokens->tokens[tokens->pos-1];
}

char* peek(TokenStream* tokens) { return tokens->tokens[tokens->pos<tokens->token_count?tokens->pos:tokens->pos-1]; }

char* index_of(char* haystack, char* needle) {
	return strstr(haystack, needle);
}
int has_next(TokenStream* tokens) { return tokens->pos < tokens->token_count; }
TokenStream new_TokenStream(void) {
	TokenStream rv;
	rv.pos = 0;
	rv.token_count = 0;
	rv.tokens = malloc(0);//allows for realloc later
	return rv;
}
char** fsd(TokenStream* iter) {
	char** rv = realloc(iter->tokens, iter->token_count * sizeof(char*));
	if (rv)
		return rv;
	else
		return iter->tokens;

}
void push(TokenStream* iter, char* token) {
	iter->token_count++;
	iter->tokens = fsd(iter);
	iter->tokens[iter->token_count - 1] = token;
}
TokenStream tokenise(char* source) {
	TokenStream rv = new_TokenStream();
	char* token = strtok(source, " ");
	do {
		 push(&rv,copy_string(token));
		 token = strtok(0, " ");
	} while (token != 0);
	return rv;
}
void print_all(TokenStream tokens) {
	while (has_next(&tokens))
		printf("%s, ",next(&tokens));
}
int contains_token(TokenStream all_tokens,char* str) {
	while (has_next(&all_tokens)) {
		if (strcmp(next(&all_tokens), str) == 0)
			return 1;
	}
	return 0;
}
 TokenStream tokenize_by(TokenStream source, char* token,int discard_token,TokenStream all_tokens) {
	TokenStream rv = new_TokenStream();
	while (has_next(&source)) {
		char* source_str = next(&source);
		if (contains_token(all_tokens, source_str)){
			push(&rv, source_str);
			continue;
		}
		char* location;
		char* probe = source_str;
		location = index_of(probe, token);
		while (location != 0) {
			*location = 0;
			if (*probe)
				push(&rv, copy_string(probe));
			if (!discard_token)
				push(&rv, copy_string(token));

			probe = location + strlen(token);
			location = index_of(probe, token);
		}
		if(strlen(probe))
			push(&rv, copy_string(probe));
	}
	return rv;
}
 TokenStream filter_by_lenght(TokenStream input,int len) {
	 TokenStream rv = new_TokenStream();
	 char* temp;
	 while(has_next(&input))
		 if(strlen(temp=next(&input) )== len)
			 push(&rv,temp);
	 return rv;
 }
 TokenStream tokenise2(TokenStream input, TokenStream tokens) {
	 TokenStream rv = input;
	 TokenStream all_tokens = tokens;
	 for (int i = 5; i > 0; i--) {


		  TokenStream my_tokens = filter_by_lenght(tokens,i);
		 while (has_next(&my_tokens)) {
			 //print_all(rv),printf("\n");
			 rv = tokenize_by(rv, next(&my_tokens), 0, all_tokens);
			 /* printf("\n");
			  print_all(rv), printf("\n");*/
		 }
	 }
	 return rv;
 }
 TokenStream scrub_spaces(TokenStream tokens)
 {
	 return tokenize_by(tokens,copy_string(" "), 1,new_TokenStream());
 }
 TokenStream stitch_minus(TokenStream tokenized,TokenStream all_tokens) {
	 TokenStream rv = new_TokenStream();
	 char* prev = 0;
	 while (has_next(&tokenized)){
		 char* current = next(&tokenized);
		 if (current == 0) {
			 printf("\n something unexpected happened during tokenization\n");
			continue;
		 }
		 if (strcmp(current, "-") == 0 && (prev == 0 || contains_token(all_tokens, prev))) {
			 char* next_token = next(&tokenized);
			 char buff[100];
			 buff[0] = 0;
			 strcat(buff, current);
			 strcat(buff, next_token);
			 push(&rv,copy_string(buff));
		 }
		 else {
			 push(&rv, copy_string(current));
		 }
		 prev = current;
	 }

	 return rv;
 }
 TokenStream stitch_function_brace(TokenStream tokenized,  TokenStream all_tokens) {
	 TokenStream rv = new_TokenStream();
	 while (has_next(&tokenized)) {
		 char* current = next(&tokenized);
		 if (current == 0) {
			 printf("\n something unexpected happened during tokenization\n");
			 continue;
		 }
		 if(!contains_token(all_tokens, current) && !is_number(current)&& *peek(&tokenized)=='('){
			 char* next_token = next(&tokenized);
			 char buff[100];
			 buff[0] = 0;
			 strcat(buff, current);
			 strcat(buff, next_token);
			 push(&rv, copy_string(buff));
		 } else
			push(&rv, copy_string(current));

	 }

	 return rv;
 }
 TokenStream tokenize(char* input, char* tokens_string) {
	 TokenStream temp = new_TokenStream();
	 push(&temp, input);

	 temp = scrub_spaces(temp);

	 TokenStream tokens = tokenise(tokens_string);
	 TokenStream tokenized= tokenise2(temp, tokens);
	 return stitch_function_brace(stitch_minus(tokenized, tokens) , tokens);
 }
