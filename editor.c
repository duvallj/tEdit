#include "editor.h"

clock_t last_clock = 0;

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
		if (sc->current_line->prev != NULL) {
			unsigned int old_row = sc->cursor_row;
			unsigned int old_col = sc->displ_cursor_col;
			
			line_t * cl = sc->current_line;
			line_t * pl = cl->prev;

			move_cursor_left(sc);

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

			draw_text(sc);
			update_cursor(sc, old_row, old_col, sc->cursor_row, sc->displ_cursor_col, 0xffff, 0x0000);
		}
	}
}

void insert_after_cursor(vstring * str, char c, unsigned int col) {

	char * buf = malloc((str->len+2)*sizeof(char));
	unsigned int index = 0;

	for (; index < col; index++) {
		buf[index] = str->str[index];
	}
	buf[index] = c;
	index++;
	for (; index <= str->len; index++) {
		buf[index] = str->str[index-1];
	}
	
	free(str->str);
	str->str = buf;
	str->len++;
}

void insert_char(screen * sc, uint16_t x, char mode) {
	switch (mode) {
		case 0:
			insert_after_cursor(sc->current_line->vstr, normal_keypress[x], sc->actual_cursor_col);
			break;
		case 1:
			insert_after_cursor(sc->current_line->vstr, shift_keypress[x], sc->actual_cursor_col);
			break;
		case 2:
			insert_after_cursor(sc->current_line->vstr, ctrl_keypress[x], sc->actual_cursor_col);
			break;
	}
	draw_text(sc);
	move_cursor_right(sc);
}

void insert_linebreak_after_cursor(screen * sc) {
	unsigned int old_col = sc->displ_cursor_col;
	unsigned int old_row = sc->cursor_row;

	line_t * cl = sc->current_line;
	unsigned int col = sc->actual_cursor_col;

	char * buf_upper = malloc((col+2)*sizeof(char));
	char * buf_lower = malloc((cl->vstr->len - col + 1)*sizeof(char));

	unsigned int iu = 0;
	unsigned int il = 0;
	unsigned int index = 0;
	
	for ( ; iu < col; iu++) {
		buf_upper[iu] = cl->vstr->str[index];
		index++;
	}
	buf_upper[iu] = '\n';
	iu++;
	buf_upper[iu] = '\0';

	unsigned int len = cl->vstr->len;
	for ( ; index < len; il++) {
		buf_lower[il] = cl->vstr->str[index];
		index++;
	}

	buf_lower[il] = '\0';

	free(cl->vstr->str);
	cl->vstr->str = buf_upper;
	cl->vstr->len = iu;

	line_t * new_line = malloc(sizeof(line_t));
	new_line->vstr = malloc(sizeof(vstring));
	new_line->vstr->str = buf_lower;
	new_line->vstr->len = il;
	
	insert_after(cl, new_line);
	move_cursor_down(sc);
	sc->displ_cursor_col = sc->actual_cursor_col = sc->ideal_cursor_col = 0;
	draw_text(sc);
	update_cursor(sc, old_row, old_col, sc->cursor_row, sc->displ_cursor_col, 0xffff, 0x0000);
}

void scan_keys(screen * sc) {
	clock_t cur_clock = clock();
	
	clock_t diff;
	
	if (cur_clock > last_clock) {
		diff = cur_clock - last_clock;
	} else {
		diff = (clock_t)1;
	}
	
	for (uint16_t x=0; x<EDITOR_ACTION_LEN; x++) {
		if (isKeyPressed(EDITOR_BUTTONS[x])) {
			if (!editor_keypress_duration[x]) {
				EDITOR_FUNCS[x](sc);
			}
			if (editor_keypress_duration[x] > ED_INITIAL_LOOP_COUNT) {
				EDITOR_FUNCS[x](sc);
				editor_keypress_duration[x] = ED_RESET_LOOP_COUNT;
			}
			editor_keypress_duration[x] += diff;
		} else {
			editor_keypress_duration[x] = 0;
		}
	}
	
	char mode = isKeyPressed(KEY_NSPIRE_SHIFT) ? 1 : isKeyPressed(KEY_NSPIRE_CTRL) ? 2 : 0;

	for(uint16_t x=0; x<INSERT_ACTION_LEN; x++) {
		if (isKeyPressed(INSERT_BUTTONS[x])) {
			if (!insert_keypress_duration[x]) {
				insert_char(sc, x, mode);
			}
			if (insert_keypress_duration[x] > IN_INITIAL_LOOP_COUNT) {
				insert_char(sc, x, mode);
				insert_keypress_duration[x] = IN_RESET_LOOP_COUNT;
			}
			insert_keypress_duration[x] += diff;
		} else {
			insert_keypress_duration[x] = 0;
		}
	}
	
	last_clock = cur_clock;
}
