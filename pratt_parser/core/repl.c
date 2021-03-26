#include <string.h>
#include <stdio.h>
#include "repl.h"
#include "Context.h"
#include "eval.h"
int no_input_detected(char* input) { return strlen(input) == 0; }

int should_quit(char* input) { return *input == 'q'; }

void print_quit_message(void) { printf("Goodbye and thanks for using my parser."); }

void remove_new_line(char* string) {
	string[strlen(string) - 1] = 0;
}
void repl(void) {
	printf("\nWelcome to the interactive version of my language:\n\ttype any string starting with q to exit \n\n");
	char input[1000];
	Context* context = new_context();
	while (1) {
		printf(">");
		fgets(input, 1000, stdin);
		if (should_quit(input)) {
			print_quit_message();
			return;
		}

		remove_new_line(input);
		if (no_input_detected(input)) 
			continue;
		
		eval_string(input, context, "v");
	}
}