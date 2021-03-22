#pragma once
typedef struct ast AbstractSyntaxTree;

typedef struct ast {
	enum typez type;
	AbstractSyntaxTree* left;
	AbstractSyntaxTree* right;
	char* val;
} AbstractSyntaxTree;

AbstractSyntaxTree* new_Ast(enum typez type, AbstractSyntaxTree* left, AbstractSyntaxTree* right, char* val);
void print_Ast(AbstractSyntaxTree* root);
