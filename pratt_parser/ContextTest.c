#include "TestCollector.h"
#include "Context.h"
#include "util.h"
#include "eval.h"
void test_assignment() {
	name_test();
	char* input = copy_string("a := 1");
	Context* context = new_context();
	eval_string2(input, context);
	assert(equals_int, get_value(context, "a"), 1);
}
void tests_context() {
	register_tests(&test_assignment);
}