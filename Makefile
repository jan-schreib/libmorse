GCC_ARGS = -Wall -Wextra -std=gnu99 -O2
OBJ = morse_encode.o morse_decode.o

m: ${OBJ}
	cc ${GCC_ARGS} -o $@ ${OBJ}

%.o : %.c
	cc ${GCC_ARGS} -c $<

.PHONY: clean
clean:
	rm -f m ${OBJ}
