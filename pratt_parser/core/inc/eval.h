#pragma once
#include "AbstractSyntaxTree.h"
#include "Context.h"

int eval_Ast(AbstractSyntaxTree* root, Context* context);

Context* eval_string(char* input, Context* context, char* arguments);
