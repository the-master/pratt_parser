#pragma once
#include "Tokenizer.h"
#include "AbstractSyntaxTree.h"
#include "blub.h"

AbstractSyntaxTree* parse(TokenStream* tokens, int current_binding_power);