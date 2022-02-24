#include "TestCollector.h"
#include "Context.h"
#include "util.h"
#include "eval.h"
static void test_assignment(void) {
	name_test();
	
	Context* context = new_context();
	set_value(context, "a", (value_container) {int_b,3});
	assert(equals_int, get_value(context, "a").i, 3);
}

void tests_context(void) {
	register_tests(&test_assignment);
}