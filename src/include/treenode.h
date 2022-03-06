#ifndef TREENODE_H
#define TREENODE_H
#include <stdlib.h>
typedef struct TREENODE_STRUCT {
	enum {
		TREENODE_NOOP,
		TREENODE_VARIABLE,
		TREENODE_VARIABLE_DEF,
		TREENODE_STRING,
		TREENODE_INT,
		TREENODE_FLOAT,
		TREENODE_FUNCTION_CALL,
		TREENODE_PLUS,
		TREENODE_MINUS,
		TREENODE_MUL,
		TREENODE_DIV,
	} type;
	struct TREENODE_STRUCT* left;
	struct TREENODE_STRUCT* right;
	struct TREENODE_STRUCT** children;
	size_t child_count;

	int row;
	int col;

	// TREENODE_VARIABLE
	char* variable_name;	

	// TREENODE_FUNCTION_CALL
	char* function_name;	
	
	// TREENODE_STRING
	char* string_value;

	// TREENODE_INT
	int int_value;

	// TREENODE_FLOAT
	float float_value;
} treenode_t;

char* treenode_to_str(treenode_t* node);

void treenode_print(treenode_t* node);

treenode_t* init_treenode_noop(int row, int col); 

treenode_t* init_treenode_variable(char* name, int row, int col);

treenode_t* init_treenode_string(char* name, int row, int col);

treenode_t* init_treenode_int(int value, int row, int col);

treenode_t* init_treenode_float(float value, int row, int col);

treenode_t* init_treenode_variable_def(treenode_t* left, treenode_t* right, int row, int col);

treenode_t* init_treenode_function_call(char* name, treenode_t** args, size_t args_size, int row, int col);

treenode_t* init_treenode_arithmetic(int type, treenode_t* left, treenode_t* right, int row, int col);
#endif
