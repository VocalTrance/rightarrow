#ifndef READER_H
#define READER_H
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>


typedef struct READER_STRUCT {
	char* buffer;
	size_t buffer_size;
	int i;
	int i_max;
} reader_t; 

reader_t* init_reader_from_string(char* contents);

reader_t* init_reader_from_file(FILE* f);

char reader_peek(reader_t* reader);

char reader_peek_k(reader_t* reader, int k);

char reader_consume(reader_t* reader);

char reader_consume_k(reader_t* reader, int k);

bool reader_is_eof(reader_t* reader);
#endif
