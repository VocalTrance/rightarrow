#include "include/visitor.h"
#include "include/builtin.h"
#include <stdio.h>
#include <string.h>

treenode_t* _visit_function_call(visitor_t* visitor, treenode_t* node);

treenode_t* _visit_variable_def(visitor_t* visitor, treenode_t* node);

treenode_t* _visit_variable(visitor_t* visitor, treenode_t* node);

treenode_t* _visit_string(visitor_t* visitor, treenode_t* node);

visitor_t* init_visitor(ast_t* ast) {
	visitor_t* visitor = calloc(1, sizeof(visitor_t));
	visitor->ast = ast;
	visitor->variables = (void*)0;
	visitor->variable_count = 0;
	return visitor;
}

treenode_t* visitor_visit(visitor_t* visitor) {
	for (int i = 0; i < visitor->ast->statements_size; i++) {
		treenode_t* to_visit = visitor->ast->statements[i];
		visitor_visit_node(visitor, to_visit);
	}
	return init_treenode_noop(-1, -1);
}


treenode_t* visitor_visit_node(visitor_t* visitor, treenode_t* node) {
	switch (node->type) {
		case TREENODE_VARIABLE_DEF: return _visit_variable_def(visitor, node);
		case TREENODE_FUNCTION_CALL: return _visit_function_call(visitor, node);
		case TREENODE_VARIABLE: return _visit_variable(visitor, node);
		case TREENODE_STRING: return _visit_string(visitor, node);
	}
	return init_treenode_noop(-1, -1);
}

treenode_t* _visit_function_call(visitor_t* visitor, treenode_t* node) {
	if (builtin_function_exists(node->function_name)) {
		return builtin_call_function(visitor, node);
	} else {
	printf("(%d, %d): No function with name %s\n", node->row, node->col, node->function_name);
		exit(1);
	}
}

treenode_t* _visit_variable_def(visitor_t* visitor, treenode_t* node) {
	if (visitor->variables == (void*)0) {
		visitor->variables = calloc(1, sizeof(treenode_t*));
	} else {
		visitor->variables = realloc(
			visitor->variables, 
			(visitor->variable_count + 1) * sizeof(treenode_t*)
		);
	}

	visitor->variables[visitor->variable_count] = node;
	visitor->variable_count += 1;
	return node;
}

treenode_t* _visit_variable(visitor_t* visitor, treenode_t* node) {
	for (int i = 0; i < visitor->variable_count; i++) {
		treenode_t* vardef = visitor->variables[i];
		if (strcmp(vardef->left->variable_name, node->variable_name) == 0) {
			return visitor_visit_node(visitor, vardef->right);
		}
	}

	printf("(%d, %d): Undefined variable %s\n", node->row, node->col, node->variable_name);
	exit(1);
}

treenode_t* _visit_string(visitor_t* visitor, treenode_t* node) {
	return node;
}
