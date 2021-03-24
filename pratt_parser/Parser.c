#include <stdio.h>
#include "AbstractSyntaxTree.h"
#include "Tokenizer.h"
#include "Operators.h"
#include "Parser.h"
void discard_closing_brace(TokenStream* tokens) {
	if (*peek(tokens) != ')')
		printf("no closing brace found someting went wrong parsing");
	else
		next(tokens);
}
AbstractSyntaxTree* parse_start_of_expression(char* current_token, TokenStream* tokens) {
	if (*current_token == '(')
	{
		AbstractSyntaxTree* rv = parse(tokens, binding_power(current_token));
		discard_closing_brace(tokens);
		return rv;
	}

	return new_Ast(leaf, 0, 0, current_token);
}
AbstractSyntaxTree* parse_with_left_expression(AbstractSyntaxTree* left, char* v, TokenStream* tokens, int binding_power) {
	AbstractSyntaxTree* rv;
	switch (string_to_operator(v)) {
	case assign: 
		rv = new_Ast(node, left, parse(tokens, binding_power-1), (char*)string_to_operator(v));
		break;
	case	plus:
	case	multiply:
	case	minus:
	case	divide:
	case	less:
	case	more:
	case	equals:
	case	and :
	case	left_brace:
	case	right_brace:
	case	operators_size:
	default:
		rv = new_Ast(node, left, parse(tokens, binding_power), (char*)string_to_operator(v));
	}
	return rv;
}

AbstractSyntaxTree* parse(TokenStream* tokens, int current_binding_power) {
	if (!has_next(tokens))
		return 0;

	AbstractSyntaxTree* left = parse_start_of_expression(next(tokens), tokens);

	while (has_next(tokens) && binding_power(peek(tokens)) > current_binding_power)
		left = parse_with_left_expression(left, next(tokens), tokens, binding_power(peek(tokens)));

	return left;
}