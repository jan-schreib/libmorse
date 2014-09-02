#define __GNU_SOURCE

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "morse_decode.h"

ssize_t morse_decode(char **textptr, size_t *n, char const *message);
static int morse_heap_index(char const *code, char const **end);
static char morse_token_consume(char const *code, char const **end);
static size_t morse_decode_fixed(char *buf, size_t buflen, char const *message);

static char const morse_heap[] =
"ETIANMSURWDKGOHV"
"F L PJBXCYZQ  54"
" 3   2       16 "
"      7   8 90"
;

enum { MORSE_HEAP_SIZE = sizeof(morse_heap) - 1 };

static int morse_heap_index(char const *code, char const **end) {
	int         r   = 1;
	char const *p   = NULL;

	/* Skip leading whitespaces */
	while(*code && isspace(*code)) {
		++code;
	}

	/* Binary heap like method (point left, das right). */
	for(p = code; *p == '.' || *p == '-'; ++p) {
		r *= 2;

		if(*p == '-') {
			++r;
		}
	}

	/* becomes -1 if loop is not running.
	 * implicit error handling.
	 */
	r -= 2;

	if(r >= MORSE_HEAP_SIZE || r < 0 || morse_heap[r] == ' ') {
		r = -1;
	}

	if(end != NULL) {
		*end = p;
	}

	return r;
}

static char morse_token_consume(char const *code, char const **end) {
	int i = morse_heap_index(code, end);
	return i >= 0 ? morse_heap[i] : '\0';
}

static size_t morse_decode_fixed(char *buf, size_t buflen, char const *message) {
	char const *p = message;
	size_t i;

	for(i = 0; i + 1 < buflen && (buf[i] = morse_token_consume(p, &p)); ++i) {
		/* Intentionally left blank */
	}

	while(morse_token_consume(p, &p)) {
		++i;
	}

	return i;
}

ssize_t morse_decode(char **textptr, size_t *n, char const *message) {
	size_t msglen;
	size_t space_needed;

	if(textptr == NULL || n == NULL) {
		return -1;
	}

	msglen = morse_decode_fixed(*textptr, *n, message);
	space_needed = msglen + 1;

	if(space_needed > *n) {
		size_t msglen2;
		char *tmp;

		tmp = realloc(*textptr, space_needed);

		if(tmp == NULL) {
			return -1;
		}

		msglen2 = morse_decode_fixed(tmp, space_needed, message);
		assert(msglen == msglen2);

		*textptr = tmp;
		*n       = space_needed;
	}

	return msglen;
}
