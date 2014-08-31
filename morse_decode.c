#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

enum { MORSE_HEAP_SIZE = 64 };

static char const *const morse_heap = "ETIANMSURWDKGOHVF\0L\0PJBXCYZQ\0\054\03\0\0\02\0\0\0\0\0\0\016\0\0\0\0\0\0\07\0\0\08\090\0\0";

int morse_heap_index(char const *code, char const **end) {
  int i = 0;
  int off = 1;

  while(*code && isspace(*code)) {
    ++code;
  }

  char const *p;
  for(p = code; *p == '.' || *p == '-'; ++p) {
    i   *= 2;
    off *= 2;

    if(*p == '-') {
      ++i;
    }
  }

  // Wird -1, wenn die Schleife nicht durchlaufen wurde.
  int r = off + i - 2;

  if(r >= MORSE_HEAP_SIZE || morse_heap[r] == '\0') {
    r = -1; // Fehlerfall.
  }

  if(end != NULL) {
    *end = p;
  }

  return r;
}

char morse_lookup(char const *code) {
  return morse_heap[morse_heap_index(code, NULL)];
}

size_t decode_morse_message(char *buf, size_t buflen, char const *message) {
  char const *p = message;
  size_t i = 0;
  int zeichen;

  while(i + 1 < buflen && (zeichen = morse_heap_index(p, &p)) >= 0) {
    buf[i++] = morse_heap[zeichen];
  }

  if(buflen != 0) {
    buf[i] = '\0';
  }

  while(morse_heap_index(p, &p) >= 0) {
    ++i;
  }

  return i;
}

int main(void) {
  char buf[1024];
  char decodebuf[1024];

  fgets(buf, sizeof(buf), stdin);

  size_t n = decode_morse_message(decodebuf, sizeof(decodebuf), buf);

  printf("%zu, %s\n", n, decodebuf);

  return 0;
}
