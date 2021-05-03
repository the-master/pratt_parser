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
	representation[leq] = "<=";
	representation[geq] = ">=";
	representation[equals] = "==";
	representation[not_equals] = "!=";
	representation[assign] = "=";
	representation[and] = "&&";
	representation[or] = "||";
	representation[conditional] = "if";
	representation[loop] = "while";
	representation[statement_seperator] = ",";

}
void init_binding_pow(void) {
	binding_pow[left_brace] = -10;
	binding_pow[right_brace] = -10;
	binding_pow[statement_seperator] = 1;
	binding_pow[assign] = 14;
	binding_pow[less] = 15;
	binding_pow[more] = 16;
	binding_pow[leq] = 16;
	binding_pow[geq] = 16;
	binding_pow[equals] = 17;
	binding_pow[not_equals] = 17;
	binding_pow[and] = 40;
	binding_pow[or ] = 35;
	binding_pow[plus] = 20;
	binding_pow[minus] = 20;
	binding_pow[multiply] = 30;
	binding_pow[divide] = 30;
}

operators string_to_operator(char* str) {

	for (int i = 0; i < operators_size; i++)
		if (strcmp(str, representation[i]) == 0)
			return i;

	return -1;
}
char* operator_to_string(operators op) {
	return representation[op];
}
int binding_power(char* arg) {
	return binding_pow[string_to_operator(arg)];

}
static int strlen_comparator(char* a, char* b) {
	return strlen(a) - strlen(b);
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