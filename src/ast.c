#include "include/ast.h"
#include <stdlib.h>

ast_t* init_ast() {
	ast_t* ast = calloc(1, sizeof(ast_t*));
	ast->statements = calloc(1, sizeof(treenode_t*));
	ast->statements_size = 0;
	return ast;
}

void ast_add_statement(ast_t* ast, treenode_t* statement) {
	ast->statements = realloc(
		ast->statements, 
		(ast->statements_size + 1) * sizeof(treenode_t*)
	);
	ast->statements[ast->statements_size] = statement;
	ast->statements_size += 1;
}
