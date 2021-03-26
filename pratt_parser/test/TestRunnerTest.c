#pragma once
#include "TestCollector.h"
 void equals_int_test(void) {
	name_test();
	assert(equals_int, 1, 1);
}
 void not_equals_int_test(void) {
	 name_test();
	assert(not_equals_int, 1, 2);
}
 void equals_string_test(void) {
	 name_test();
	assert(equals_string, "bblub","bblub");
}
 void not_equals_string_test(void) {
	 name_test();
	 assert(not_equals_string, "blub", "blob");
 }
 


void tests_framework(void) {
	register_tests(
		&equals_int_test,
		&equals_string_test,
		&not_equals_int_test,
		&not_equals_string_test
	);
}