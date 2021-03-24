#pragma once
#include "language.h"

char* representation[operators_size];

void init_operator_module(void);

int binding_power(char* arg);

char* space_seperated_operators(void);

char* operator_to_string(operators op);

operators string_to_operator(char* str);