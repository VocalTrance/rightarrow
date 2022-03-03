#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// Declares functions only used in this file
token_t* _lex(lexer_t* lexer);

token_t* _lex_string(lexer_t* lexer);

token_t* _lex_ident(lexer_t* lexer);

token_t* _lex_number(lexer_t* lexer);


lexer_t* init_lexer(reader_t* reader) {
	lexer_t* lexer = calloc(1, sizeof(lexer_t));
	lexer->reader = reader;
	return lexer;
}

token_t* lexer_next_token(lexer_t* lexer) {
	return _lex(lexer);
}

token_t* _lex(lexer_t* lexer) {
	reader_t* reader = lexer->reader;
	if (!reader_is_eof(reader)) {
		char c = reader_peek(reader);

		// Save spaces to attach to front of next token
		char* spaces = calloc(1, sizeof(char));
		while (isspace(c)) {
			reader_consume(reader);
			size_t spaces_len = strlen(spaces);
			spaces = realloc(spaces, (spaces_len + 2) * sizeof(char));
			spaces[spaces_len] = c;
			c = reader_peek(reader);
		}
		
		token_t* token = (void*)0;
		switch (c) {
			case '"': token = _lex_string(lexer); break;
			default: {
					// Number state
					if (isdigit(c)) {
						token = _lex_number(lexer);
					} else if (isalnum(c)) {
						token = _lex_ident(lexer);
					} else if (reader_is_eof(reader)) {
						token = init_token(TOKEN_EOF, "");
					}
			}
		}

		if (token) {
			if (strlen(spaces)) {
				spaces = realloc(spaces, (strlen(spaces) + strlen(token->value) + 1) * sizeof(char));
				strcat(spaces, token->value);
				token = init_token(token->type, spaces);  
			}
			return token;
		} else {
			// Unknown character
			printf("Unknown character (%c, %d) at %d\n", c, c, reader->i + 1);
			exit(1);
		}
	}
	return init_token(TOKEN_EOF, "");
}

token_t* _lex_string(lexer_t* lexer) {
	reader_t* reader = lexer->reader;
	reader_consume(reader); // Consume '"'

	char* string = calloc(1, sizeof(char));
	char c = reader_peek(reader);
	while (c != '"' && !reader_is_eof(reader)) {
		reader_consume(reader);
		size_t string_len = strlen(string);
		string = realloc(string, (string_len + 2) * sizeof(char)); 
		string[string_len] = c;
		c = reader_peek(reader);
	}

	if (reader_is_eof(reader)) {
		// Unclosed string literal
	} else {
		reader_consume(reader); // Consume closing '"'
	}
	return init_token(TOKEN_STRING_L, string);
}

token_t* _lex_ident(lexer_t* lexer) {
	reader_t* reader = lexer->reader;

	char* string = calloc(1, sizeof(char));
	char c = reader_peek(reader);
	while (isalnum(c) && !reader_is_eof(reader)) {
		reader_consume(reader);
		size_t string_len = strlen(string);
		string = realloc(string, (string_len + 2) * sizeof(char)); 
		string[string_len] = c;
		c = reader_peek(reader);
	}

	return init_token(TOKEN_IDENT, string); 
}

token_t* _lex_number(lexer_t* lexer) {
	reader_t* reader = lexer->reader;

	int colon_found = 0;
	char* string = calloc(1, sizeof(char));
	char c = reader_peek(reader);
	while ((isdigit(c) || 
			 	(c == '.' && isdigit(reader_peek_k(reader, 2)) && colon_found < 1
				)) && !reader_is_eof(reader))
	{
		reader_consume(reader);
		size_t string_len = strlen(string);
		string = realloc(string, (string_len + 2) * sizeof(char)); 
		string[string_len] = c;
		if (c == '.') {
			colon_found += 1;
		}
		c = reader_peek(reader);
	}

	if (!colon_found) {
		return init_token(TOKEN_INT_L, string); 
	} else {
		return init_token(TOKEN_FLOAT_L, string);	
	}
}
