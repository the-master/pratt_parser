#include <stdio.h>
#include "util.h"
#include "AbstractSyntaxTree.h"
#include "Tokenizer.h"
#include "Operators.h"
#include <string.h>
#include "Parser.h"
#include "Context.h"
void discard_closing_brace(TokenStream* tokens) {
	if (*peek(tokens) != ')')
		printf("no closing brace found someting went wrong parsing");
	else
		next(tokens);
}
static int is_function_token(char* token) {
	return strlen(token)>1&&strstr(token, "(") != 0;
}
void discard_comma_or_brace(TokenStream* tokens) {
	if (*peek(tokens) == ','|| *peek(tokens) == ')')
		next(tokens);
	else
		printf("discarding comma for function arguments went wrong\n");
}

AbstractSyntaxTree* parse_start_of_expression(char* current_token, TokenStream* tokens, Context* context) {
	
	if (*current_token == '('){
		AbstractSyntaxTree* rv = parse(tokens, binding_power(current_token), context);
		discard_closing_brace(tokens);
		return rv;
	}
	if (is_function_token(current_token)) {
		if (has_fun(context, current_token))
		{
			CCFunction* f= get_fun(context, current_token);
			if (f->arg_count == 0) {
				discard_closing_brace(tokens);

				return new_Ast(no_left_operand, 0, 0, current_token);
			}
			AbstractSyntaxTree* acc[2] = { 0 };
			for (int i = 0; i < f->arg_count; i++) {
				AbstractSyntaxTree* value = parse(tokens, binding_power(","), context);
				AbstractSyntaxTree* variable = new_Ast(no_left_operand, 0, 0, f->args[i]);
				AbstractSyntaxTree* assignment=new_Ast(with_left_operand, variable, value, assign);
				if (acc[0] == 0 && acc[1] ==0)
					acc[0] = assignment;
				else if (acc[1]==0) {
					acc[1] = new_Ast(with_left_operand,acc[0],assignment, statement_seperator);
				}
				else {
					acc[1] = new_Ast(with_left_operand, acc[1], assignment, statement_seperator);
				}

				discard_comma_or_brace(tokens);
			}
			if(acc[1])	
				return new_Ast(no_left_operand, acc[1],0, current_token);
			else
				return new_Ast(no_left_operand, acc[0], 0, current_token);
		}

		AbstractSyntaxTree* rv = new_Ast(no_left_operand, 0, 0, current_token);
		//parse(tokens, binding_power("("))
		discard_closing_brace(tokens);
		return rv;
	}
	if (string_to_operator(current_token) == conditional)
	{
		AbstractSyntaxTree* condition = parse(tokens, 0, context);
		AbstractSyntaxTree* conditional_epxression = parse(tokens, 0, context);

		return new_Ast(no_left_operand, condition, conditional_epxression, current_token);
	}
	if (string_to_operator(current_token) == loop)
	{
		AbstractSyntaxTree* condition = parse(tokens, 0, context);
		AbstractSyntaxTree* conditional_epxression = parse(tokens, 0, context);

		return new_Ast(no_left_operand, condition, conditional_epxression, current_token);
	}

	return new_Ast(no_left_operand, 0, 0, current_token);
}
AbstractSyntaxTree* parse_with_left_expression(AbstractSyntaxTree* left, char* v, TokenStream* tokens, int binding_power, Context* context) {
	AbstractSyntaxTree* rv;
	switch (string_to_operator(v)) {
	case assign: 
		rv = new_Ast(with_left_operand, left, parse(tokens, binding_power-1, context), (char*)string_to_operator(v));
		break;
	case	plus:
	case	multiply:
	case	minus:
	case	divide:
	case	less:
	case	more:
	case	equals:
	case	not_equals:
	case	leq:
	case	geq:
	case	and:
	case	or:
	case	left_brace:
	case	right_brace:
	case	statement_seperator:
	case	operators_size:
	default:
		rv = new_Ast(with_left_operand, left, parse(tokens, binding_power, context), (char*)string_to_operator(v));
		break;
	case conditional:
		printf(" %s is not supported with %s as left argument.\n", operator_to_string(conditional),left->val);
		rv = 0;
		break;

	}
	return rv;
}

AbstractSyntaxTree* parse(TokenStream* tokens, int current_binding_power,Context* context) {
	if (!has_next(tokens))
		return 0;

	AbstractSyntaxTree* left = parse_start_of_expression(next(tokens), tokens, context);

	while (has_next(tokens) && binding_power(peek(tokens)) > current_binding_power)
		left = parse_with_left_expression(left, next(tokens), tokens, binding_power(peek(tokens)), context);

	return left;
}