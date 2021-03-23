#include "Context.h"

Context* new_context() {
	Context* rv = malloc(sizeof(Context));
	rv->keys = new_TokenStream();
	rv->values = new_TokenStream();
	return rv;
}
int get_value(Context* context, char* key) {
	TokenStream keys = context->keys;
	TokenStream values = context->values;
	while (has_next(&keys)) {
		char* current_key = next(&keys);
		next(&values);
		if (strcmp(key, current_key) == 0)
			return (int)values.tokens[values.pos - 1];
	}
}

int has_key(Context* context, char* key) {
	TokenStream keys = context->keys;
	while (has_next(&keys)) {
		char* current_key = next(&keys);
		if (strcmp(key, current_key) == 0)
			return 1;
	}
	return 0;
}

int set_value(Context* con, char* key, int val) {
	printf("settinf value: %i", val);
	TokenStream keys = con->keys;
	TokenStream values = con->keys;

	while (has_next(&keys)) {
		char* current_key = next(&keys);
		next(&values);
		if (strcmp(key, current_key) == 0)
			return (int)values.tokens[values.pos - 1] = (char*)val;
	}
	push(&con->keys, key);
	push(&con->values, (char*)val);
	return val;
}

void print_context(Context* c) {
	TokenStream keys = c->keys;
	TokenStream values = c->values;
	while (has_next(&keys)) {
		printf("%s: %i\n", next(&keys), next(&values));
	}
	return 0;
}