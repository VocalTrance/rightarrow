#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT {
	enum {
		TOKEN_EOF,

		TOKEN_IDENT,
		TOKEN_STRING_L,
		TOKEN_INT_L,
		TOKEN_FLOAT_L,
		TOKEN_COLON
	} type;
	char* value;
} token_t;

token_t* init_token(int type, char* value);
#endif
