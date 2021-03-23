
#include "Context.h"
#include "TestRunner.h"

void test_expression() {
	name_test();
	//char* input = copy_string("1+1== (0+((3+7 )/(1+1))/2)");
	char* input = copy_string("a := 1");
	Context* context = new_context();
	eval_string2(input, context);
	assert(equals_int, get_value(context, "a"), 1);
}
void tests_parser() {
	register_tests(&test_expression);
}