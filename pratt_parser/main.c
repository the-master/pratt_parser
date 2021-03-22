#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.h"
#include "Tokenizer.h"
#include "AbstractSyntaxTree.h"
#include "Operators.h"
#include "util.h"
#define _CRT_SECURE_NO_WARNINGS 1







//int eval_Ast(AbstractSyntaxTree* root) {
//	switch (root->type)
//	{
//	case leaf:
//		return atoi(root->val);
//	case node:
//		switch ((int)root->val) {
//		case	plus: return eval_Ast(root->left) + eval_Ast(root->right);
//		case	multiply:  return eval_Ast(root->left) * eval_Ast(root->right);
//		case	minus: return eval_Ast(root->left) - eval_Ast(root->right);
//		case	divide:  return eval_Ast(root->left) / eval_Ast(root->right);
//		case	less:  return eval_Ast(root->left) < eval_Ast(root->right);
//		case	more:  return eval_Ast(root->left) > eval_Ast(root->right);
//		case	equals:  return eval_Ast(root->left) == eval_Ast(root->right);
//		case	assign: return eval_Ast(root->right);
//		}
//			printf("errrrrr");
//	}
//}
typedef struct {
	TokenStream keys;
	TokenStream values;
}Context;
Context* new_context() {
	Context* rv = malloc(sizeof(Context));
	rv->keys = new_TokenStream();
	rv->values= new_TokenStream();
	return rv;
}
int get_value(Context* context, char* key) {
	TokenStream keys = context->keys;
	TokenStream values = context->values;
	while (has_next(&keys)) {
		char* current_key = next(&keys);
		next(&values);
		if (strcmp(key, current_key) == 0)
			return (int)values.tokens[values.pos-1];
	}
}
int has_key(Context* context, char* key) {
	TokenStream keys = context->keys;
	while (has_next(&keys)) {
		char* current_key = next(&keys);
		if (strcmp(key, current_key) == 0)
			return 1;
	}
	return 0;
}
int set_value(Context* con,char* key, int val) {
	printf("settinf value: %i", val);
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
	return val;
}
int is_number(char* str) {
	while (*str)
		if (('0' > *str) || (*str > '9'))
			return 0;
		else
			str++;
	return 1;
}
void print_context(Context* c) {
	TokenStream keys = c->keys;
	TokenStream values = c->values;
	while (has_next(&keys)) {
		printf("%s: %i\n", next(&keys),next(&values));
	}
	return 0;
}
int eval_Ast2(AbstractSyntaxTree* root,Context* context) {
	if (root == 0)
		return printf("evaluating null tree\n"),0;
	switch (root->type)
	{
	case leaf:
		if (is_number(root->val))
			return atoi(root->val);
		else
			return get_value(context,root->val);
	case node:
		switch ((int)root->val) {
		case	plus: return eval_Ast2(root->left, context) + eval_Ast2(root->right, context);
		case	multiply:  return eval_Ast2(root->left, context) * eval_Ast2(root->right, context);
		case	minus: return eval_Ast2(root->left, context) - eval_Ast2(root->right, context);
		case	divide:  return eval_Ast2(root->left, context) / eval_Ast2(root->right, context);
		case	less:  return eval_Ast2(root->left, context) < eval_Ast2(root->right, context);
		case	more:  return eval_Ast2(root->left, context) > eval_Ast2(root->right, context);
		case	equals:  return eval_Ast2(root->left, context) == eval_Ast2(root->right, context);
		case	assign: return root->left?set_value(context, root->left->val,eval_Ast2(root->right, context)):-999;
		}

	}
}
//void eval_string(char* input) {
//	TokenStream tokens = tokenize(input, space_seperated_operators());
//	AbstractSyntaxTree* tree = parse(&tokens, 0);
//	printf("\t%i\n", eval_Ast(tree));
//}
Context* eval_string2(char* input,Context* context) {
	TokenStream tokens = tokenize(input, space_seperated_operators());
	AbstractSyntaxTree* tree = parse(&tokens, 0);
	print_Ast(tree);
	printf("\t%i\n", eval_Ast2(tree,context));
	return context;
}
void repl();
void repl2();
test_assignment() {
	char* input = copy_string("a := 1");
	Context* context = new_context();
	eval_string2(input, context);
	print_context(context);
}
azzert(int val,int expected) {
	if (val == expected)
		printf("succes\n");
	else
		printf("fail\n");
}
test_is_number() {
	char* test_string[] = { "blub" ,"1","a3","3a"};
	int expected[] = { 0,1,0,0 };
	for (int i = 0; i < 4; i++)
		azzert(is_number(test_string[i]), expected[i]);
}
main(void) {
	init_binding_pow();
	init_representation();
	test_assignment();
	test_is_number();
	printf("\n=================\n");
	//printf("operators:\n");
	//printf(space_seperated_operators());
	//printf("\n");
	//char* token_set = copy_string("( ) + - * / > < =");
	char* input = copy_string("1+1== (0+((3+7 )/(1+1))/2)");
	//char* input = copy_string("3==2");
	//char* input = copy_string("1+2");
	printf("%s\n", input);
	eval_string2(input,new_context());
	repl2();
	return 1;
}


int no_input_detected(char* input) {return strlen(input) <= 1;}
		
int should_quit(char* input) { return *input == 'q'; }

void print_quit_message() {	printf("Goodbye and thanks for using my parser.");}

//void repl() {
//	printf("\n");
//	char input[1000];
//	while(1) {
//		fgets(input, 1000, stdin);
//		if (should_quit(input))
//			return print_quit_message();
//		if(no_input_detected(input))
//			continue;
//
//		eval_string(input);
//	}
//}
void remove_new_line(char* string) {
	string[strlen(string) - 1] = 0;
}
void repl2() {
	printf("\n");
	char input[1000];
	Context* context = new_context();
	while (1) {
		fgets(input, 1000, stdin);
		if (should_quit(input))
			return print_quit_message();
		if (no_input_detected(input))
			continue;
		remove_new_line(input);
		eval_string2(input,context);
	}
}