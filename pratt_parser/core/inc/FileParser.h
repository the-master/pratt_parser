#pragma once
#include"AbstractSyntaxTree.h"

typedef struct {
	int i;
	char* name;
	int arg_count;
	char** args;
	char* expression;
	AbstractSyntaxTree* tree;
}CCFunction;
typedef struct {
	int i;
	CCFunction functions[100];
}CCFile;
void repl2(char* source_file);