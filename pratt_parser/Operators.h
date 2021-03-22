#pragma once
#include "language.h"
char* representation[operators_size];

void init_representation();
int init_binding_pow();
int binding_power(char* arg);

char* space_seperated_operators();

char* operator_to_string(enum operators op);

enum operators string_to_operator(char* str);