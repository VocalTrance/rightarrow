#include "include/treenode.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* treenode_to_str(treenode_t* node) {
	char* buffer = calloc(1000, sizeof(char));
	switch (node->type) {
		case TREENODE_NOOP: return "TREENODE_NOOP";
		case TREENODE_VARIABLE: sprintf(buffer, "TREENODE_VARIABLE: %s", node->variable_name); break;
		case TREENODE_VARIABLE_DEF: sprintf(buffer, "TREENODE_VARIABLE_DEF: %s = %s", node->left->variable_name, node->right->string_value); break;
		case TREENODE_STRING: sprintf(buffer, "TREENODE_STRING: %s", node->string_value); break;
		case TREENODE_FUNCTION_CALL: sprintf(buffer, "TREENODE_FUNCTION_CALL: %s() %d arguments", node->function_name, node->child_count);
	}
	//char* args = calloc(2, sizeof(char));
	//size_t args_len = strlen(args);
	//for (int i = 0; i < node->child_count; i++) {
	//char* arg_str = treenode_to_str(node->children[i]);
	//args = realloc(args, (strlen(arg_str) + args_len) * sizeof(char));
	//strcat(args, arg_str);
	//args_len += strlen(arg_str);
	//}
	//sprintf(buffer, "TREENODE_FUNCTION_CALL: %s(%s)", node->function_name, args);
	//
	
	return buffer;
}

void treenode_print(treenode_t* node) {
	printf("%s\n", treenode_to_str(node));
}

treenode_t* _init_empty(int row, int col) {
	treenode_t* node = calloc(1, sizeof(treenode_t));
	node->type = TREENODE_NOOP;
	node->left = (void*)0;
	node->right = (void*)0;
	node->children = (void*)0;
	node->child_count = 0;
	node->row = row;
	node->col = col;

	node->variable_name = (void*)0;
	node->function_name = (void*)0;
	node->string_value = (void*)0;
	return node;
}


treenode_t* init_treenode_noop(int row, int col) {
	treenode_t* node = _init_empty(row, col);
	return node;
}

treenode_t* init_treenode_variable(char* name, int row, int col) {
	treenode_t* node = _init_empty(row, col);
	node->type = TREENODE_VARIABLE;
	node->variable_name = name;
	return node;
}

treenode_t* init_treenode_string(char* name, int row, int col) {
	treenode_t* node = _init_empty(row, col);
	node->type = TREENODE_STRING;
	node->string_value = name;
	return node;
}

treenode_t* init_treenode_variable_def(treenode_t* left, treenode_t* right, int row, int col) {
	treenode_t* node = _init_empty(row, col);
	node->type = TREENODE_VARIABLE_DEF;
	node->left = left;
	node->right = right;
	return node;
}

treenode_t* init_treenode_function_call(char* name, treenode_t** args, size_t args_size, int row, int col) {
	treenode_t* node = _init_empty(row, col);
	node->type = TREENODE_FUNCTION_CALL;
	node->function_name = name;
	node->children = args;
	node->child_count = args_size;
	return node;
}
