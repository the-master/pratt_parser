#include "eval.h"
#include "language.h"
#include "util.h"
#include "Operators.h"
#include "Parser.h"
#include "stdlib.h"
#include <stdio.h>
int eval_Ast(AbstractSyntaxTree* root, Context* context) {
	if (root == 0)
		return printf("evaluating null tree\n"), 0;
	switch (root->type)
	{
	case leaf:
		if (string_to_operator(root->val) == conditional) {
			if (eval_Ast(root->left, context))
				return eval_Ast(root->right,context);
			return 0;
		}
		if (string_to_operator(root->val) == loop) {
			int rv = 0;
			while (eval_Ast(root->left, context))
				rv= eval_Ast(root->right, context);
			return rv;
		}
		if (is_number(root->val))
			return atoi(root->val);
		else
			return *root->val=='-'?-get_value(context, root->val+1): get_value(context, root->val);
	case node:
		switch ((int)root->val) {
		case	plus: return eval_Ast(root->left, context) + eval_Ast(root->right, context);
		case	multiply:  return eval_Ast(root->left, context) * eval_Ast(root->right, context);
		case	minus: return eval_Ast(root->left, context) - eval_Ast(root->right, context);
		case	divide:  return eval_Ast(root->left, context) / eval_Ast(root->right, context);
		case	less:  return eval_Ast(root->left, context) < eval_Ast(root->right, context);
		case	more:  return eval_Ast(root->left, context) > eval_Ast(root->right, context);
		case	equals:  return eval_Ast(root->left, context) == eval_Ast(root->right, context);
		case	and:  return eval_Ast(root->left, context) && eval_Ast(root->right, context);
		case	assign: return root->left ? set_value(context, root->left->val, eval_Ast(root->right, context)) : -999;
		case	statement_seperator:return eval_Ast(root->left, context), eval_Ast(root->right, context);
		case	operators_size: return 0;
		}
	}
	printf("errrr something went terribly wrong\n");
	return -1;
}

Context* eval_string(char* input, Context* context) {
	TokenStream tokens = tokenize(input, space_seperated_operators());
	AbstractSyntaxTree* tree = parse(&tokens, 0);
	//print_Ast(tree);
	printf("\t%i\n", eval_Ast(tree, context));
	return context;
}