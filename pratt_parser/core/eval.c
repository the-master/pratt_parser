
#include <stdio.h>
#include <string.h>
#include "eval.h"
#include "language.h"
#include "util.h"
#include "Operators.h"
#include "Parser.h"
#include "stdlib.h"
#include "basetype_operators.h"


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
typedef struct {
	TokenStream arguments_types;
	char* return_type;
}expression_type;
expression_type null_type;
expression_type int_epxr = { .return_type = "int" };
expression_type type_of_Ast(AbstractSyntaxTree* root, Context* context) {
	if (root == 0)
		return null_type;
	switch (root->type)
	{
	case no_left_operand:
		switch (string_to_operator(root->val))
		{
		case return_statement:
			return type_of_Ast(root->right, context);
		case conditional:
			return null_type;
		case loop:
			return null_type;
		default:
			if (is_number(root->val))
				return (expression_type) { .return_type = "int" };
			else if (is_function_token(root->val)) {
				TokenStream temp = new_TokenStream();

				expression_type exp = { temp,"int" };
				return exp;
			}
		case with_left_operand:
			switch ((int)root->val) {
			case	plus: return int_epxr;
			case	multiply:  return int_epxr;
			case	minus: return int_epxr;
			case	divide:  return int_epxr;
			case	less:  return int_epxr;
			case	more:  return int_epxr;
			case	leq:  return int_epxr;
			case	geq:  return int_epxr;
			case	equals: return int_epxr;
			case	not_equals: return int_epxr;
			caseand:  return int_epxr;
			case or :  return int_epxr;
			case	assign:
				if (root->left && root->left->val == declaration)
					return (expression_type) { .return_type = root->left->val };
				else if (root->left)
					return type_of_Ast(root->right, context);
			case	statement_seperator:return type_of_Ast(root->right, context);
			case	declaration:return null_type;
			case	operators_size: return null_type;
			}
		}
	}
	printf("errrr something went terribly wrong\n");
	return null_type;
}

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

value_container eval_Ast_temp(AbstractSyntaxTree* root, Context* context) {
	//print_Ast(root);
	//print_context(context);
	if (!context->alive)
		return (value_container) {	int_b, -666	};
	if (root == 0)
		return printf("evaluating null tree\n"), (value_container) { int_b, 0 };
	value_container rv;
	switch (root->type)
	{
	case no_left_operand:
		switch (string_to_operator(root->val))
		{
		case return_statement:
			rv = eval_Ast_temp(root->right, context);
			context->result = rv;
			context->alive = 0;
			return  rv;
		case conditional:
			if (eval_Ast_temp(root->left, context).i)
				return eval_Ast_temp(root->right->left, context);
			if (root->right->right)//XXX rfactor to else
				return eval_Ast_temp(root->right->right, context);
			return (value_container) { int_b, 0 };
		case loop: {
			value_container rv = { 0 };
			while (eval_Ast_temp(root->left, context).i)
				rv = eval_Ast_temp(root->right, context);
			return rv;
		}
		case array_declaration_l:
		{
				//AbstractSyntaxTree* tr = root->left;
				//value_container v = (value_container){ array_a,(array) {0,malloc(0)} };
				////	TokenStream function_argument = function_arguments(tr);
				////	print_all(function_argument);
				//if (tr->val != statement_seperator)
				//{
				//	v.arr.
				//}
				//do {//TODO  fix
				//	int temp;
				//	print_Ast(root);

				//	set_value(, tr->right->left->val, eval_Ast_temp(tr->right->right, context));
				//	tr = tr->left;
				//} while (tr && tr->val == statement_seperator);
				//return tr;
		}
		
			
		default:
			if (is_a_basetype_number(root->val))
				return string_to_value(root->val);
			else if (is_function_token(root->val)) {
				Context* function_scope = new_context();
				inherit_functions(context, function_scope);
				CCFunction* f = get_fun(context, root->val);
				function_scope->up = context;
				if (f->arg_count == 1)
				{
					set_value(function_scope, root->left->left->val, eval_Ast_temp(root->left->right, context));
				}
				else {
					AbstractSyntaxTree* tr = root->left;
					//	TokenStream function_argument = function_arguments(tr);
					//	print_all(function_argument);
					do {//TODO  fix
						int temp;
						print_Ast(root);

						set_value(function_scope, tr->right->left->val, eval_Ast_temp(tr->right->right, context));
						tr = tr->left;
					} while (tr && tr->val == statement_seperator);

					set_value(function_scope, tr->left->val, eval_Ast_temp(tr->right, context));
				}
				//	function_scope->up = 0;
					//print_Ast(f->tree);
				value_container res = eval_Ast_temp(f->tree, function_scope);
				if (function_scope->alive)
					return   res ;
				else
					return  function_scope->result ;
			}
			else
				return  * root->val == '-' ? get_value(context, root->val + 1) : get_value(context, root->val);
		}
	case with_left_operand:
		switch ((int)root->val) {
		case	plus: 
		case	multiply:
		case	minus: 
		case	divide:  
		case	less:  
		case	more:
		case	leq:
		case	geq:  
		case	equals:  
		case	not_equals:  
		case and :  
		case or : 
		 return operate(eval_Ast_temp(root->left, context) , eval_Ast_temp(root->right, context),(keywords)root->val);
		case	assign:
			if (root->left && root->left->val == declaration)
				return  set_value(context, root->left->right->val, eval_Ast_temp(root->right, context)) ;

			else if (root->left)
				return set_value(context, root->left->val, eval_Ast_temp(root->right, context)) ;
			else
				return (value_container) {	int_b, -99};

		case	statement_seperator:return eval_Ast_temp(root->left, context), eval_Ast_temp(root->right, context);
		case	declaration:return set_value(context, root->right->val, (value_container) { int_b, 0 });
		case	operators_size: return (value_container) {	int_b, 0};
		}
	}
	printf("errrr something went terribly wrong\n");
	return (value_container) {
		int_b, -1
	};
}




typedef struct { int todo; }VerificationData;
char* write_tabs(char* output, int indentation_count) {
	if ( output[-1] == '\n') {
		for (int i = 0; i < indentation_count; i++)
			output += sprintf(output, "\t");
	}
	return output;
}
int Ast_to_c_file(char* output, AbstractSyntaxTree* root, Context* c, int indentation_count,int binding_pow);
void write_symbol(char* output,AbstractSyntaxTree* root, char* symbol, Context* c, int indentation_count,int surrounding_spaces,int binding_pow) {
	char* written = output;
	int a = binding_power(symbol);
	
	if (a < binding_pow)	output += sprintf(output, "(");

	output += Ast_to_c_file(output, root->left, c,indentation_count,a);


	output += sprintf(output, "%s%s%s", surrounding_spaces ?" ":"", symbol, surrounding_spaces ? " " : "");

	output += Ast_to_c_file(output, root->right, c, indentation_count, a);

	if (a < binding_pow)	output += sprintf(output, ")");
}
int Ast_to_c_file(char* output,AbstractSyntaxTree* root,Context* c, int indentation_count,int binding_pow) {
	char* start = output;
	output = write_tabs(output,indentation_count );

	if (root == 0)
		return 1;
	switch (root->type)
	{
	case no_left_operand:
		switch (string_to_operator(root->val))
		{
		case return_statement:
			output += sprintf(output, "return ");
			output += Ast_to_c_file(output, root->right, c, indentation_count, binding_pow);
			output += sprintf(output, ";\n ");
			return strlen(start); ;
		case conditional:
			output += sprintf(output, "if( ");
			output += Ast_to_c_file(output, root->left, c, indentation_count, binding_pow);
			output += sprintf(output, ")\{\n");
			output += Ast_to_c_file(output, root->right, c, indentation_count, binding_pow);
			output = write_tabs(output, indentation_count);
			output += sprintf(output, "\}\n");
			return strlen(start);
		case loop:

			output += sprintf(output, "while( ");
			output += Ast_to_c_file(output, root->left, c, indentation_count, binding_pow);
			output += sprintf(output, ")\{\n");
			output += Ast_to_c_file(output, root->right, c, indentation_count, binding_pow);
			output = write_tabs(output, indentation_count);
			output +=sprintf(output, "\}\n");
			return strlen(start);
		default:
			if (is_number(root->val))
				return sprintf(output, "%s", root->val), strlen(start);
			else if (is_function_token(root->val)) {
				CCFunction* f = get_function(c->functions, root->val);
				output += sprintf(output, "%s", f->name);
				root = root->left;
				TokenStream ss = new_TokenStream();
				char buffer[200] = { 0 };
				for (int i = 0; i < f->arg_count - 1; i++) {
					Ast_to_c_file(buffer, root->right->right, c, indentation_count, 0);
					push(&ss, copy_string(buffer));
					push(&ss, copy_string(", "));
					if(i < f->arg_count - 2)
						root = root->left;
				}
				Ast_to_c_file(buffer, root->left->right, c, indentation_count, 0);
				push(&ss, copy_string(buffer));
				for (int i = ss.token_count - 1; i >= 0; i--)
					output += sprintf(output, "%s",ss.tokens[i]);
				output += sprintf(output, ")");
				return strlen(start);
			}
			else {
				sprintf(output, "%s", root->val);
				return strlen(start);
			}
		}
		case with_left_operand:
			switch ((int)root->val) {
			case	plus:
			case	multiply:
			case	minus:
			case	divide:
			case	less:
			case	more:
			case	leq:
			case	geq:
			case	equals:
			case	not_equals:
				write_symbol(output, root, operator_to_string((int)root->val), c, indentation_count,1,binding_pow);
				return strlen(start);
			case	assign:
				write_symbol(output, root, operator_to_string((int)root->val),c, indentation_count,1,0);
				return strlen(start);
			case	statement_seperator:
				write_symbol(output, root, "\;\n",c,  indentation_count,0,0);
				return strlen(start);
			case	declaration:

				write_symbol(output, root,  " ",c, indentation_count, 0,0);
				
				return strlen(start);
			case	operators_size: return 0;
			}
		}
	
	printf("errrr something went terribly wrong\n");
	return 0;
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
	int result = eval_Ast_temp(tree, context).i;
	if(verbose(arguments))
		printf("\t%i\n",result);
	return context;
}

