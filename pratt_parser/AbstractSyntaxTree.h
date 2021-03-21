#pragma once
typedef struct Ast AbstractSyntaxTree;
typedef struct Ast {
	enum typez type;
	AbstractSyntaxTree* left;
	AbstractSyntaxTree* right;
	char* val;
} AbstractSyntaxTree;

AbstractSyntaxTree* new_Ast(enum typez type, AbstractSyntaxTree* left, AbstractSyntaxTree* right, char* val);
void print_Ast(AbstractSyntaxTree* root);
