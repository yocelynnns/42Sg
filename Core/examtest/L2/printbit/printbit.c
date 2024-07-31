#include <unistd.h>

void printbits(unsigned char octet)
{
	int i = 0;
	unsigned char bit;

	while (i--)
	{
		bit = (octet >> i & 1) + '0';
		write (1, &bit, 1);
	}
}
