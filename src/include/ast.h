#ifndef AST_H
#define AST_H
#include "treenode.h"
#include <stdlib.h>
typedef struct AST_STRUCT {
	treenode_t** statements;
	size_t statements_size;
} ast_t;

ast_t* init_ast();

void ast_add_statement(ast_t* ast, treenode_t* statement);
#endif
