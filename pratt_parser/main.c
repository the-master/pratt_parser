#include <stdio.h>
#include <string.h>
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
		}

	}
}
main(void) {
	init_binding_pow();
	init_representation();

	if(	string_to_operator("==") == equals)
		printf("== is correct");
	printf("operators:\n");
	printf(space_seperated_operators());
	printf("\n");
	//char* token_set = copy_string("( ) + - * / > < =");
	//char* input = copy_string("1+3< (0+((3+7 )/(1+1))/2)");
	char* input = copy_string("3==2");
	//char* input = copy_string("1+2");
	printf("input: : %s\n", input);
	TokenStream tokens = tokenize(input, space_seperated_operators());
	print_all(tokens);
	printf("\n");
	AbstractSyntaxTree* tree = parse(&tokens, 0);
	print_Ast(tree);
	printf("\nEvaluates to : \t%i", eval_Ast(tree));
	return 1;
}