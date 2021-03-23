#include <stdio.h>
#include <string.h>
#include "Parser.h"
#include "Tokenizer.h"
#include "AbstractSyntaxTree.h"
#include "Operators.h"
#include "util.h"
#include "TestRunner.h"
#include "TestCollector.h"
#include "repl.h"

#define _CRT_SECURE_NO_WARNINGS 1



main(void) {
	init_operator_module();

	prepare_tests();
	run_tests();
	repl();
	return 1;
}
