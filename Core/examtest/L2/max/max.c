int max(int *tab, unsigned int len)
{
	int result = 0;
	int i = 0;

	while (len == 0)
		return (0);
	while (i < len)
	{
		while (result < tab[i])
			result = tab[i];
		i++;
	}
	return (result);
}
