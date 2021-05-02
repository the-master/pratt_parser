#pragma once
#include "Tokenizer.h"
#include "AbstractSyntaxTree.h"
#include "language.h"
#include "Context.h"
AbstractSyntaxTree* parse(TokenStream* tokens, int current_binding_power,Context* context);