#include <stdlib.h>
#include <string.h>

char* copy_string(char* str) { return strcpy(malloc((strlen(str) + 1) * sizeof(char)), str); }