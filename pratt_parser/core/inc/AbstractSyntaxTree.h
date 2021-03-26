#pragma once
#include "language.h"
typedef struct ast AbstractSyntaxTree;

typedef struct ast {
	typez type;
	AbstractSyntaxTree* left;
	AbstractSyntaxTree* right;
	char* val;
} AbstractSyntaxTree;

AbstractSyntaxTree* new_Ast(typez type, AbstractSyntaxTree* left, AbstractSyntaxTree* right, char* val);
void print_Ast(AbstractSyntaxTree* root);
