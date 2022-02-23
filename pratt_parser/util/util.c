#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* copy_string(char* str) { 
	char* cpy = malloc((strlen(str) + 1) * sizeof(char));
	if(cpy)
		return strcpy(cpy , str); 
return 0;}

int in(int n,char arr[], char c) {
	for (int i = 0; i < n; i++)
		if (arr[i] == c)
			return 1;
	return 0;
}

int is_number(char* str) {
	char number_chars[] = { '0','1','2','3','4','5','6','7','8','9','-' };
	while (*str)
		if (in(sizeof(number_chars), number_chars, *str++))
			continue;
		else
			return 0;
	return 1;
}

void* exit_on_null(void* ptr) {
	if (ptr)
		return ptr;
	else
	{
		printf("\nmemory allocation failed\n");
		
		exit(0);
	}
}