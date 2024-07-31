int ft_strlen(char s)
{
	int i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char *ft_strdup(char *src)
{
	int size;
	char *dest;
	int i = 0;

	size = ft_strlen(src);
	dest = (char *)malloc(size * sizeof(char) + 1);
	if (dest == NULL)
		return (NULL);
	if (dest != NULL)
	{
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (dest);
}	
