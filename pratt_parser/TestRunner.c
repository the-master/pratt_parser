#pragma once
#include "TestRunner.h"
static char* current_name;

void print_test_report() {

}
void print_test(Test test) {
	if (test.succes)
		printf("\t~~\t%s\n");
	else
		printf("\t##: %s failed because: %s\n",test.name,test.explanation);
}
void register_tests(int n, ...){
	 va_list ap;
	 va_start(ap, n);
	 va_arg(ap, int);
	 va_end(ap);
}
void name(char* arg) {
	current_name = arg;
}
assert(test_type type,int n, ...) {
	va_list ap;
	va_start(ap, n);
	switch (type) {
	case equals_int: assert_int(va_arg(ap, int), va_arg(ap, int));
	case equals_string: assert_string(va_arg(ap, char*), va_arg(ap, char*));
	}
	va_end(ap);

}
assert_string(char* left,char*right) {

}
assert_int(int x, int y) {
	
}
void run_tests() {

}