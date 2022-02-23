#include "basetype_operators.h"
#include <stdlib.h>
#include <string.h>
#include "Operators.h"
#include "util.h"
#include <stdio.h>
typedef enum { plus_b, multiply_b, divide_b, equals_b,minus_b,less_b,more_b,leq_b,geq_b,not_equals_b,and_b,or_b,base_operations_size } base_operations;
value_container plus_int_int(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i + v2.i }; }
value_container plus_int_float(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i + v2.f }; }
value_container plus_float_int(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f + v2.i }; }
value_container plus_float_float(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f + v2.f }; }
value_container multiply_int_int(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i * v2.i }; }
value_container multiply_int_float(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i * v2.f }; }
value_container multiply_float_int(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f * v2.i }; }
value_container multiply_float_float(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f * v2.f }; }
value_container divide_int_int(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i / v2.i }; }
value_container divide_int_float(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i / v2.f }; }
value_container divide_float_int(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f / v2.i }; }
value_container divide_float_float(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f / v2.f }; }
value_container equals_int_int(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i == v2.i }; }
value_container equals_int_float(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i == v2.f }; }
value_container equals_float_int(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f == v2.i }; }
value_container equals_float_float(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f == v2.f }; }
value_container minus_int_int(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i - v2.i }; }
value_container minus_int_float(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i - v2.f }; }
value_container minus_float_int(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f - v2.i }; }
value_container minus_float_float(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f - v2.f }; }
value_container less_int_int(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i < v2.i }; }
value_container less_int_float(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i < v2.f }; }
value_container less_float_int(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f < v2.i }; }
value_container less_float_float(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f < v2.f }; }
value_container more_int_int(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i > v2.i }; }
value_container more_int_float(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i > v2.f }; }
value_container more_float_int(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f > v2.i }; }
value_container more_float_float(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f > v2.f }; }
value_container leq_int_int(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i <= v2.i }; }
value_container leq_int_float(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i <= v2.f }; }
value_container leq_float_int(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f <= v2.i }; }
value_container leq_float_float(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f <= v2.f }; }
value_container geq_int_int(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i >= v2.i }; }
value_container geq_int_float(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i >= v2.f }; }
value_container geq_float_int(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f >= v2.i }; }
value_container geq_float_float(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f >= v2.f }; }
value_container not_equals_int_int(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i != v2.i }; }
value_container not_equals_int_float(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i != v2.f }; }
value_container not_equals_float_int(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f != v2.i }; }
value_container not_equals_float_float(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f != v2.f }; }
value_container and_int_int(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i && v2.i }; }
value_container and_int_float(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i && v2.f }; }
value_container and_float_int(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f && v2.i }; }
value_container and_float_float(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f && v2.f }; }
value_container or_int_int(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i || v2.i }; }
value_container or_int_float(value_container v1, value_container v2) { return (value_container) { int_b, .i = v1.i || v2.f }; }
value_container or_float_int(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f || v2.i }; }
value_container or_float_float(value_container v1, value_container v2) { return (value_container) { float_b, .f = v1.f || v2.f }; }
value_container(*all_operations[base_types_size][base_types_size][base_operations_size])(value_container, value_container) = {
		[int_b] [int_b] [plus_b] = plus_int_int,
		[int_b][float_b][plus_b] = plus_int_float,
		[float_b][int_b][plus_b] = plus_float_int,
		[float_b][float_b][plus_b] = plus_float_float,
		[int_b][int_b][multiply_b] = multiply_int_int,
		[int_b][float_b][multiply_b] = multiply_int_float,
		[float_b][int_b][multiply_b] = multiply_float_int,
		[float_b][float_b][multiply_b] = multiply_float_float,
		[int_b][int_b][divide_b] = divide_int_int,
		[int_b][float_b][divide_b] = divide_int_float,
		[float_b][int_b][divide_b] = divide_float_int,
		[float_b][float_b][divide_b] = divide_float_float,
		[int_b][int_b][equals_b] = equals_int_int,
		[int_b][float_b][equals_b] = equals_int_float,
		[float_b][int_b][equals_b] = equals_float_int,
		[float_b][float_b][equals_b] = equals_float_float,
		[int_b][int_b][minus_b] = minus_int_int,
		[int_b][float_b][minus_b] = minus_int_float,
		[float_b][int_b][minus_b] = minus_float_int,
		[float_b][float_b][minus_b] = minus_float_float,
		[int_b][int_b][less_b] = less_int_int,
		[int_b][float_b][less_b] = less_int_float,
		[float_b][int_b][less_b] = less_float_int,
		[float_b][float_b][less_b] = less_float_float,
		[int_b][int_b][more_b] = more_int_int,
		[int_b][float_b][more_b] = more_int_float,
		[float_b][int_b][more_b] = more_float_int,
		[float_b][float_b][more_b] = more_float_float,
		[int_b][int_b][leq_b] = leq_int_int,
		[int_b][float_b][leq_b] = leq_int_float,
		[float_b][int_b][leq_b] = leq_float_int,
		[float_b][float_b][leq_b] = leq_float_float,
		[int_b][int_b][geq_b] = geq_int_int,
		[int_b][float_b][geq_b] = geq_int_float,
		[float_b][int_b][geq_b] = geq_float_int,
		[float_b][float_b][geq_b] = geq_float_float,
		[int_b][int_b][not_equals_b] = not_equals_int_int,
		[int_b][float_b][not_equals_b] = not_equals_int_float,
		[float_b][int_b][not_equals_b] = not_equals_float_int,
		[float_b][float_b][not_equals_b] = not_equals_float_float,
		[int_b][int_b][and_b] = and_int_int,
		[int_b][float_b][and_b] = and_int_float,
		[float_b][int_b][and_b] = and_float_int,
		[float_b][float_b][and_b] = and_float_float,
		[int_b][int_b][or_b] = or_int_int,
		[int_b][float_b][or_b] = or_int_float,
		[float_b][int_b][or_b] = or_float_int,
		[float_b][float_b][or_b] = or_float_float,
};
keywords base_operations_to_keyword[base_operations_size] = { plus, multiply, divide, equals,minus,less,more,leq,geq,not_equals,and, or };
base_operations keyword_to_base_operations[operators_size] =
{ 
	[plus]=plus_b,
	[multiply]=multiply_b,
	[divide] = divide_b,
	[equals]=equals_b,
	[minus]=minus_b,
	[less] = less_b,
	[more] = more_b,
	[leq] = leq_b,
	[geq] = geq_b,
	[not_equals] = not_equals_b,
	[and] = and_b,
	[or ] = or_b
};
char* base_type_to_string[base_types_size] = { "int","float" };
char* base_operations_to_string[base_operations_size] = { "plus",	"multiply",	"divide",	"equals",	"minus",	"less" ,	"more" ,	"leq" ,	"geq" ,	"not_equals" ,	"and",	"or" };

value_container string_to_value(char* number) {
	value_container rv;
	int n;
	if (sscanf(number, "%d %n", &rv.i, &n) == 1 && !number[n]) {
		rv.type = int_b;
		return rv;
	}
	if (sscanf(number, "%f", &rv.f) == 1) {
		rv.type = float_b;
		return rv;
	}
	return rv;
}
int is_a_basetype_number(char* number) {
	value_container rv;
	int n;
	if (sscanf(number, "%d %n", &rv.i,&n) == 1 && !number[n])
		return 1;
	if (sscanf(number, "%f %n", &rv.f,&n) == 1) 
		return 1;
	return 0;
}

base_types string_to_base_type(char* str) {
	for (int i = 0; i < base_types_size; i++)
		if (strstr(str, base_type_to_string[i]) == 0)
			return (base_types)i;
	return base_types_size;
}
void add_operation(base_types t1, base_types t2, base_operations op, value_container(*operation)(value_container, value_container)) {
	all_operations[t1][t2][op] = operation;
}
int operation_exists(char* t1, char* t2, keywords keyword) {
	base_operations op = keyword_to_base_operations[keyword];
	base_types t1_b = string_to_base_type(t1);

	base_types t2_b = string_to_base_type(t2);
	if (t1_b == base_types_size || t2_b == base_types_size)
		return 0;
	return all_operations[t1_b][t2_b][op] != 0;
}
value_container operate(value_container v1, value_container v2, keywords keyword) {
	base_operations op = keyword_to_base_operations[keyword];
	return all_operations[v1.type][v2.type][op](v1, v2);
}

void generate(void) {

	char* base_key[base_types_size] = { ".i",".f" };
	TokenStream result = new_TokenStream();

	for (int OP = 0; OP < base_operations_size; OP++)
		for (int T1 = 0; T1 < base_types_size; T1++)
			for (int T2 = 0; T2 < base_types_size; T2++) {
				char* str = malloc(200);
				sprintf(str,
					"value_container %s_%s_%s(value_container v1, value_container v2) { return (value_container) { %s_b, %s = v1%s %s v2%s }; }\n",
					base_operations_to_string[OP],
					base_type_to_string[T1],
					base_type_to_string[T2],
					base_type_to_string[T1],
					base_key[T1],
					base_key[T1],
					operator_to_string(base_operations_to_keyword[OP]),
					base_key[T2]);
				push(&result, str);
			}
	while (has_next(&result))
		printf("%s", next(&result));

	result = new_TokenStream();
	push(&result, copy_string("value_container (*all_operations[base_types_size][base_types_size][base_operations_size])(value_container, value_container)= {\n"));

	for (int OP = 0; OP < base_operations_size; OP++)
		for (int T1 = 0; T1 < base_types_size; T1++)
			for (int T2 = 0; T2 < base_types_size; T2++) {
				 char* str = malloc(200);
				sprintf(str,
					"\t[%s_b] [%s_b] [%s_b] = %s_%s_%s,\n",
					base_type_to_string[T1],
					base_type_to_string[T2],
					base_operations_to_string[OP],
					base_operations_to_string[OP],
					base_type_to_string[T1],
					base_type_to_string[T2]);
				push(&result, str);
			}
	push(&result,copy_string("};\n"));
	while (has_next(&result))
		printf("%s", next(&result));



}