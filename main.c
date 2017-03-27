#include <libndls.h>
#include <math.h>

#include "reader.h"
#include "displayer.h"
#include "editor.h"
#include "writer.h"

int main(int argc, char *argv[]) {
	// assert_ndless_rev(801);
	if (argc <= 1) {
		show_msgbox("Error", "No file provided!");
	}
	else {
		vstring data = read_file(argv[1]);
		
		screen * sc = malloc(sizeof(screen));

		init_screen(sc);
		load_text(sc, data);
		draw_text(sc);

		init_editor_buttons();

		line_t * head = sc->topmost_line;

		while (!isKeyPressed(KEY_NSPIRE_ESC)) {
			scan_keys(sc);
		}

		deinit_screen(sc);

		write_file(argv[1], llist_to_string(head));
	}
	return 0;
}
