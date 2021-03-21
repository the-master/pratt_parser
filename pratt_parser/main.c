#include <stdio.h>
#include <string.h>
#include "Tokenizer.h"
#include "AbstractSyntaxTree.h"
#define _CRT_SECURE_NO_WARNINGS 1
char* copy_string(char* str) { return strcpy(malloc((strlen(str) + 1) * sizeof(char)), str); }

enum typez { led, nud };


int binding_power(char* arg) {
	switch (*arg) {
	case '+': return 20;
	case '-': return 20;
	case '*': return 30;
	case '/': return 30;
	case '(': return 0;
	case ')': return 0;
	case '<': return 40;
	case '>': return 40;
	case '=': return 40;
	}
}
AbstractSyntaxTree* parse(TokenStream*, int);
AbstractSyntaxTree* nud_create(char* arg, TokenStream* tokens) {
	if (*arg == '(')
	{
		AbstractSyntaxTree* rv = parse(tokens, binding_power(arg));
		if (*peek(tokens) != ')')
			printf("errrrrr");
		else
			next(tokens);

		return rv;
	}

	return new_Ast(nud, 0, 0, arg);
}
AbstractSyntaxTree* led_create(AbstractSyntaxTree* left, char* v, TokenStream* tokens, int binding_power) {

	AbstractSyntaxTree* rv = new_Ast(led, left, parse(tokens, binding_power), v);

	return rv;
}

AbstractSyntaxTree* parse(TokenStream* tokens, int current_binding_power) {
	if (!has_next(tokens))
		return NULL;

	AbstractSyntaxTree* left = nud_create(next(tokens), tokens);

	while (has_next(tokens) && binding_power(peek(tokens)) > current_binding_power)
		left = led_create(left, next(tokens), tokens, binding_power(peek(tokens)));

	return left;
}


int eval_Ast(AbstractSyntaxTree* root) {
	switch (root->type)
	{
	case nud:
		return atoi(root->val);
	case led:
		switch (*root->val) {
		case	'+': return eval_Ast(root->left) + eval_Ast(root->right);
		case	'*':  return eval_Ast(root->left) * eval_Ast(root->right);
		case	'-': return eval_Ast(root->left) - eval_Ast(root->right);
		case	'/':  return eval_Ast(root->left) / eval_Ast(root->right);
		case	'<':  return eval_Ast(root->left) < eval_Ast(root->right);
		case	'>':  return eval_Ast(root->left) > eval_Ast(root->right);
		case	'=':  return eval_Ast(root->left) == eval_Ast(root->right);
		}

	}
}
main(void) {
	char* token_set = copy_string("( ) + - * / > < =");
	char* input = copy_string("3< (0+((3+7 )/(1+1))/2)");
	char* inp = input;
	printf("input: : %s\n", input);
	TokenStream tokens = tokenize(input, token_set);
	AbstractSyntaxTree* tree = parse(&tokens, 0);
	print_Ast(tree);
	printf("\nEvaluates to : \t%i", eval_Ast(tree));
	return 1;
}