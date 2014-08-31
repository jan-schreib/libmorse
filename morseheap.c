#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

enum { MORSE_HEAP_SIZE = 64 };

static size_t morse_heap_index(char const *code) {
  size_t i = 0;
  size_t off = 1;

  for(char const *p = code; *p; ++p) {
    assert(*p == '.' || *p == '-');

    i   *= 2;
    off *= 2;

    if(*p == '-') {
      ++i;
    }
  }

  size_t r = off + i - 2;

  assert(r < MORSE_HEAP_SIZE);
  return r;
}

typedef struct {
  char data[MORSE_HEAP_SIZE];
} morse_heap;

static morse_heap morse_heap_init(void) {
  morse_heap h = { { 0 } };

#define MORSE_INIT(zeichen, code) do { h.data[morse_heap_index(code)] = zeichen; } while(0)
  MORSE_INIT('A', ".-");
  MORSE_INIT('B', "-...");
  MORSE_INIT('C', "-.-.");
  MORSE_INIT('D', "-..");
  MORSE_INIT('E', ".");
  MORSE_INIT('F', "..-.");
  MORSE_INIT('G', "--.");
  MORSE_INIT('H', "....");
  MORSE_INIT('I', "..");
  MORSE_INIT('J', ".---");
  MORSE_INIT('K', "-.-");
  MORSE_INIT('L', ".-..");
  MORSE_INIT('M', "--");
  MORSE_INIT('N', "-.");
  MORSE_INIT('O', "---");
  MORSE_INIT('P', ".--.");
  MORSE_INIT('Q', "--.-");
  MORSE_INIT('R', ".-.");
  MORSE_INIT('S', "...");
  MORSE_INIT('T', "-");
  MORSE_INIT('U', "..-");
  MORSE_INIT('V', "...-");
  MORSE_INIT('W', ".--");
  MORSE_INIT('X', "-..-");
  MORSE_INIT('Y', "-.--");
  MORSE_INIT('Z', "--..");
  MORSE_INIT('0', "-----");
  MORSE_INIT('1', ".----");
  MORSE_INIT('2', "..---");
  MORSE_INIT('3', "...--");
  MORSE_INIT('4', "....-");
  MORSE_INIT('5', ".....");
  MORSE_INIT('6', "-....");
  MORSE_INIT('7', "--...");
  MORSE_INIT('8', "---..");
  MORSE_INIT('9', "----.");
#undef MORSE_INIT

  return h;
}

static char morse_heap_lookup(morse_heap const *h, char const *code) {
  return h->data[morse_heap_index(code)];
}

int main(void) {
  morse_heap h = morse_heap_init();

  char buf[1024];

  fgets(buf, sizeof(buf), stdin);
  buf[strlen(buf) - 1] = '\0';

  printf("%s = %c\n", buf, morse_heap_lookup(&h, buf));

  return 0;
}
