#pragma once
#include <stdarg.h>
/*
* call this once in each textfile with all functions representing tests as arguments
* ex:
*  register_tests(&test1,&test2,&test3);
*/
//#define register_tests(...) _register_tests(__FILE__,sizeof( (void*[]){__VA_ARGS__}) / sizeof( void* ), __VA_ARGS__)
typedef void(*testing_function)(void);

#define register_tests(...) _register_tests(__FILE__,sizeof((testing_function[]){__VA_ARGS__}) / sizeof(testing_function), __VA_ARGS__)
#define name_test() _name(__func__)
typedef enum {equals_int,equals_string ,not_equals_string,not_equals_int}test_type;

void _register_tests(char* name,int n , ...);
void _name(char*);

void assert(test_type t,...);


void run_tests(void);