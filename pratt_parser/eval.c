#include "eval.h"
#include "language.h"
int eval_Ast2(AbstractSyntaxTree* root, Context* context) {
	if (root == 0)
		return printf("evaluating null tree\n"), 0;
	switch (root->type)
	{
	case leaf:
		if (is_number(root->val))
			return atoi(root->val);
		else
			return get_value(context, root->val);
	case node:
		switch ((int)root->val) {
		case	plus: return eval_Ast2(root->left, context) + eval_Ast2(root->right, context);
		case	multiply:  return eval_Ast2(root->left, context) * eval_Ast2(root->right, context);
		case	minus: return eval_Ast2(root->left, context) - eval_Ast2(root->right, context);
		case	divide:  return eval_Ast2(root->left, context) / eval_Ast2(root->right, context);
		case	less:  return eval_Ast2(root->left, context) < eval_Ast2(root->right, context);
		case	more:  return eval_Ast2(root->left, context) > eval_Ast2(root->right, context);
		case	equals:  return eval_Ast2(root->left, context) == eval_Ast2(root->right, context);
		case	assign: return root->left ? set_value(context, root->left->val, eval_Ast2(root->right, context)) : -999;
		}

	}
}

Context* eval_string2(char* input, Context* context) {
	TokenStream tokens = tokenize(input, space_seperated_operators());
	AbstractSyntaxTree* tree = parse(&tokens, 0);
	//print_Ast(tree);
	printf("\t%i\n", eval_Ast2(tree, context));
	return context;
}