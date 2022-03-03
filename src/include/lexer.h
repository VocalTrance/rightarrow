#ifndef LEXER_H
#define LEXER_H
#include "reader.h"
#include "token.h"


typedef struct LEXER_STRUCT {
	reader_t* reader;
} lexer_t;

lexer_t* init_lexer(reader_t* reader);

token_t* lexer_next_token(lexer_t* lexer);
#endif
