#include "include/lexer.h"
#include "include/reader.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
	char* src = "int xd \"MySTRINGERO\" int x 12 int y 234.234 int xy 23.33.33   ";
	reader_t* reader = init_reader_from_string(src);
	lexer_t* lexer = init_lexer(reader);
	token_t* tok = lexer_next_token(lexer);
	printf("Token (%d, %s)\n", tok->type, tok->value);
	while (tok->type != TOKEN_EOF) {
		tok = lexer_next_token(lexer);
		printf("Token (%d, %s)\n", tok->type, tok->value);
	}
	return 0;
}
