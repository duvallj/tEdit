#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "displayer.h"
#include <libndls.h>
#include <keys.h>

#define EDITOR_ACTION_LEN 	5

extern void delete_before_cursor(screen * sc);

static void (*EDITOR_FUNCS[EDITOR_ACTION_LEN])(screen * sc) = {
	move_cursor_up,
	move_cursor_down,
	move_cursor_left,
	move_cursor_right,
	delete_before_cursor
};

static t_key EDITOR_BUTTONS[EDITOR_ACTION_LEN];/* = {
	KEY_NSPIRE_UP,
	KEY_NSPIRE_DOWN,
	KEY_NSPIRE_LEFT,
	KEY_NSPIRE_RIGHT,
	KEY_NSPIRE_DEL
};*/
extern void init_editor_buttons();
static uint8_t editor_keypress_duration[EDITOR_ACTION_LEN] = {
	0,
	0,
	0,
	0,
	0
};

//I have no way to measure time, everything has to be done in # loops
#define INITIAL_LOOP_COUNT	40
#define RESET_LOOP_COUNT	30

extern void scan_keys(screen * sc);

#endif
