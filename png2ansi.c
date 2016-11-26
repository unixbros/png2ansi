#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "upng.h"
#include "hex2ansi.h"

int
main(int argc, char **argv) {
	upng_t *png;
	char *path = argv[1];
	unsigned int fg, bg;
	unsigned int i, x, max;

	png = upng_new_from_file(path);
	if (png != NULL) {
		upng_decode(png);
		if (upng_get_error(png) != UPNG_EOK) {
			switch (upng_get_error(png)) {
			case UPNG_ENOTPNG:
				errx(1, "not a png");
			case UPNG_BADFORMAT:
				errx(1, "bad png format");
			case UPNG_EUNFORMAT:
				errx(1, "unsupported color format");
			default:
				errx(1, "png error");
			}
		}
		max = upng_get_size(png);

		for (i = 0; i < max - (upng_get_width(png) * upng_get_components(png)); i += upng_get_components(png)) {
			bg = rgb2hex(upng_get_buffer(png)[i],
				upng_get_buffer(png)[i+1],
				upng_get_buffer(png)[i+2]);
			fg = rgb2hex(upng_get_buffer(png)[i+(upng_get_width(png) * upng_get_components(png))],
				upng_get_buffer(png)[i+1+(upng_get_width(png) * upng_get_components(png))],
				upng_get_buffer(png)[i+2+upng_get_width(png) * upng_get_components(png)]);

			printf("\033[48;5;%dm\033[38;5;%dm▄\033[0m",
					closest(bg), closest(fg));

			x++;
			if ((x % upng_get_width(png) == 0))
				putchar('\n');
		}

		upng_free(png);
	}

	return 0;
}
