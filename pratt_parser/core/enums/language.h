#pragma once

typedef enum { with_left_operand, no_left_operand } ast_type_of_operand;
typedef enum { plus, minus, multiply, divide, left_brace, right_brace, less, more, not_equals,
equals,leq,geq, assign, and, or, conditional,conditional_else,loop,statement_seperator, return_statement,declaration,array_declaration_l, array_declaration_r,brace_constructor_l, brace_constructor_r,operators_size }keywords;

