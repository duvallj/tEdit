#ifndef _LLSTRING_H_
#define _LLSTRING_H_

#include <stdlib.h>
#include <string.h>

#include "reader.h"

typedef struct line
{
	vstring * vstr;
	struct line * next;
	struct line * prev;
} line_t;

extern void init_line_t_ptr(line_t * node);
extern line_t * string_to_llist(vstring str);
extern vstring llist_to_string(line_t * head);
extern void insert_after(line_t * node, line_t * newnode);
extern void insert_before(line_t * node, line_t * newnode);

extern void debug(unsigned int value);

#endif
