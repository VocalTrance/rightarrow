#include "include/reader.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


reader_t* init_reader_from_string(char* contents) {
	reader_t* reader = calloc(1, sizeof(reader_t));
	reader->buffer = contents;
	reader->i = 0;
	reader->buffer_size = strlen(contents);
	reader->i_max = reader->buffer_size - 1;
	reader->row = 1;
	reader->col = 1;
}

reader_t* init_reader_from_file(FILE* f) {
}

char reader_current_char(reader_t* reader) {
	return reader->buffer[reader->i];
}

char reader_peek(reader_t* reader) {
	return reader_peek_k(reader, 1);
}

char reader_peek_k(reader_t* reader, int k) {
	if (reader->i + k <= reader->i_max) {
		return reader->buffer[reader->i + k];
	}
	return 0;
}

char reader_consume(reader_t* reader) {
	return reader_consume_k(reader, 1);
}

char reader_consume_k(reader_t* reader, int k) {
	int n = reader->i + k;
	if (n <= reader->i_max) {
		// Set new row and column
		for (int j = reader->i + 1; j <= n; j++) {
			char c = reader->buffer[j];
			if (c == '\n') {
				reader->row += 1;
				reader->col = 0;
			} else {
				reader->col += 1;
			}
			// printf("Now looking at char %c at (%d, %d)\n", c, reader->row, reader->col);
		}

//		printf("Now looking at char %c at (%d, %d)\n", reader->buffer[reader->i], reader->row, reader->col);
		reader->i = n;
		return reader->buffer[n];
	}
	return 0;
}

bool reader_is_eof(reader_t* reader) {
	return reader->i >= reader->i_max;
}

