#include <libndls.h>
#include <math.h>

#include "reader.h"
#include "displayer.h"
#include "editor.h"
#include "writer.h"
#include "file_browser.h"

int main(int argc, char *argv[]) {
	printf("Starting program\n");
	enable_relative_paths(argv);
	screen * sc = malloc(sizeof(screen));
	init_screen(sc);
	printf("Inited screen\n");
	if (argc <= 1) {
		init_fb(sc);
		printf("Inited file browser\n");
		draw_fb(sc);
		printf("Drew file browser\n");
	}
	else {
		printf("In here for some reason\n");
		vstring data = read_file(argv[1]);
		set_filename(sc, argv[1]);
		load_text(sc, data);
		draw_text(sc);
	}
	
	printf("Finished initing\n");
	//line_t * head = sc->topmost_line;

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
	printf("Got to writing the file\n");
	if (sc->fqfilename != NULL) {
		printf("%s\n", sc->fqfilename->str);
		vstring data = llist_to_string(sc->topmost_line);
		printf("%s\n", data.str);
		write_file(sc->fqfilename->str, data);
	}
	deinit_screen(sc);
	return 0;
}
