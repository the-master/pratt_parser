#include "TokenStreamTest.h"
#include "TestRunnerTest.h"
#include "ContextTest.h"
void prepare_tests() {
	tests_TokenStream();
	test_framework();
	tests_parser();
	tests_context();
}