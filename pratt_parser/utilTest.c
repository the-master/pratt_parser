#include "util.h"
#include "Testing.h"
void test_assignment2() {
	name_test();
	assert(equals_int, 1, 1);
}
void tests_util() {
	register_tests(&test_assignment2);
}