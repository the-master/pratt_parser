
#include <stdio.h>
#include <string.h>
#include "eval.h"
#include "language.h"
#include "util.h"
#include "Operators.h"
#include "Parser.h"
#include "stdlib.h"



int is_function_token(char* token) {
	return strlen(token) > 1 && strstr(token, "(") != 0;
}


void inherit_functions(Context* origin, Context* target) {
	target->functions = origin->functions;
}
typedef struct eval_context {
	//int count;
	TokenStream answers;
	TokenStream stack;
}eval_context;
typedef struct eval_state {
	AbstractSyntaxTree* tree;
	Context* context;
	//void (*func)(eval_context);
}eval_state;

void push_state(eval_context* c, eval_state* state) {
	push(&(c->stack), (char*)state);
}
eval_state* pop_state(eval_context* c) {
	return (eval_state*) next(&(c->stack));
}
int has_state(eval_context* c) {
	return has_next(&(c->stack));
}
void f_eval(eval_state state) {
	AbstractSyntaxTree* root = state.tree;
	Context* context = state.context;

}
//eval_state f_conditional(eval_state e) {
//	AbstractSyntaxTree* root = e.tree;
//	Context* context = e.context;
//	if (eval_Ast(root->left, context))
//		return (eval_state){ root->right->left, context,f_eval,0 };
//	if (root->right->right)
//		return (eval_state){ root->right->right, context,f_eval,0 };
//	return (eval_state) { 0, 0, 0, 0 };
//}
//int evaal(AbstractSyntaxTree* root, Context* context) {
//
//	eval_context cont = { new_TokenStream() ,new_TokenStream()};
//	eval_state start = {root,context};
//	push_state(&cont, &start);
//	while (has_state(&cont)) {
//		eval_state* s = pop_state(&cont);
//		eval_Ast2(s->tree, s->context, cont);
//	}
//	//eval_state current = eval_Ast2(root, context);
//	
//}
//
//eval_state eval_Ast2(AbstractSyntaxTree* root, Context* context,eval_context c) {
//	//print_Ast(root);
//	//print_context(context);
//	if (root == 0)
//		return (eval_state) {0,0};
//	switch (root->type)	{
//	case no_left_operand:
//		switch (string_to_operator(root->val))
//		{
//		
//		}
//	case with_left_operand:
//		switch ((int)root->val) {
//		case	plus: 
//			push_state({root->left,context});
//			return eval_Ast(root->left, context) + eval_Ast(root->right, context);
//		//case	multiply:  return eval_Ast(root->left, context) * eval_Ast(root->right, context);
//		//case	minus: return eval_Ast(root->left, context) - eval_Ast(root->right, context);
//		//case	divide:  return eval_Ast(root->left, context) / eval_Ast(root->right, context);
//		//case	less:  return eval_Ast(root->left, context) < eval_Ast(root->right, context);
//		//case	more:  return eval_Ast(root->left, context) > eval_Ast(root->right, context);
//		//case	leq:  return eval_Ast(root->left, context) <= eval_Ast(root->right, context);
//		//case	geq:  return eval_Ast(root->left, context) >= eval_Ast(root->right, context);
//		//case	equals:  return eval_Ast(root->left, context) == eval_Ast(root->right, context);
//		//case	not_equals:  return eval_Ast(root->left, context) != eval_Ast(root->right, context);
//		//caseand :  return eval_Ast(root->left, context) && eval_Ast(root->right, context);
//		//case or :  return eval_Ast(root->left, context) || eval_Ast(root->right, context);
//		//case	assign: return root->left ? set_value(context, root->left->val, eval_Ast(root->right, context)) : -999;
//		//case	statement_seperator:return eval_Ast(root->left, context), eval_Ast(root->right, context);
//		//case	operators_size: return 0;
//		}
//	}
//	printf("errrr something went terribly wrong\n");
//	return -1;
//}

int eval_Ast(AbstractSyntaxTree* root, Context* context) {
	//print_Ast(root);
	//print_context(context);
	if (!context->alive)
		return -666;
	if (root == 0)
		return printf("evaluating null tree\n"), 0;
	switch (root->type)
	{
	case no_left_operand:
		switch (string_to_operator(root->val)) 
		{
		case return_statement:
			context->result = eval_Ast(root->right, context);
			context->alive = 0;
		case conditional:
			if (eval_Ast(root->left, context))
				return eval_Ast(root->right->left, context);
			if (root->right->right)//XXX rfactor to else
				return eval_Ast(root->right->right, context);
			return 0;
		case loop: {
			int rv = 0;
			while (eval_Ast(root->left, context))
				rv = eval_Ast(root->right, context);
			return rv;
		}
		default:
			if (is_number(root->val))
				return atoi(root->val);
			else if (is_function_token(root->val)) {
				Context* function_scope = new_context();
				inherit_functions(context, function_scope);
				CCFunction* f = get_fun(context, root->val);
				function_scope->up = context;
				if(root->left)
					eval_Ast(root->left, function_scope);
				function_scope->up = 0;
				//print_Ast(f->tree);
				int res= eval_Ast(f->tree, function_scope);
				if (function_scope->alive)
					return res;
				else
					return function_scope->result;
			}
			else
				return *root->val == '-' ? -get_value(context, root->val + 1) : get_value(context, root->val);
		}
	case with_left_operand:
		switch ((int)root->val) {
		case	plus: return eval_Ast(root->left, context) + eval_Ast(root->right, context);
		case	multiply:  return eval_Ast(root->left, context) * eval_Ast(root->right, context);
		case	minus: return eval_Ast(root->left, context) - eval_Ast(root->right, context);
		case	divide:  return eval_Ast(root->left, context) / eval_Ast(root->right, context);
		case	less:  return eval_Ast(root->left, context) < eval_Ast(root->right, context);
		case	more:  return eval_Ast(root->left, context) > eval_Ast(root->right, context);
		case	leq:  return eval_Ast(root->left, context) <= eval_Ast(root->right, context);
		case	geq:  return eval_Ast(root->left, context) >= eval_Ast(root->right, context);
		case	equals:  return eval_Ast(root->left, context) == eval_Ast(root->right, context);
		case	not_equals:  return eval_Ast(root->left, context) != eval_Ast(root->right, context);
		case	and:  return eval_Ast(root->left, context) && eval_Ast(root->right, context);
		case	or:  return eval_Ast(root->left, context) || eval_Ast(root->right, context);
		case	assign: return root->left ? set_value(context, root->left->val, eval_Ast(root->right, context)) : -999;
		case	statement_seperator:return eval_Ast(root->left, context), eval_Ast(root->right, context);
		case	operators_size: return 0;
		}
	}
	printf("errrr something went terribly wrong\n");
	return -1;
}
static int verbose(char* arguments) {
	if (arguments != 0 && *arguments == 'v')
		return 1;
	return 0;
}
Context* eval_file(char* file) {

}
Context* eval_string(char* input, Context* context,char* arguments) {
	TokenStream tokens = tokenize(input, space_seperated_operators());
	AbstractSyntaxTree* tree = parse(&tokens, 0,context,context);
	//print_Ast(tree);
	int result = eval_Ast(tree, context);
	if(verbose(arguments))
		printf("\t%i\n",result);
	return context;
}

