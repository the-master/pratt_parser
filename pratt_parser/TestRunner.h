#pragma once
#include <stdarg.h>
#include <limits.h>

#define register_tests(...) _register_tests(__FILE__,sizeof((void*[]) {__VA_ARGS__}) / sizeof(void*), __VA_ARGS__)
#define name_test() _name(__func__)
typedef enum {equals_int,equals_string ,not_equals_string,not_equals_int}test_type;
typedef struct {
	void (*test)();
	char* name;
	int succes;
	char* explanation;
}Test;
typedef struct {
	char* name;
	Test tests[1000];
	int n;
}TestSet;
typedef struct {
	TestSet tests[1000];
	int n;
}TestRunner;
void _register_tests(char* name,int n , ...);
void _name(char*);
void assert(test_type t,...);
void print_test(Test test);
void run_tests();