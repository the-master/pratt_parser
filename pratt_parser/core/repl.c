#include <string.h>
#include <stdio.h>
#include "repl.h"
#include "Context.h"
#include "eval.h"
#include "util.h"
static int no_input_detected(char* input) { return strlen(input) == 0; }

static int should_quit(char* input) { return *input == 'q'; }

static void print_quit_message(void) { printf("Goodbye and thanks for using my parser."); }

static void remove_new_line(char* string) {
	if(string[strlen(string) - 1]=='\n')
		string[strlen(string) - 1] = 0;
}
static int buffer_overflow_attempt(char* input) {
	if(strlen(input)==999)
		return input[999] == 0 && ((input[998] != '\n') || ( input[998] != '\r'));
	return 0;
}
void repl(void) {
	printf("\nWelcome to the interactive version of my language:\n\ttype any string starting with q to exit \n\n");
	char input[1000];
	Context* context = new_context();
	while (1) {
		printf(">");
		fgets(input, 1000, stdin);
		if (buffer_overflow_attempt(input))
		{
			printf("Max input 1000 characters \n");
			int ch;
			while ((ch = getchar() != '\n') && (ch != EOF));
			continue;
		}
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
static int is_empty_line(char line[300]) {
	for (int i = 0; i < 300; i++)
	{
		char c = line[i];
		if (c != ' ' && c != '\t' && c != '\n')
			return 0;
	}
	return 1;
}