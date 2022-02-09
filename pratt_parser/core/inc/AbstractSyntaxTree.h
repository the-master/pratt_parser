#pragma once
#include "language.h"
typedef struct ast AbstractSyntaxTree;

typedef struct ast {
	ast_type_of_operand type;
	AbstractSyntaxTree* left;
	AbstractSyntaxTree* right;
	char* val;
} AbstractSyntaxTree;

AbstractSyntaxTree* new_Ast(ast_type_of_operand type, AbstractSyntaxTree* left, AbstractSyntaxTree* right, char* val);
void print_Ast(AbstractSyntaxTree* root);
