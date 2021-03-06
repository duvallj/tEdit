#ifndef READER_H
#define READER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define freeinn(X) if (X != NULL){free(X);}

typedef struct
{
	char * str;
	size_t len;
} vstring;

extern vstring new_vstring();
extern vstring concat(vstring a, vstring b);
extern vstring read_file(const char * filename);

#endif // READER_H
