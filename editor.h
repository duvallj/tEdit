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

static void (*EDITOR_FUNCS[EDITOR_ACTION_LEN])(screen * sc) = {
	move_cursor_up,
	move_cursor_down,
	move_cursor_left,
	move_cursor_right,
	delete_before_cursor,
	insert_linebreak_after_cursor,
	insert_linebreak_after_cursor
};

t_key EDITOR_BUTTONS[EDITOR_ACTION_LEN];
t_key INSERT_BUTTONS[INSERT_ACTION_LEN];

extern void init_editor_buttons();
static clock_t editor_keypress_duration[EDITOR_ACTION_LEN] = {0};
static clock_t insert_keypress_duration[INSERT_ACTION_LEN] = {0};

static char normal_keypress[INSERT_ACTION_LEN] = {
	'a','b','c','d','e','f',
	'g','h','i','j','k','l',
	'm','n','o','p','q','r',
	's','t','u','v','w','x',
	'y','z','1','2','3','4',
	'5','6','7','8','9','0',
	'.','-','=','^','(',')',
	'*','/','+','-',',','?','%',' '
};
static char shift_keypress[INSERT_ACTION_LEN] = {
	'A','B','C','D','E','F',
	'G','H','I','J','K','L',
	'M','N','O','P','Q','R',
	'S','T','U','V','W','X',
	'Y','Z','1','2','3','4',
	'5','6','7','8','9','0',
	':','_','>','"','[',']',
	'#','\\','&','_',';','!','$',' '
};
static char ctrl_keypress[INSERT_ACTION_LEN] = {
	'a','b','c','d','e','f',
	'g','h','i','j','k','l',
	'm','n','o','p','q','r',
	's','t','u','v','w','x',
	'y','z','1','2','3','4',
	'5','6','7','8','9','0',
	'.','~','<','\'','{','}',
	'*','|','+','~','`','?','@',' '
};


//I have no way to measure time, everything has to be done in terms of clock cycles
#define ED_INITIAL_LOOP_COUNT	4000
#define ED_RESET_LOOP_COUNT		3000
#define IN_INITIAL_LOOP_COUNT	7500
#define IN_RESET_LOOP_COUNT		5000

extern void scan_keys(screen * sc);

#endif
