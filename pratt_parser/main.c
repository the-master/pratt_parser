#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.h"
#include "Tokenizer.h"
#include "AbstractSyntaxTree.h"
#include "Operators.h"
#define _CRT_SECURE_NO_WARNINGS 1

char* copy_string(char* str) { return strcpy(malloc((strlen(str) + 1) * sizeof(char)), str); }






int eval_Ast(AbstractSyntaxTree* root) {
	switch (root->type)
	{
	case nud:
		return atoi(root->val);
	case led:
		switch ((int)root->val) {
		case	plus: return eval_Ast(root->left) + eval_Ast(root->right);
		case	multiply:  return eval_Ast(root->left) * eval_Ast(root->right);
		case	minus: return eval_Ast(root->left) - eval_Ast(root->right);
		case	divide:  return eval_Ast(root->left) / eval_Ast(root->right);
		case	less:  return eval_Ast(root->left) < eval_Ast(root->right);
		case	more:  return eval_Ast(root->left) > eval_Ast(root->right);
		case	equals:  return eval_Ast(root->left) == eval_Ast(root->right);
		case	assign: return eval_Ast(root->right);
		}

	}
}
typedef struct {
	TokenStream keys;
	TokenStream values;
}Context;
Context* new_context() {
	Context* rv = malloc(sizeof(Context));
	rv->keys = new_token_iter();
	rv->values= new_token_iter();
	return rv;
}
get_value(Context* context, char* key) {
	TokenStream keys = context->keys;
	TokenStream values = context->values;
	while (has_next(&keys)) {
		char* current_key = next(&keys);
		next(&values);
		if (strcmp(key, current_key) == 0)
			return values.tokens[values.pos-1];
	}
}
int set_value(Context* con,char* key, int val) {
	TokenStream keys = con->keys;
	TokenStream values= con->keys;

	while (has_next(&keys)) {
		char* current_key = next(&keys);
		 next(&values);
		 if (strcmp(key, current_key) == 0)
			return (int)values.tokens[values.pos-1] = (char*)val;
	}
	push(&con->keys, key);
	push(&con->values,(char*) val);

}

//int eval_Ast2(AbstractSyntaxTree* root,Context* context) {
//	switch (root->type)
//	{
//	case nud:
//		if (is_number(root->val))
//			return atoi(root->val);
//		else
//			return get_value(context);
//	case led:
//		switch ((int)root->val) {
//		case	plus: return eval_Ast2(root->left, context) + eval_Ast2(root->right, context);
//		case	multiply:  return eval_Ast2(root->left, context) * eval_Ast2(root->right, context);
//		case	minus: return eval_Ast2(root->left, context) - eval_Ast2(root->right, context);
//		case	divide:  return eval_Ast2(root->left, context) / eval_Ast2(root->right, context);
//		case	less:  return eval_Ast2(root->left, context) < eval_Ast2(root->right, context);
//		case	more:  return eval_Ast2(root->left, context) > eval_Ast2(root->right, context);
//		case	equals:  return eval_Ast2(root->left, context) == eval_Ast2(root->right, context);
//		case	assign: return set_value(context, eval_Ast2(root->right, context));
//		}
//
//	}
//}
void eval_string(char* input) {
	TokenStream tokens = tokenize(input, space_seperated_operators());
	AbstractSyntaxTree* tree = parse(&tokens, 0);
	printf("\t%i\n", eval_Ast(tree));
}
void repl();
main(void) {
	init_binding_pow();
	init_representation();
	Context* c = new_context();
	set_value(c, "a", 3);
	printf("%i", get_value(c, "a"));
	//printf("operators:\n");
	//printf(space_seperated_operators());
	//printf("\n");
	//char* token_set = copy_string("( ) + - * / > < =");
	char* input = copy_string("1+1== (0+((3+7 )/(1+1))/2)");
	//char* input = copy_string("3==2");
	//char* input = copy_string("1+2");
	printf("%s\n", input);
	eval_string(input);
	repl();
	return 1;
}


int no_input_detected(char* input) {return strlen(input) <= 1;}

int should_quit(char* input) { return *input == 'q'; }

void print_quit_message() {	printf("Goodbye and thanks for using my parser.");}

void repl() {
	printf("\n");
	char input[1000];
	while(1) {
		fgets(input, 1000, stdin);
		if (should_quit(input))
			return print_quit_message();
		if(no_input_detected(input))
			continue;

		eval_string(input);
	}

}