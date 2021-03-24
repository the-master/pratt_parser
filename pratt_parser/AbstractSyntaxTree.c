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
	if (root->type == leaf)
		printf("%s ", root->val);
	else
		printf("%s ", operator_to_string((operators)root->val));
	print_Ast_recursive(root->left);
	printf(" ");
	print_Ast_recursive(root->right);
	printf(" ");

}
void printBT(char* prefix,AbstractSyntaxTree* node, int isLeft,int first)
{
	char buff[1000];
	if (node == 0)
		return;
	printf("%s",prefix);
	if (first) {
		printf(" %s\n", node->type == leaf ? node->val : operator_to_string((operators)node->val));
		printBT("   ", node->left, 1,0);
		printBT("   ", node->right, 0,0);
		return;
	}

	printf("%s",isLeft ? "|--" : "\"--");

	// print the value of the node
	printf(" %s\n",node->type==leaf?node->val:operator_to_string((operators)node->val));

	// enter the next tree level - left and right branch
	*buff = 0;
	strcat(buff, prefix);
	strcat(buff, isLeft ? "|---" : "    ");

	printBT(copy_string(buff), node->left, 1,0);
	*buff = 0;
	strcat(buff, prefix);
	strcat(buff, isLeft ? "|   " : "    ");
	printBT(copy_string(buff), node->right, 0,0);

}
void print_Ast(AbstractSyntaxTree* root) {
	printBT("",root,0,1);
	print_Ast_recursive(root);
	printf("\n");
}