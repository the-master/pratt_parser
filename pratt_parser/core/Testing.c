#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Testing.h"
#include "util.h"

typedef struct Test {void (*test)(void);	char* name;	int succes;	char* explanation;}	Test;

typedef struct TestFile { char* name;	Test tests[1000]; int n; }TestFile;

static struct {	TestFile tests[1000];	int n; }all_tests;

static char* current_name;
static char* current_explenation;
static int current_succes;
static int expected_succes;
//static TestFramework all_tests;
void init_test_module(void) {
	all_tests.n = 0;
}
void print_test(Test test) {
	if (test.succes)
		printf("  [+]: %s\n",test.name);
	else
		printf("  [-]: %s failed because: %s\n",test.name,test.explanation);
}
void register_test(void (*f)(void)) {
	all_tests.tests[all_tests.n].tests[all_tests.tests[all_tests.n].n++].test = f;
}
void _register_tests(char*name,int n, ...){
	all_tests.tests[all_tests.n].name = name;
	 va_list ap;
	 va_start(ap, n);
	 for (int i = 0; i < n; i++) {
		 register_test(va_arg(ap, testing_function));
	 }
	 va_end(ap);

	 all_tests.n++;
}
void _name(char* arg) {
	current_name = arg;
}
void assert_string(char* left, char* right) {

	if (strcmp(left, right) == 0) {
		current_succes &= 1;
		return;
	}
	current_explenation = (char*) exit_on_null( malloc(1000 * sizeof(char)));
	sprintf(current_explenation, "%s is not equal to %s", left, right);
}
void assert_int(int x, int y) {
	current_succes &= (x == y);
	if (!current_succes) {
		current_explenation = (char*)exit_on_null(malloc(1000 * sizeof(char)));
		sprintf(current_explenation, "%i is not equal to %i", x, y);
	}
}
void assert_string_not_equal(char* left, char* right) {
	if (strcmp(left, right) != 0) {
		current_succes  &= 1;
		return;
	}
	current_explenation = (char*)exit_on_null(malloc(1000 * sizeof(char)));
	sprintf(current_explenation, "%s is equal to %s", left, right);
}
void assert_int_not_equal(int x, int y) {
	current_succes &= (x != y);
	if (!current_succes) {
		current_explenation = (char*)exit_on_null(malloc(1000 * sizeof(char)));
		sprintf(current_explenation, "%i is equal to %i", x, y);
	}
}
void assert(test_type type, ...) {
	va_list ap;
	va_start(ap, type);
	switch (type) {
	case equals_int:{
		int x = va_arg(ap, int);
		int y = va_arg(ap, int);
		assert_int(x, y);
		}break;
	case equals_string: {
		char* x = va_arg(ap, char*);
		char* y = va_arg(ap, char*);
		assert_string(x, y); 
		}break;
	case not_equals_int: {
		int x = va_arg(ap, int);
		int y = va_arg(ap, int);
		assert_int_not_equal(x, y);
	}break;
	case not_equals_string: {
		char* x = va_arg(ap, char*);
		char* y = va_arg(ap, char*);
		assert_string_not_equal(x, y);
	}break;
	}
	va_end(ap);

}
void expect_failure(void) {
	current_succes = 0;
	expected_succes = 0;
}
void run_tests(void) {
	printf("Starting Tests:\n----------------------------------------------------------------\n");
	for (int i = 0; i < all_tests.n; i++) {
		printf("From: %s\n", all_tests.tests[i].name);
		int aggregate_succes = 1;
		for (int j = 0; j < all_tests.tests[i].n; j++) {
			current_explenation = "no asserts were called";
			current_name = 0;
			expected_succes = 1;
			current_succes = 1;
			all_tests.tests[i].tests[j].test();
			all_tests.tests[i].tests[j].name = current_name==0?"use name_test() at the start of your test function to have it appear here":current_name;
			all_tests.tests[i].tests[j].succes = ( current_succes == expected_succes );
			aggregate_succes &= all_tests.tests[i].tests[j].succes;
			if(all_tests.tests[i].tests[j].succes == 0)
				all_tests.tests[i].tests[j].explanation = current_explenation;
			print_test(all_tests.tests[i].tests[j]);
		}
		printf(" %s\n\n",aggregate_succes?"[+] succes":"[-] failure");
	}
}