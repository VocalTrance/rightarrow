#include "include/token.h"
#include <stdlib.h>


token_t* init_token(int type, char* value) {
	token_t* tok = calloc(1, sizeof(token_t));
	tok->type = type;
	tok->value = value;
	return tok;
}
