#include "include/lexer.h"
#include "include/reader.h"
#include <stdio.h>
#include <stdlib.h>
#include "include/parser.h"
#include "include/visitor.h"




void _lex_all(lexer_t* lexer) {
	token_t* tok = lexer_next_token(lexer);
	printf("%s, %d\n", tok->value, tok->type);
	while (tok->type != TOKEN_EOF) {
		tok = lexer_next_token(lexer);
		printf("%s, %d\n", tok->value, tok->type);
	}
}

void _print_help() {
	printf("Usage:\n  ra.out <filename>\n");
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		_print_help();
		exit(1);
	}

	reader_t* reader = init_reader_from_file(argv[1]);
	lexer_t* lexer = init_lexer(reader);

	parser_t* parser = init_parser(lexer);
	ast_t* ast = parser_parse(parser);
	visitor_t* visitor = init_visitor(ast);
	visitor_visit(visitor);
	return 0;
}
