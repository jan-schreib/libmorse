libmorse
========

A C library for en/decoding morse code.

Example:

```
int main(void) {

  	char *foo = "foo";
	char *plain = NULL;
	size_t len = 0;

	char *code = encode(foo);

	morse_decode(&plain, &len, code);
	
	printf("%s\n", code);
	printf("%s\n", plain);

	free(code);
	free(plain;)
}
```
