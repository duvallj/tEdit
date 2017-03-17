#ifndef _READER_H_
#define _READER_H_

#include <string.h>

typedef struct
{
	char * str;
	size_t len;
} vstring;

extern vstring new_vstring();
extern vstring read_file(const char * filename);

#endif
