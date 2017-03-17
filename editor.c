#include "editor.h"

void delete_before_cursor(screen * sc) {
	if (sc->actual_cursor_col) {
		vstring * st = sc->current_line->vstr;
		uint16_t ac = sc->actual_cursor_col;
		uint16_t x=0;
		char * new_buffer = malloc(st->len*sizeof(char));
		for ( ; x<ac-1; x++) {
			new_buffer[x] = st->str[x];
		}
		for( ; x<st->len-1; x++ ) {
			new_buffer[x] = st->str[x+1];
		}
		new_buffer[x] = '\0';
		free(st->str);
		st->str = new_buffer;
		st->len--;
		draw_text(sc);
		move_cursor_left(sc);
	} else {
		// TODO: fix this
		if (sc->current_line->prev != NULL) {
			move_cursor_left(sc);
			
			line_t * cl = sc->current_line;
			line_t * pl = cl->prev;
			pl->vstr->str[pl->vstr->len-1] = '\0';

			char * new_buffer = malloc((pl->vstr->len + cl->vstr->len)*sizeof(char));
			uint16_t x=0;
			
			for ( ; x < pl->vstr->len - 1; x++ ) {
				new_buffer[x] = pl->vstr->str[x];
			}
			for ( uint16_t y=0; y < cl->vstr->len; y++ ) {
				new_buffer[x] = cl->vstr->str[y];
				x++;
			}
			
			new_buffer[x] = '\0';
			free(pl->vstr->str);
			pl->vstr->str = new_buffer;
			pl->vstr->len = pl->vstr->len + cl->vstr->len - 1;

			if (cl->next != NULL) {
				pl->next = cl->next;
				cl->next->prev = pl;
			} else {
				pl->next = NULL;
			}
			cl->next = NULL;
			cl->prev = NULL;

			free(cl->vstr->str);
			free(cl->vstr);
			free(cl);

			sc->current_line = pl;
			if (sc->cursor_row) {
				sc->cursor_row--;
			}
			draw_text(sc);
		}
	}
}

void scan_keys(screen * sc) {
	for (uint16_t x=0; x<EDITOR_ACTION_LEN; x++) {
		if (isKeyPressed(EDITOR_BUTTONS[x])) {
			if (!editor_keypress_duration[x]) {
				EDITOR_FUNCS[x](sc);
			}
			if (editor_keypress_duration[x] > INITIAL_LOOP_COUNT) {
				EDITOR_FUNCS[x](sc);
				editor_keypress_duration[x] = RESET_LOOP_COUNT;
			}
			editor_keypress_duration[x]++;
		} else {
			editor_keypress_duration[x] = 0;
		}
	}

	// for (uint16_t x=0; x<
}

void init_editor_buttons() {
	EDITOR_BUTTONS[0] = KEY_NSPIRE_UP;
	EDITOR_BUTTONS[1] = KEY_NSPIRE_DOWN;
	EDITOR_BUTTONS[2] = KEY_NSPIRE_LEFT;
	EDITOR_BUTTONS[3] = KEY_NSPIRE_RIGHT;
	EDITOR_BUTTONS[4] = KEY_NSPIRE_DEL;
}
