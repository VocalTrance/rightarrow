#include "include/parser.h"
#include <stdlib.h>

// Defines static functions
void _parser_eat(parser_t* parser, int token_type);

treenode_t* _parse_statement(parser_t* parser);

treenode_t* _parse_expr(parser_t* parser);

treenode_t* _parse_string(parser_t* parser);

treenode_t* _parse_int(parser_t* parser);

treenode_t* _parse_float(parser_t* parser);

treenode_t* _parse_variable(parser_t* parser);

treenode_t* _parse_variable_def(parser_t* parser);

treenode_t* _parse_function_call(parser_t* parser);

treenode_t* F(parser_t* parser);

treenode_t* T(parser_t* parser);

treenode_t* E(parser_t* parser);

parser_t* init_parser(lexer_t* lexer) {
	parser_t* parser = calloc(1, sizeof(parser_t));
	parser->lexer = lexer;
	parser->cur_token = lexer_next_token(lexer);
	parser->prev_token = (void*)0;
	return parser;
}

ast_t* parser_parse(parser_t* parser) {
	ast_t* ast = init_ast();	

	treenode_t* node = _parse_statement(parser);
	treenode_print(node);
	ast_add_statement(ast, node);
	while (parser->cur_token->type == TOKEN_SEMI) {
		_parser_eat(parser, TOKEN_SEMI);
		node = _parse_statement(parser);
		if (node == (void*)0) {
			break;
		} else {
			ast_add_statement(ast, node);
			treenode_print(node);
		}
	}

	return ast;
}

void _parser_eat(parser_t* parser, int token_type) {
	token_t* current = parser->cur_token;
	if (current->type == token_type) {
		parser->cur_token = lexer_next_token(parser->lexer);
		parser->prev_token = current;
	} else {
		printf("Unexpected token %s with type %d\n", current->value, current->type);
		exit(1);
	}
}

treenode_t* _parse_statement(parser_t* parser) {
	token_t* token = parser->cur_token;
	switch (token->type) {
		case TOKEN_EOF: return (void*)0;
		case TOKEN_IDENT: 
			_parser_eat(parser, TOKEN_IDENT);
			if (parser->cur_token->type == TOKEN_LPAREN) {
				return _parse_function_call(parser);
			} else if (parser->cur_token->type == TOKEN_EQUALS) {
				return _parse_variable_def(parser);
			}
	}
	printf("Failed to parse statement with token %s of type %d\n", token->value, token->type);
	exit(1);
}

treenode_t* F(parser_t* parser) {
	token_t* cur_token = parser->cur_token;
	switch (cur_token->type) {
		case TOKEN_IDENT: return _parse_variable(parser);
		case TOKEN_INT_L: return _parse_int(parser);
		case TOKEN_LPAREN:
			_parser_eat(parser, TOKEN_LPAREN);
			treenode_t* a = E(parser);
			_parser_eat(parser, TOKEN_RPAREN);
			return a;
	}
}

treenode_t* T(parser_t* parser) {
	treenode_t* a = F(parser);
	token_t* cur_token = parser->cur_token;
	while (true) {
		switch (cur_token->type) {
			case TOKEN_MUL:
				_parser_eat(parser, TOKEN_MUL);
				treenode_t* b = F(parser);
				a = init_treenode_arithmetic(TREENODE_MUL, a, b, a->row, a->col);
				break;
			case TOKEN_DIV:
				_parser_eat(parser, TOKEN_DIV);
				b = F(parser);
				a = init_treenode_arithmetic(TREENODE_DIV, a, b, a->row, a->col);
				break;
			default:
				return a;
		}
	}
}

treenode_t* E(parser_t* parser) {
	treenode_t* a = T(parser);
	token_t* cur_token = parser->cur_token;
	while (true) {
		switch (cur_token->type) {
			case TOKEN_PLUS:
				_parser_eat(parser, TOKEN_PLUS);
				treenode_t* b = T(parser);
				a = init_treenode_arithmetic(TREENODE_PLUS, a, b, a->row, a->col);
				break;
			case TOKEN_MINUS:
				_parser_eat(parser, TOKEN_MINUS);
				b = T(parser);
				a = init_treenode_arithmetic(TREENODE_MINUS, a, b, a->row, a->col);
				break;
			default:
				return a;
		}
	}
}


treenode_t* _parse_expr(parser_t* parser) {
	token_t* cur_token = parser->cur_token;
	switch (cur_token->type) {
		case TOKEN_STRING_L: return _parse_string(parser);
		case TOKEN_INT_L: return _parse_int(parser); 
		case TOKEN_FLOAT_L: return _parse_float(parser); 
		case TOKEN_IDENT: 
			_parser_eat(parser, TOKEN_IDENT);
			if (parser->cur_token->type == TOKEN_LPAREN) {
				return _parse_function_call(parser);
			} else {
				return _parse_variable(parser); 
			}
	}
	printf("Failed to parse expression %s of type %d\n", cur_token->value, cur_token->type);
	exit(1);
}

treenode_t* _parse_string(parser_t* parser) {
	_parser_eat(parser, TOKEN_STRING_L);
	return init_treenode_string(parser->prev_token->value, parser->prev_token->row, parser->prev_token->col);
}

treenode_t* _parse_int(parser_t* parser) {
	_parser_eat(parser, TOKEN_INT_L);
	long value = strtol(parser->prev_token->value, (void*)0, 10);
	return init_treenode_int(value, parser->prev_token->row, parser->prev_token->col);
}

treenode_t* _parse_float(parser_t* parser) {
	_parser_eat(parser, TOKEN_FLOAT_L);
	float value = strtof(parser->prev_token->value, (void*)0);
	return init_treenode_float(value, parser->prev_token->row, parser->prev_token->col);
}

treenode_t* _parse_variable(parser_t* parser) {
	return init_treenode_variable(parser->prev_token->value, parser->prev_token->row, parser->prev_token->col);
}

treenode_t* _parse_variable_def(parser_t* parser) {
	token_t* ident = parser->prev_token;
	_parser_eat(parser, TOKEN_EQUALS);

	treenode_t* left = init_treenode_variable(ident->value, parser->prev_token->row, parser->prev_token->col);
	treenode_t* right = _parse_expr(parser);
	treenode_t* node = init_treenode_variable_def(left, right, parser->prev_token->row, parser->prev_token->col);
	return node;
}

treenode_t* _parse_function_call(parser_t* parser) {
	token_t* ident = parser->prev_token;
	_parser_eat(parser, TOKEN_LPAREN);
	
	treenode_t** children = calloc(1, sizeof(treenode_t*));
	size_t child_count = 0;
	if (parser->cur_token->type == TOKEN_RPAREN) {
		treenode_t* node = init_treenode_function_call(ident->value, children, child_count, parser->prev_token->row, parser->prev_token->col);
		return node;
	}

	children[0] = _parse_expr(parser);
	child_count += 1;

	while (parser->cur_token->type == TOKEN_COMMA) {
		_parser_eat(parser, TOKEN_COMMA);
		if (parser->cur_token->type == TOKEN_RPAREN) {
			break;
		}

		children = realloc(children, (child_count + 1) * sizeof(treenode_t*));
		children[child_count] = _parse_expr(parser);
		child_count += 1;
	}
	_parser_eat(parser, TOKEN_RPAREN);

	treenode_t* node = init_treenode_function_call(ident->value, children, child_count, parser->prev_token->row, parser->prev_token->col);
	return node;
}
