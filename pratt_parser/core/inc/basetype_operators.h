#pragma once

#include "Context.h"
#include "AbstractSyntaxTree.h"
#include "language.h"

typedef enum { int_b, float_b, base_types_size } base_types;
typedef struct {
	base_types type;
	union {
		int i;
		float f;
	};
}value_container;
void generate(void);
value_container operate(value_container v1, value_container v2, keywords keyword);
value_container string_to_value(char* number);
int is_a_basetype_number(char* number);