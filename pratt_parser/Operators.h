#pragma once
typedef enum { plus, minus, multiply, divide, left_brace, right_brace, less, more, equals,assign, operators_size }operators;
char* representation[operators_size];

void init_representation();
int init_binding_pow();
int binding_power(char* arg);

char* space_seperated_operators();

char* operator_to_string(enum operators op);

enum operators string_to_operator(char* str);