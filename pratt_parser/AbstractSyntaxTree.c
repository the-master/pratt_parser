#include "AbstractSyntaxTree.h"
#include "blub.h"
#include "Operators.h"
AbstractSyntaxTree* new_Ast(enum typez type, AbstractSyntaxTree* left, AbstractSyntaxTree* right, char* val) {
	AbstractSyntaxTree* rv = malloc(sizeof(AbstractSyntaxTree));
	rv->type = type;
	rv->val = val;
	rv->left = left;
	rv->right = right;
	return rv;
}


void print_Ast(AbstractSyntaxTree* root) {
	if (root == 0)
		return;
	if (root->type == nud)
		printf("%s ", root->val);
	else
		printf("%s ",operator_to_string((enum operators)root->val));
	print_Ast(root->left);
	printf(" ");
	print_Ast(root->right);
	printf("");
	
}