#include <libndls.h>

#include "llstring.h"

typedef struct
{
	node_t * before;
	node_t * after;
	// Not memory efficient, but I want to handle
	// big files too.
	long line;
	long col;
	short rel_line;
	short rel_col;
} cursor;
