#include "include/reader.h"
#include <stdlib.h>
#include <string.h>


reader_t* init_reader_from_string(char* contents) {
	reader_t* reader = calloc(1, sizeof(reader_t));
	reader->buffer = contents;
	reader->i = -1;
	reader->buffer_size = strlen(contents);
	reader->i_max = reader->buffer_size - 1;
}

reader_t* init_reader_from_file(FILE* f) {
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
	if (reader->i + k <= reader->i_max) {
		reader->i += k;
		return reader->buffer[reader->i];
	}
	return 0;
}

bool reader_is_eof(reader_t* reader) {
	return reader->i >= reader->i_max;
}

