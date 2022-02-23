#pragma once
#include "AbstractSyntaxTree.h"
#include "Context.h"
#include "FunctionContext.h"
int eval_Ast(AbstractSyntaxTree* root, Context* context);

Context* eval_string(char* input, Context* context, char* arguments);

Context* eval_string2(char* input, Context* context,FunctionContext* fn_context, char* arguments);
int Ast_to_c_file(char* output, AbstractSyntaxTree* root, Context* c, int indentation_count);

value_container eval_Ast_temp(AbstractSyntaxTree* root, Context* context);
