#include <stdlib.h>
#include <err.h>

#include "upng.h"
#include "hex2ansi.h"

int
main(int argc, char **argv) {
	upng_t *png;
	char *path = argv[1];
	unsigned int color;
	int i, max;

	png = upng_new_from_file(path);
	if (png != NULL) {
		upng_decode(png);
		if (upng_get_error(png) == UPNG_EOK) {
			max = (upng_get_width(png) * upng_get_height(png)) * 3;

			for (i = max; i; i -= 4) {
				color = rgb2hex(upng_get_buffer(png)[i],
						upng_get_buffer(png)[i+1],
						upng_get_buffer(png)[i+2]);
			}

		}

		upng_free(png);
	}

	return 0;
}
