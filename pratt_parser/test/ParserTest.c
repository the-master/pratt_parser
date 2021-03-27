#include "TestCollector.h"
#include "Context.h"
#include "util.h"
#include "eval.h"
static void test_assignment(void) {
	name_test();
	char* input = copy_string("a = 1");
	Context* context = new_context();
	eval_string(input, context,"");
	assert(equals_int, get_value(context, "a"), 1);
}
static void test_assignment_chained(void) {
	name_test();
	char* input = copy_string("a = b=1");
	Context* context = new_context();
	eval_string(input, context, "");
	assert(equals_int, get_value(context, "a"), 1);
}
static void test_chained_statments(void) {
	name_test();
	char* input = copy_string("a =1,b=a+3");
	Context* context = new_context();
	eval_string(input, context, "");
	assert(equals_int, get_value(context, "b"), 4);
}
static void test_loop(void) {
	name_test();
	char* input = copy_string("x =0,sum=0,while(x<100)(x=x+1,sum=sum+x)");
	Context* context = new_context();
	eval_string(input, context, "");
	assert(equals_int, get_value(context, "sum"), 5050);
}
void tests_Parser_module(void) {
	register_tests(&test_assignment,
		&test_assignment_chained,
		&test_chained_statments,
		&test_loop);
}