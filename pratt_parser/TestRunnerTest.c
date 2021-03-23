#pragma once
#include "TestRunner.h"
 void equals_int_test() {
	register_test();
	assert(equals_int, 1, 1);
}
 void not_equals_int_test() {
	register_test();
	assert(not_equals_int, 1, 2);
}
 void equals_string_test() {
	register_test();
	assert(equals_string, "bblub","bblub");
}
 void not_equals_string_test() {
	 register_test();
	 assert(not_equals_string, "blub", "blob");
 }
 


void test_framework() {
	register_tests(
		&equals_int_test,
		&equals_string_test,
		&not_equals_int_test,
		&not_equals_string_test
	);
}