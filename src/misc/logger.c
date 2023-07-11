#include <stdio.h>
#include <stdlib.h>

#include "misc/logger.h"

void info(char *string) {
	printf("[info] %s\n", string);
}

void die(char *string) {
	printf("[fatal] %s\n", string);
	exit(EXIT_FAILURE);
}
