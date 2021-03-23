
#include <stdio.h>
#include "repl.h"
#include "Context.h"
int no_input_detected(char* input) { return strlen(input) <= 1; }

int should_quit(char* input) { return *input == 'q'; }

void print_quit_message() { printf("Goodbye and thanks for using my parser."); }

void remove_new_line(char* string) {
	string[strlen(string) - 1] = 0;
}
void repl() {
	printf("\nWelcome to the interactive version of my language:\n\ttype quit to exit \n\n");
	char input[1000];
	Context* context = new_context();
	while (1) {
		printf(">");
		fgets(input, 1000, stdin);
		if (should_quit(input))
			return print_quit_message();
		if (no_input_detected(input))
			continue;
		remove_new_line(input);
		eval_string2(input, context);
	}
}