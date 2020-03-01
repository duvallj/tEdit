#ifndef EDITOR_H
#define EDITOR_H

#include "displayer.h"
#include "llstring.h"
#include <libndls.h>
#include <keys.h>

#include <time.h>

#define EDITOR_ACTION_LEN 	7
#define INSERT_ACTION_LEN	50

extern void delete_before_cursor(screen * sc);
extern void insert_after_cursor(vstring * str, char c, unsigned int col);
extern void insert_linebreak_after_cursor(screen * sc);

extern void (* const EDITOR_FUNCS[EDITOR_ACTION_LEN])(screen * sc);

extern const t_key EDITOR_BUTTONS[EDITOR_ACTION_LEN];
extern const t_key INSERT_BUTTONS[INSERT_ACTION_LEN];

extern clock_t editor_keypress_duration[EDITOR_ACTION_LEN];
extern clock_t insert_keypress_duration[INSERT_ACTION_LEN];

extern const char normal_keypress[INSERT_ACTION_LEN];
extern const char shift_keypress[INSERT_ACTION_LEN];
extern const char ctrl_keypress[INSERT_ACTION_LEN];

//I have no way to measure time, everything has to be done in terms of clock cycles
#define ED_INITIAL_LOOP_COUNT	4000
#define ED_RESET_LOOP_COUNT		3000
#define IN_INITIAL_LOOP_COUNT	7500
#define IN_RESET_LOOP_COUNT		5000

extern void scan_keys(screen * sc);

#endif // EDITOR_H
