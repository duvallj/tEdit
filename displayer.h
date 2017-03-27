#ifndef _DISPLAYER_H_
#define _DISPLAYER_H_

#include <libndls.h>

#include "llstring.h"
#include "font.h"

// -1 for some reason...
#define NUM_ROWS 	(29)
#define NUM_COLS	(40)
#define CHAR_H		(8)
#define CHAR_W		(8)

typedef struct
{
	line_t * current_line;
	line_t * topmost_line;
	unsigned int leftmost_index;
	uint8_t cursor_row;
	uint8_t displ_cursor_col;
	unsigned int actual_cursor_col;
	unsigned int ideal_cursor_col;
	uint16_t * buffer;
	scr_type_t scr_type;
	char mode;
	// 0 = editing
	// 1 = browsing files
	// 2 = filename editing in file browser
} screen;

extern void move_cursor_up(screen * sc);
extern void move_cursor_down(screen * sc);
extern void move_cursor_left(screen * sc);
extern void move_cursor_right(screen * sc);
extern void update_cursor(screen * sc, unsigned int old_row, unsigned int old_col, unsigned int new_row, unsigned int new_col, uint16_t fg, uint16_t bg);


extern void draw_text(screen * sc);
extern void load_text(screen * sc, vstring text);
extern void init_screen(screen * sc);
extern void deinit_screen(screen * sc);

#endif
