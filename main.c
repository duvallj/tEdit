#include <libndls.h>
#include <math.h>

#include "reader.h"
#include "displayer.h"
#include "editor.h"
#include "writer.h"
#include "file_browser.h"

int main(int argc, char *argv[]) {
	enable_relative_paths(argv);
	screen * sc = malloc(sizeof(screen));
	init_screen(sc);
	
	if (argc <= 1) {
		init_fb(sc);
		draw_fb(sc);
	}
	else {
		vstring data = read_file(argv[1]);
		set_filename(sc, argv[1]);
		load_text(sc, data);
		draw_text(sc);
	}
	init_editor_buttons();
	init_fb_buttons();

	line_t * head = sc->topmost_line;

	while (!isKeyPressed(KEY_NSPIRE_ESC)) {
		switch(sc->mode) {
			case 0:
				scan_keys(sc);
				break;
			case 1:
				fb_scan_keys(sc);
				break;
			case 2:
				fb_scan_keys(sc);
				break;
		}
	}
	if (sc->fqfilename != NULL) {
		write_file(sc->fqfilename->str, llist_to_string(head));
	}
	deinit_screen(sc);
	return 0;
}
