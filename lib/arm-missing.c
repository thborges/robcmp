
void abort (void) {
    while(1);
}

void *memcpy(void *dst, const void *src, unsigned int len)
{
	const char *s = src;
	char *d = dst;

	while (len--)
		*d++ = *s++;

	return dst;
}

