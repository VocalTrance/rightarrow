#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT {
	enum {
		TOKEN_EOF,
		TOKEN_IDENT,
		TOKEN_STRING_L,
		TOKEN_INT_L,
		TOKEN_FLOAT_L,
		TOKEN_COLON,
		TOKEN_EQUALS,
		TOKEN_SEMI,
		TOKEN_COMMA,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
	} type;
	char* value;
	int row;
	int col;
} token_t;

token_t* init_token(int type, char* value, int row, int column);
#endif
