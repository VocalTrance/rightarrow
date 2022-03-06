#ifndef BUILTIN_H
#define BUILTIN_H
#include <stdlib.h>
#include "visitor.h"
#include "treenode.h"

int builtin_function_exists(char* function_name);

treenode_t* builtin_call_function(visitor_t* visitor, treenode_t* function_call_node);
#endif
