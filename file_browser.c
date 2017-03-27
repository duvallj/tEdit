#include "file_browser.h"

void move_fb_cursor_up(screen * sc) {
	if (sc->mode == 2) {
		toggle_filename_browsing(sc);
	} else {
		if (sc->current_line->prev != NULL) {
			if(sc->cursor_row > 0) {
				sc->cursor_row--;
			} else {
				sc->topmost_line = sc->topmost_line->prev;
			}
			sc->current_line = sc->current_line->prev;
			draw_fb(sc);
		}
	}
}

void move_fb_cursor_down(screen * sc) {
	if (sc->current_line->next != NULL) {
		if (sc->cursor_row < NUM_ROWS - LINES_BEFORE - LINES_AFTER) {
			sc->cursor_row++;
		} else {
			sc->topmost_line = sc->topmost_line->next;
		}
		sc->current_line = sc->current_line->next;
		draw_fb(sc);
	}
}

void move_fb_cursor_left(screen * sc) {
	if (sc->mode == 1) {
		toggle_filename_browsing(sc);
	}
	
	// unsigned int acc = sc->actual_cursor_col;
	unsigned int old_col = sc->displ_cursor_col;

	if (sc->actual_cursor_col > 0) {
		sc->actual_cursor_col--;
	}
	if (sc->actual_cursor_col < sc->leftmost_index) {
		sc->leftmost_index = acc;
		draw_fb(sc);
	}
	sc->displ_cursor_col = sc->actual_cursor_col - sc->leftmost_index;
	update_cursor(sc, sc->cursor_row, old_col, sc->cursor_row, sc->displ_cursor_col, white, black);
}

void move_fb_cursor_right(screen * sc) {
	if (sc->mode == 1) {
		toggle_filename_browsing(sc);
	}

	unsigned int old_col = sc->displ_cursor_col;

	if (sc->actual_cursor_col < sc->current_line->vstr->len) {
		sc->actual_cursor_col++;
	}

	if (sc->actual_cursor_col > sc->leftmost_index + NUM_COLS - 1) {
		sc->leftmost_index = sc->actual_cursor_col - NUM_COLS + 1;
		draw_fb(sc);
	}
	sc->displ_cursor_col = sc->actual_cursor_col - sc->leftmost_index;
	update_cursor(sc, sc->cursor_row, old_col, sc->cursor_row, sc->displ_cursor_col, white, black);
}

vstring * current_directory_header;
vstring * current_directory;

vstring * filename_header;
vstring * filename;

void toggle_filename_browsing(screen * sc) {
	if (sc->mode == 1) {
		sc->current_line = 
	}
	else if (sc->mode == 2) {

	}
}

void switch_to_editing(screen * sc) {

}

void draw_fb(screen * sc) {

}

void set_current_directory_string() {
	char cd[FILENAME_MAX];
	getcwd(cd, sizeof(cd));
	free(current_directory->str);
	current_directory->str = cd;
	current_directory->len = sizeof(cd)-1;
}

void init_fb() {
	current_directory_header = malloc(sizeof(vstring));
	current_directory_header->str = "Current Directory:";
	current_directory_header->len = 18;

	current_directory = malloc(sizeof(vstring));
	current_directory->str = malloc(sizeof(char));
	set_current_directory_string();
	
	filename_header = malloc(sizeof(vstring));
	filename_header->str = "Filename:";
	filename_header->len = 9;

	filename = malloc(sizeof(vstring));
	filename->str = "."; // Should be the first entry, anyway
	filename->len = 1;

	// TODO: also init all the files for the filenames
}

void deinit_fb() {
	free(current_directory_header->str);
	free(current_directory_header);

	free(current_directory->str);
	free(current_directory);

	free(filename_header->str);
	free(filename_header);

	free(filename->str);
	free(filename);

	// TODO: free all the lines that represent files
	// Or maybe that's for the method where I load a new directory. IDK
}

void init_fb_buttons() {
	FB_FUNCS[0] = KEY_NSPIRE_UP;
	FB_FUNCS[1] = KEY_NSPIRE_DOWN;
	FB_FUNCS[2] = KEY_NSPIRE_LEFT;
	FB_FUNCS[3] = KEY_NSPIRE_RIGHT;
	FB_FUNCS[4] = KEY_NSPIRE_DEL;
	FB_FUNCS[5] = KEY_NSPIRE_TAB;
	FB_FUNCS[6] = KEY_NSPIRE_ENTER;
	FB_FUNCS[7] = KEY_NSPIRE_RET;
}
