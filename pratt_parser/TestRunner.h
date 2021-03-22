#pragma once
#include <stdarg.h>
typedef enum {equals_int,equals_string  }test_type;
typedef struct {
	char* name;
	int succes;
	char* explanation;
}Test;
typedef struct {
	Test* tests;
}TestRunner;
typedef struct {
	Test executed[1000];
	int n;
}TestReport;
void register_tests(int n, ...);
void name(char*);
void print_test_report();
void print_test(Test test);