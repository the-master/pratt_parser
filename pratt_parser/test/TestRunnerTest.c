#pragma once
#include "TestCollector.h"
static void equals_int_test(void) {
	name_test();
	assert(equals_int, 1, 1);
}
static  void not_equals_int_test(void) {
	 name_test();
	assert(not_equals_int, 1, 2);
}
static  void equals_string_test(void) {
	 name_test();
	assert(equals_string, "bblub","bblub");
}
static  void not_equals_string_test(void) {
	 name_test();
	 assert(not_equals_string, "blub", "blob");
 } 


static  void multi_assert_test(void) {
	 name_test();
	 assert(not_equals_string, "blub", "blob");
	 assert(not_equals_string, "blub", "blob");
 }
 void multi_assert_test_fail(void) {
	 name_test();
	 expect_failure();
	 assert(not_equals_string, "blob", "blob");
	 assert(not_equals_string, "blub", "blob");
	 assert(not_equals_string, "blub", "blob");
 }
 


void tests_framework(void) {
	register_tests(
		&equals_int_test,
		&equals_string_test,
		&not_equals_int_test,
		&not_equals_string_test,
		&multi_assert_test,
		&multi_assert_test_fail
	);
}