#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AbstractSyntaxTree.h"
#include "language.h"
#include "Operators.h"
#include "util.h"
AbstractSyntaxTree* new_Ast(typez type, AbstractSyntaxTree* left, AbstractSyntaxTree* right, char* val) {
	AbstractSyntaxTree* rv = exit_on_null( malloc(sizeof(AbstractSyntaxTree)));
	rv->type = type;
	rv->val = val;
	rv->left = left;
	rv->right = right;
	return rv;
}


void print_Ast_recursive(AbstractSyntaxTree* root) {
	if (root == 0)
		return;

	print_Ast_recursive(root->left);
	printf("");
	if (root->type == no_left_operand)
		printf(" %s ", root->val);
	else {
		printf(" %s ", operator_to_string((operators)root->val));
	}
	print_Ast_recursive(root->right);
	printf("");

}

void print_Ast(AbstractSyntaxTree* root) {
	print_Ast_recursive(root);
	printf("\n");
}