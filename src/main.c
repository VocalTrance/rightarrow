#include "include/lexer.h"
#include "include/reader.h"
#include <stdio.h>
#include <stdlib.h>
#include "include/parser.h"
#include "include/visitor.h"


int main(int argc, char* argv[]) {
	char* src = "honey= \"Honeeeey\";"
							"print(honey, \"Ok\")\n;"
							"print(\"hm...ok\");";

	reader_t* reader = init_reader_from_string(src);
	lexer_t* lexer = init_lexer(reader);
	parser_t* parser = init_parser(lexer);
	ast_t* ast = parser_parse(parser);
	visitor_t* visitor = init_visitor(ast);
	visitor_visit(visitor);
	return 0;
}
