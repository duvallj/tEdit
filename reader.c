#include <libndls.h>
#include <stdlib.h>
#include <stdio.h>

#include "reader.h"

vstring new_vstring(){
	vstring str;
	str.str = NULL;
	str.len = 0;

	return str;
}

vstring read_file(const char * filename) {
	vstring output;
	output.str = NULL;
	output.len = 0;

	FILE *fp = fopen(filename, "r");
	if (!fp) {
		show_msgbox("Error", "How'd you make that file not exist?");
		return output;
	}
	char *data = NULL;
	fseek(fp, 0, SEEK_END);
	size_t file_size = ftell(fp);
	if (!file_size) goto close_quit;
	data = malloc(file_size + 1);
	if (!data) goto close_quit;
	rewind(fp);
	if (fread(data, 1, file_size, fp) != file_size) {
		free(data);
		data = NULL;
close_quit:
		fclose(fp);
		return output;
	}
	fclose(fp);
	data[file_size] = '\0';
	file_size++;

	output.str = data;
	output.len = file_size;

	return output;
}

