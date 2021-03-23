#pragma once
#include "AbstractSyntaxTree.h"
#include "Context.h"

int eval_Ast2(AbstractSyntaxTree* root, Context* context);

Context* eval_string2(char* input, Context* context);