#pragma once

#include "language.h"

typedef enum { int_b, float_b, base_types_size } base_types;

typedef enum { int_a, float_a, pointer_a, array_a, user_struct_a, all_types_size } all_types;
typedef struct {
	int len;
	all_types type;
	void* content;
} array;
typedef struct {
	char* name;
	int todo;
} user_struct;
typedef struct {
	all_types type;
	union {
		int i;
		float f;
		void* ptr;
		user_struct o;
		array arr;
	};
}value_container;



void generate(char*);
value_container operate(value_container v1, value_container v2, keywords keyword);
value_container string_to_value(char* number);
int is_a_basetype_number(char* number);