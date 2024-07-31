unsigned char swapbits(unsigned char octet)
{
	return ((octet >> 4) | (octet << 4));
}
