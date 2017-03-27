#include "writer.h"

void write_file(const char * filename, const vstring data) {
	FILE * file = fopen(filename, "w");
	fwrite(data.str, sizeof(char), data.len, file);
	fclose(file);
}
