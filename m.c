#include <stdio.h>
#include "morse.h"


int main(void) {
	char *code;

	code = encode_bulk("r");
	printf("%s\n", code);

	free(code);

	return 0;

}
