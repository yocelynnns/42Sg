#include <stdlib.h>

char *ft_strdup(char *src)
{
	int size;
	char *dest;
	int i = 0;

	while (src[size])
		size++;
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
