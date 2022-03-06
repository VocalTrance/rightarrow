#include "include/builtin.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


static int is_initialized = 0;
static const size_t builtin_function_count = 1;
static char** builtin_functions; 

treenode_t* _print(visitor_t* visitor, treenode_t** args, size_t args_size) {
	for (int i = 0; i < args_size; i++) {
		treenode_t* arg = visitor_visit_node(visitor, args[i]);
		switch (arg->type) {
			case TREENODE_NOOP: break; // Ignore function calls with no return value
			case TREENODE_STRING: printf("%s ", arg->string_value); break;
		}
	}
	printf("\n");
	return init_treenode_noop(-1, -1);
}

void _init_builtin() {
	if (!is_initialized) {
		builtin_functions = calloc(builtin_function_count, sizeof(char*));
		builtin_functions[0] = "print";
		is_initialized = 1;
	}
}

int builtin_function_exists(char* function_name) {
	_init_builtin();
	for (int i = 0; i < builtin_function_count; i++) {
		if (strcmp(function_name, builtin_functions[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

treenode_t* builtin_call_function(visitor_t* visitor, treenode_t* function_call_node) {
	_init_builtin();
	char* name = function_call_node->function_name;
	treenode_t** args = function_call_node->children;
	size_t arg_count = function_call_node->child_count;

	if (strcmp(name, "print") == 0) {
		return	_print(visitor, args, arg_count);
	}
}

