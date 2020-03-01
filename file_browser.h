#ifndef FILE_BROWSER_H
#define FILE_BROWSER_H

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
extern void init_fb(screen * sc);
extern void set_filename(screen * sc, char * name);
extern void fb_scan_keys(screen * sc);

extern const t_key FB_BUTTONS[FB_ACTION_LEN];
extern clock_t fb_keypress_duration[FB_ACTION_LEN];

extern void (* const FB_FUNCS[FB_ACTION_LEN])(screen * sc);

#define LINES_ABOVE	2
#define LINES_BELOW	2

#endif // FILE_BROWSER_H
