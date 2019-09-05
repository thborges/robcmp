#include <cstdio>
#include <cctype>

void unescape(char *data)
{
    int oval;
	char *current = data;
	char *unescaped = data;
	
	#define UCHAR(cp)	((unsigned char *) (cp))
	#define ISOCTAL(ch)	(isdigit(ch) && (ch) != '8' && (ch) != '9')

    while (*UCHAR(current) != 0) {
		if (*current != '\\') {
			*unescaped = *current;
		}
		else {
			current++;
			switch (*UCHAR(current)) {
				case 'a':				/* \a -> audible bell */
					*unescaped = '\a';
					break;
				case 'b':				/* \b -> backspace */
					*unescaped = '\b';
					break;
				case 'f':				/* \f -> formfeed */
					*unescaped = '\f';
					break;
				case 'n':				/* \n -> newline */
					*unescaped = '\n';
					break;
				case 'r':				/* \r -> carriagereturn */
					*unescaped = '\r';
					break;
				case 't':				/* \t -> horizontal tab */
					*unescaped = '\t';
					break;
				case 'v':				/* \v -> vertical tab */
					*unescaped = '\v';
					break;
				case '0':				/* \nnn -> ASCII value */
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
					oval = (*current - '0');
					if (ISOCTAL(current[1])) {
						oval = (oval << 3) | (current[1] - '0');
						current++;
						if (ISOCTAL(current[1])) {
							oval = (oval << 3) | (current[1] - '0');
							current++;
						}
					}
					*unescaped = oval;
					break;
				default:				/* \any -> any */
					*unescaped = *current;
			}
		}
   		unescaped++;
		current++;
	}
	*unescaped = '\0';
}

/*int main() {

	char escaped[] = "thiago\\t10\\nasdf\\23t\\1\\2345";
	char escaped2[] = "thiago\t10\nasdf\23t\1\2345";


	unescape(escaped);
	printf("%s\n", escaped);
	printf("%s\n", escaped2);

}*/

