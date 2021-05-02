#include <stdio.h>
#include <string.h>
#include "Context.h"
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


static void add_function(CCFile* file, char* name, char* expression, int argc, char** args) {
	file->functions[file->i].name = name;
	file->functions[file->i].expression = expression;
	file->functions[file->i].arg_count = argc;
	file->functions[file->i].args = args;
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
	int commas = 0;
	while (*name != 0)
		if (*name++ == ',')
			commas++;
	return commas + 1;

}
static CCFile* parze(char lines[100][300], int n) {
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
				current_tabs = count_tabs(lines[i]);
				*writer++ = ')';
				*writer = 0;
				*writer++ = ',';
				*writer = 0;
				writer = strcat(writer, &lines[i][current_tabs]) + strlen(&lines[i][current_tabs]);
				start_of_block = 0;
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
			char* comma_location = strstr(seek, ",");
			*comma_location = 0;
			args[i]=copy_string(seek);
			seek = comma_location + 1;
		}
		*end = 0;
		args[argc - 1] = copy_string(seek);
		*start = 0;

		//remove_closing_brace(name);
		
		add_function(file, name, copy_string(parsed),argc,args);
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
void repl2(char* source_code) {

	 

	char content[100][300];
	FILE* source_file = fopen(source_code, "r");
	char current;
	int line = 0;
	while (fgets(content[line++], 300, source_file) != 0)
		;
	line--;
	line = line - remove_comments(content, line);
	CCFile* file = parze(content, line);
	Context* context = new_context();
	for (int i = 0; i < file->i; i++)
		add_fun(context, file->functions[i].name, &file->functions[i]);


	printf("blah\t%i\n",eval_Ast(main_f(file), context));
	int i = 0;
	context = new_context();

}