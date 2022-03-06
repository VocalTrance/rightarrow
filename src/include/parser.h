#ifndef PARSER_H
#define PARSER_H
#include "treenode.h"
#include "lexer.h"
#include "ast.h"
typedef struct PARSER_STRUCT {
	lexer_t* lexer;
	token_t* cur_token;
	token_t* prev_token;
} parser_t;

parser_t* init_parser(lexer_t* lexer);

ast_t* parser_parse(parser_t* parser);
#endif
