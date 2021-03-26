#include "util.h"
#include "Testing.h"
static void test_assignment2(void) {
	name_test();
	assert(equals_int, 1, 1);
}
void tests_util(void) {
	register_tests(&test_assignment2);
}