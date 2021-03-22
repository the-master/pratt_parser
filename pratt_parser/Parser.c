#include "AbstractSyntaxTree.h"
#include "Tokenizer.h"
#include "Operators.h"
#include "Parser.h"

AbstractSyntaxTree* nud_create(char* arg, TokenStream* tokens) {
	if (*arg == '(')
	{
		AbstractSyntaxTree* rv = parse(tokens, binding_power(arg));
		if (*peek(tokens) != ')')
			printf("errrrrr");
		else
			next(tokens);

		return rv;
	}

	return new_Ast(leaf, 0, 0, arg);
}
AbstractSyntaxTree* led_create(AbstractSyntaxTree* left, char* v, TokenStream* tokens, int binding_power) {

	AbstractSyntaxTree* rv = new_Ast(node, left, parse(tokens, binding_power), (char*)string_to_operator(v));

	return rv;
}

AbstractSyntaxTree* parse(TokenStream* tokens, int current_binding_power) {
	if (!has_next(tokens))
		return 0;

	AbstractSyntaxTree* left = nud_create(next(tokens), tokens);

	while (has_next(tokens) && binding_power(peek(tokens)) > current_binding_power)
		left = led_create(left, next(tokens), tokens, binding_power(peek(tokens)));

	return left;
}