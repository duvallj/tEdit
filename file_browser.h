#ifndef _FILE_BROWSER_H_
#define _FILE_BROWSER_H_

#include "displayer.h"
#include "editor.h"
#include <keys.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>

#define FB_ACTION_LEN	8

extern void move_fb_cursor_up(screen * sc);
extern void move_fb_cursor_down(screen * sc);
extern void move_fb_cursor_right(screen * sc);
extern void move_fb_cursor_left(screen * sc);

extern void fb_delete_before_cursor(screen * sc);

extern void toggle_filename_browsing(screen * sc);
extern void fb_enter_pressed(screen * sc);

extern void draw_fb(screen * sc);
extern void init_fb_buttons();
extern void init_fb(screen * sc);
extern void set_filename(screen * sc, char * name);
extern void fb_scan_keys(screen * sc);

t_key FB_BUTTONS[FB_ACTION_LEN];
static clock_t fb_keypress_duration[FB_ACTION_LEN] = {0};

static void (*FB_FUNCS[FB_ACTION_LEN])(screen * sc) = {
	move_fb_cursor_up,
	move_fb_cursor_down,
	move_fb_cursor_left,
	move_fb_cursor_right,
	fb_delete_before_cursor,
	toggle_filename_browsing,
	fb_enter_pressed,
	fb_enter_pressed
};

#define LINES_ABOVE	2
#define LINES_BELOW	2

#endif
