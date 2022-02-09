#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Context.h"
#include "Operators.h"
#include "eval.h"
#include "FileParser.h"
#include "Parser.h"
#include "util.h"
#include "Tokenizer.h"
static int remove_comments(char content[100][300], int n) {
	int count = 0;
	for (int i = 0; i < n; i++)
		if (has_comment_preamble(content[i]))
			content[i][0] = 0, count++;
	int i = 0;
	int j = 0;
	while (j < n) {
		while (content[i][0] != 0)
		{
			i++;
			if (i == n)
				goto DONE;
		}
		j = j < i ? i : j;
		while (content[j][0] == 0) {
			j++;
			if (j == n)
				goto DONE;
		}
		for (int x = 0; x < 300; x++)
			content[i][x] = content[j][x];
		content[j][0] = 0;
		i++, j++;
	}
DONE:;
	return count;

}


static void add_function(CCFile* file, char* name, char* expression, int argc, char** args, char* return_type) {
	file->functions[file->i].name = name;
	file->functions[file->i].expression = expression;
	file->functions[file->i].arg_count = argc;
	file->functions[file->i].args = args;
	file->functions[file->i].return_type = return_type;
	file->i++;
}
static AbstractSyntaxTree* main_f(CCFile* file) {
	for (int i = 0; i < file->i; i++)
		if (strstr(file->functions[i].name, "main") != 0)
			return file->functions[i].tree;
	return 0;
}
static int count_tabs(char line[300]) {
	int i = 0;
	while (line[i] == '\t' && i < 300)
		i++;
	return i;
}
static void remove_new_line(char* string) {
	if (string[strlen(string) - 1] == '\n')
		string[strlen(string) - 1] = 0;
}
static void remove_closing_brace(char* string) {
	if (string[strlen(string) - 1] == ')')
		string[strlen(string) - 1] = 0;
}

static int has_comment_preamble(char line[300]) {
	return line[0] == '/' && line[1] == '/';
}

int count_args(char* name) {
	if (strstr(name, "()") != 0)
		return 0;
	int comma_count = 0;
	while (*name != 0)
		if (*name++ == ',')
			comma_count++;
	return comma_count + 1;

}
static CCFile* parse_single_file(char lines[100][300], int n) {
	CCFile* file = malloc(sizeof(CCFile));
	Context* context = new_context();
	file->i = 0;
	char* parsed = malloc(20000);
	
	int i = 0;
	while (i < n) {
		*parsed = 0;
		char* writer = parsed;
		//function definition
		int current_tabs = 1;
		char* name = copy_string(lines[i++]);
		int start_of_block = 1;

		while (i < n && lines[i][0] == '\t')
		{
			remove_new_line(lines[i]);
			if (current_tabs == count_tabs(lines[i]))
			{
				if (!start_of_block)
					*writer++ = ',';
				*writer = 0;
				writer = strcat(writer, &lines[i][current_tabs]) + strlen(&lines[i][current_tabs]);
				start_of_block = 0;
			}
			else if (current_tabs < count_tabs(lines[i]))
			{
				current_tabs = count_tabs(lines[i]);
				*writer++ = '(';
				*writer = 0;
				writer = strcat(writer, &lines[i][current_tabs]) + strlen(&lines[i][current_tabs]);
				start_of_block = 0;
			}
			else {
				//XXX: reduce stepwise
				current_tabs = count_tabs(lines[i]);
				if (string_to_operator(&lines[i][current_tabs]) == conditional_else)
				{
					*writer++ = ')';
					*writer = 0;
					writer = strcat(writer, &lines[i][current_tabs]) + strlen(&lines[i][current_tabs]);

				}
				else {
					*writer++ = ')';
					*writer = 0;
					*writer++ = ',';
					*writer = 0;
					writer = strcat(writer, &lines[i][current_tabs]) + strlen(&lines[i][current_tabs]);
					start_of_block = 0;
				}

			}
			i++;
		}
		if (current_tabs > 1) {
			*writer++ = ')';
			*writer = 0;
		}
		remove_new_line(name);
		int argc =count_args(name);
		char** args = malloc(50 * sizeof(char*));
		char* start = strstr(name, "(") + 1;
		char* seek = start;
		char* end = strstr(name, ")");
		for (int i = 0; i < argc-1; i++) {
			if(strstr(seek, ":"))
				seek = strstr(seek, ":")+1;
			char* comma_location = strstr(seek, ",");
			*comma_location = 0;
			args[i]=copy_string(seek);
			seek = comma_location + 1;
		}
		*end = 0;
		if (strstr(seek, ":"))
			seek = strstr(seek, ":") + 1;
 		args[argc - 1] = copy_string(seek);
		*start = 0;

		//remove_closing_brace(name);
		char* return_type = "void";
		if (strstr(name, " ")) {
			name = copy_string(name);
			return_type = name;
			char* space = strstr(name, " ");
			*space = 0;
			name = space + 1;
		}
			
		add_function(file, name, copy_string(parsed),argc,args,return_type);
		add_fun(context, name, &file->functions[file->i - 1]);
	}

	for (int i = 0; i < file->i; i++) {

		TokenStream tokens = tokenize(file->functions[i].expression, space_seperated_operators());

		file->functions[i].tree = parse(&tokens, 0,context);

	}
	return file;
}
FunctionContext* function_context_from_file(CCFile* file) {
	FunctionContext* fn_context = new_function_context();
	for (int i = 0; i < file->i; i++)
		set_function(fn_context, file->functions[i].name, &file->functions[i]);
	return fn_context;
}
static int read_file(char* source_code,char content[200][300]) {
	FILE* source_file = fopen(source_code, "r");
	if (source_file == 0)
		return printf("%s \t:no such file");
	char current;
	int lines_read = 0;
	while (fgets(content[lines_read++], 300, source_file) != 0)
		;
	lines_read--;
	return lines_read;
}
void repl2(char* source_code) {

	char content[100][300];
	int line = read_file(source_code, content);

	line = line - remove_comments(content, line);

	CCFile* file = parse_single_file(&content, line);
	Context* context = new_context();
	for (int i = 0; i < file->i; i++)
		add_fun(context, file->functions[i].name, &file->functions[i]);

	if (main_f(file))
		printf("blah\t%i\n", eval_Ast(main_f(file), context));
	else
		printf("no main defined in:\n %s\n",source_code);

}