#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"
#include "treenode.h"
#include <stdlib.h>
typedef struct VISITOR_STRUCT {
	ast_t* ast;
	treenode_t** variables;
	size_t variable_count;
} visitor_t;

visitor_t* init_visitor(ast_t* ast);

treenode_t* visitor_visit(visitor_t* visitor);

treenode_t* visitor_visit_node(visitor_t* visitor, treenode_t* node); 
#endif
