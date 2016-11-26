#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "upng.h"
#include "hex2ansi.h"

int
main(int argc, char **argv) {
	upng_t *png;
	char *path = argv[1];
	unsigned int color;
	unsigned int i, x, max;

	png = upng_new_from_file(path);
	if (png != NULL) {
		upng_decode(png);
		if (upng_get_error(png) == UPNG_EOK) {
			max = upng_get_size(png);

			for (i = 0; i < max; i += upng_get_components(png)) {
				color = rgb2hex(upng_get_buffer(png)[i],
						upng_get_buffer(png)[i+1],
						upng_get_buffer(png)[i+2]);

				printf("\033[48;5;%dm \033[0m",
						closest(color));

				x++;
				if ((x % upng_get_width(png) == 0))
					putchar('\n');
			}
		}

		upng_free(png);
	}

	return 0;
}
