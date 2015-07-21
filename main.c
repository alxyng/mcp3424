#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mcp3424.h"

#define RAW_MIN 0
#define RAW_MAX_12 2048
#define RAW_MAX_14 8192
#define RAW_MAX_16 32768
#define RAW_MAX_18 131072
#define V_MIN 0.00
#define V_MAX 5.06

#define MAP(val, from_min, from_max, to_min, to_max) \
	((val - from_min) * ((to_max - to_min) / (from_max - from_min))) + to_min

int main(int argc, char const **argv) {
	int fd;
	mcp3424 j2;
	mcp3424 j3;
	unsigned int iteration = 0;
	int i;

	int channels[4] = {
		MCP3424_CHANNEL_1,
		MCP3424_CHANNEL_2,
		MCP3424_CHANNEL_3,
		MCP3424_CHANNEL_4
	};
	unsigned int res[8];
	float v[8];

	fd = open("/dev/i2c-1", O_RDWR);
	if (fd == -1) {
		printf("error: open: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	mcp3424_init(&j2, fd, 0x68, MCP3424_RESOLUTION_14);
	mcp3424_set_conversion_mode(&j2, MCP3424_CONVERSION_MODE_CONTINUOUS);
	mcp3424_init(&j3, fd, 0x69, MCP3424_RESOLUTION_14);
	mcp3424_set_conversion_mode(&j3, MCP3424_CONVERSION_MODE_CONTINUOUS);

	while (1) {
		printf("iteration: %u\n", iteration++);
		for (i = 0; i < 4; i++) {
			res[i] = mcp3424_get_raw(&j2, channels[i]);
			if (j2.err) {
				printf("error: mcp3424_get_raw: %s\n", j2.errstr);
				close(fd);
				exit(EXIT_FAILURE);
			}
			v[i] = MAP(res[i], RAW_MIN, RAW_MAX_14, V_MIN, V_MAX);
		}
		for (i = 0; i < 4; i++) {
			res[i + 4] = mcp3424_get_raw(&j3, channels[i]);
			if (j3.err) {
				printf("error: mcp3424_get_raw: %s\n", j3.errstr);
				close(fd);
				exit(EXIT_FAILURE);
			}
			v[i + 4] = MAP(res[i + 4], RAW_MIN, RAW_MAX_14, V_MIN, V_MAX);
		}

		for (i = 0; i < 8; i++) {
			printf("res[%d] = %u, v[%d] = %0.2f\n", i, res[i], i, v[i]);
		}
		printf("\n");
	}

	close(fd);

	return EXIT_SUCCESS;
}
