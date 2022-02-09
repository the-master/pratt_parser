#pragma once
#include "language.h"


void init_operator_module(void);

int binding_power(char* arg);

char* space_seperated_operators(void);

char* operator_to_string(keywords op);

keywords string_to_operator(char* str);