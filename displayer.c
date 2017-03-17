#include "displayer.h"

const uint16_t white = 0xffff;
const uint16_t black = 0x00;

void init_screen(screen * sc) {
	sc->buffer = malloc(320*240*sizeof(uint16_t));
	sc->scr_type = lcd_type() == SCR_320x240_4 ? SCR_320x240_4 : SCR_320x240_565;
	lcd_init(sc->scr_type);
	memset(sc->buffer, 0, 320*240*sizeof(uint16_t));
}

void deinit_screen(screen * sc) {
	free(sc->buffer);
	lcd_init(SCR_TYPE_INVALID);
}

void set_pixel(screen * sc, uint16_t x, uint16_t y, uint16_t c) {
	unsigned int spot = 320*y+x;
	if (sc->scr_type == SCR_320x240_565) {
		sc->buffer[spot] = c;
	} else { // Haven't tested the part below
		memcpy(sc->buffer, &c, 1);
	}
}

uint16_t rgb_to_color(unsigned char r, unsigned char g, unsigned char b) {
	if (lcd_type() != SCR_320x240_4) {
		return ((r&0x1f)<<11) + ((g&0x3f)<<5) + (b&0x1f);
	} else {
		return (r+g+b) / 4;
	}
	return 0;
}

void draw_char(screen * sc, uint8_t row, uint8_t col, char c, uint16_t fg, uint16_t bg) {
	uint64_t bitmap = font[(int)c];
	for ( uint8_t y=0; y<CHAR_H; y++) {
		for ( uint8_t x=0; x<CHAR_W; x++) {
			set_pixel(sc, col*CHAR_W+x, row*CHAR_H+y, (bitmap>>(63-8*y-x))&1 ? fg : bg);
		}
	}
}

void draw_text(screen * sc) {
	memset(sc->buffer, 0, 320*240*sizeof(uint16_t));
	//uint16_t white = rgb_to_color(0x1f, 0x3f, 0x1f);
	//uint16_t black = rgb_to_color(0,0,0);
	line_t * cl = sc->topmost_line;
	for (uint8_t row=0; row<=NUM_ROWS && cl != NULL; row++) {
		for(uint8_t col=0; col<NUM_COLS && col+sc->leftmost_index < cl->vstr->len-1; col++ ) {
			draw_char(sc, row, col, cl->vstr->str[sc->leftmost_index + col], white, black);
		}
		cl = cl->next;
	}
	
	lcd_blit(sc->buffer, sc->scr_type);
}

void update_cursor(screen * sc,
		unsigned int old_row, unsigned int old_col, 
		unsigned int new_row, unsigned int new_col,
		uint16_t fg, uint16_t bg) {
	for (uint8_t y=0; y<CHAR_H; y++) {
		set_pixel(sc, old_col*CHAR_W, old_row*CHAR_H+y, bg);
		set_pixel(sc, new_col*CHAR_W, new_row*CHAR_H+y, fg);
	}

	lcd_blit(sc->buffer, sc->scr_type);
}


void adjust_cursor_col(screen * sc) {
	unsigned int icc, acc, lnl, lmi;
	icc = sc->ideal_cursor_col;
	acc = sc->actual_cursor_col;
	lnl = sc->current_line->vstr->len-1;
	lmi = sc->leftmost_index;
	if (icc > lnl) {
		sc->actual_cursor_col = lnl;
	} else {
		sc->actual_cursor_col = icc;
	}
	acc = sc->actual_cursor_col;
	if (acc < lmi) {
		sc->leftmost_index = acc;
		draw_text(sc);
	}
	if (acc > lmi + NUM_COLS - 1) {
		sc->leftmost_index = acc - NUM_COLS + 1;
		draw_text(sc);
	}
	lmi = sc->leftmost_index;
	sc->displ_cursor_col = acc - lmi;
}

void move_cursor_up(screen * sc) {
	if (sc->current_line->prev != NULL) {
		bool redraw = 0;
		unsigned int old_row = sc->cursor_row;
		unsigned int old_col = sc->displ_cursor_col;
		if (sc->cursor_row > 0) {
			sc->cursor_row--;
		} else {
			// If and only if current_line's prev is null,
			// then so will be this one.
			sc->topmost_line = sc->topmost_line->prev;
			redraw = 1;
		}
		sc->current_line = sc->current_line->prev;
		adjust_cursor_col(sc);
		if (redraw) draw_text(sc);
		update_cursor(sc, old_row, old_col, sc->cursor_row, sc->displ_cursor_col, white, black);
	}
}

void move_cursor_down(screen * sc) {
	if (sc->current_line->next != NULL) {
		bool redraw = 0;
		unsigned int old_row = sc->cursor_row;
		unsigned int old_col = sc->displ_cursor_col;
		if (sc->cursor_row < NUM_ROWS) {
			sc->cursor_row++;
		} else {
			sc->topmost_line = sc->topmost_line->next;
			redraw = 1;
		}
		sc->current_line = sc->current_line->next;
		adjust_cursor_col(sc);
		if (redraw) draw_text(sc);
		update_cursor(sc, old_row, old_col, sc->cursor_row, sc->displ_cursor_col, white, black);
	}
}

void move_cursor_left(screen * sc) {
	unsigned int old_row = sc->cursor_row;
	unsigned int acc = sc->actual_cursor_col;
	unsigned int old_col = sc->displ_cursor_col;
	if (acc > 0) {
		acc--;
	} else {
		bool wrap = sc->current_line->prev != NULL;
		move_cursor_up(sc);
		old_row = sc->cursor_row;
		old_col = sc->displ_cursor_col;
		if (wrap) {
			acc = sc->current_line->vstr->len-1;
		}
	}
	sc->ideal_cursor_col = sc->actual_cursor_col = acc;
	if (acc < sc->leftmost_index) {
		sc->leftmost_index = acc;
		draw_text(sc);
	}
	sc->displ_cursor_col = sc->actual_cursor_col - sc->leftmost_index;
	update_cursor(sc, old_row, old_col, sc->cursor_row, sc->displ_cursor_col, white, black);

}

void move_cursor_right(screen * sc) {
	unsigned int old_row = sc->cursor_row;
	unsigned int acc = sc->actual_cursor_col;
	unsigned int old_col = sc->displ_cursor_col;
	if (acc < sc->current_line->vstr->len-1) {
		acc++;
	} else {
		bool wrap = sc->current_line->next != NULL;
		move_cursor_down(sc);
		old_row = sc->cursor_row;
		old_col = sc->displ_cursor_col;
		if (wrap) {
			acc = 0;
		}
	}
	sc->ideal_cursor_col = acc;
	sc->actual_cursor_col = acc;
	if (acc > sc->leftmost_index + NUM_COLS - 1) {
		sc->leftmost_index = acc - NUM_COLS + 1;
		draw_text(sc);
	}
	sc->displ_cursor_col = sc->actual_cursor_col - sc->leftmost_index;
	update_cursor(sc, old_row, old_col, sc->cursor_row, sc->displ_cursor_col, white, black);
}



void load_text(screen * sc, vstring text) {
	sc->topmost_line = string_to_llist(text);
	sc->current_line = sc->topmost_line;
	sc->leftmost_index = 0;
	sc->cursor_row = 0;
	sc->actual_cursor_col = 0;
	sc->ideal_cursor_col = 0;
	sc->displ_cursor_col = 0;
}
