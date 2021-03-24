#include <string.h>
#include <stdlib.h>
#include "Operators.h"
#include "util.h"
char* representation[operators_size];
int binding_pow[operators_size];

void init_representation(void) {
	representation[plus] = "+";
	representation[minus] = "-";
	representation[multiply] = "*";
	representation[divide] = "/";
	representation[left_brace] = "(";
	representation[right_brace] = ")";
	representation[less] = "<";
	representation[more] = ">";
	representation[equals] = "==";
	representation[assign] = "=";
	representation[and] = "&&";

}


char* operator_to_string(operators op) {
	return representation[op];
}
operators string_to_operator(char* str) {
	
	for (int i = 0; i < operators_size ; i++) 
		if (strcmp(str, representation[i]) == 0)
			return i;
	
	return -1;
}
int init_binding_pow(void) {
	binding_pow[plus] = 20;
	binding_pow[minus] = 20;
	binding_pow[multiply] = 30;
	binding_pow[divide] = 30;
	binding_pow[less] = 15;
	binding_pow[more] = 16;
	binding_pow[equals] = 17;
	binding_pow[assign] = 10;
	binding_pow[and] = 40;
	return 1;
}

int binding_power(char* arg) {
	return binding_pow[string_to_operator(arg)];

}


char* space_seperated_operators(void) {
	char* rv = exit_on_null( malloc(operators_size * 4 ));
	*rv = 0;
	for (int i = 0; i < operators_size; i++)
	{
		strcat(rv, representation[i]);
		strcat(rv, " ");
	}
	char* temp = copy_string(rv);
	free(rv);
	return temp;
}


void init_operator_module(void) {
	init_representation();
	init_binding_pow();
}