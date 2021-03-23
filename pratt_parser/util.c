#include <stdlib.h>
#include <string.h>

char* copy_string(char* str) { return strcpy(malloc((strlen(str) + 1) * sizeof(char)), str); }

int in(int n,char arr[], char c) {
	int rv = 1;

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