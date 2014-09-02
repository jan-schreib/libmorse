#define __GNU_SOURCE

#include <string.h>
#include <stdlib.h>

#include "morse_encode.h"

/* prototypes */
static void encode_single(char const in, char **out);
static char *encode_bulk(char const *in);
static char up(unsigned char in);

/* uppercase chars only */

char up(unsigned char in){
	if(in >= 97 && in <= 172){
		return (char)in - 32;
	} else if(in >= 65 && in <= 90){
		return (char)in;
	} else {
		return ' ';
	}
}

/* encode a single char and safes it in out */

void encode_single(char const in, char **out){
	char up_in = up(in);

	switch(up_in) {
		case 'A': *out = ".- ";    break;
		case 'B': *out = "-... ";  break;
		case 'C': *out = "-.-. ";  break;
		case 'D': *out = "-.. ";   break;
		case 'E': *out = ". ";     break;
		case 'F': *out = "..-. ";  break;
		case 'G': *out = "--. ";   break;
		case 'H': *out = ".... ";  break;
		case 'I': *out = ".. ";    break;
		case 'J': *out = ".--- ";  break;
		case 'K': *out = "-.- ";   break;
		case 'L': *out = ".-.. ";  break;
		case 'M': *out = "-- ";    break;
		case 'N': *out = "-. ";    break;
		case 'O': *out = "--- ";   break;
		case 'P': *out = ".--. ";  break;
		case 'Q': *out = "--.- ";  break;
		case 'R': *out = ".-. ";   break;
		case 'S': *out = "... ";   break;
		case 'T': *out = "- ";     break;
		case 'U': *out = "..- ";   break;
		case 'V': *out = "...- ";  break;
		case 'W': *out = ".-- ";   break;
		case 'X': *out = "-..- ";  break;
		case 'Y': *out = "-.-- ";  break;
		case 'Z': *out = "--.. ";  break;
		case '0': *out = "----- "; break;
		case '1': *out = ".---- "; break;
		case '2': *out = "..--- "; break;
		case '3': *out = "...-- "; break;
		case '4': *out = "....- "; break;
		case '5': *out = "..... "; break;
		case '6': *out = "-.... "; break;
		case '7': *out = "--... "; break;
		case '8': *out = "---.. "; break;
		case '9': *out = "----. "; break;
		default:  *out = "";       break;
	}
}

/* converts a char* into morsecode and returns it */

char *encode_bulk(char const *in){
	char *buf[7];
	char *res;

	size_t len = strlen(in);

	/*
	 * lets make that easy:
	 * I assume every morse char has the length of 5+1+1.
	 * 5 chars, 1 space, 1 '\n'
	 * makes allocation easier.
	 */

	res = malloc(len * 5 + 2);

	if(!res) {
		return "";
	}

	for(unsigned int i = 0; i < len; i++){
		encode_single(in[i], buf);
		strcat(res, *buf);
	}
	return res;
}

char *morse_encode(char const *in){
	return encode_bulk(in);
}
