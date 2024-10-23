int max(int *tab, unsigned int len)
{
	int result = 0;
	unsigned int i = 0;

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

#include <stdio.h>
int main()
{
        int tab[] = {2, 6, 1};
        int len = 3;

        printf("%d", max(tab, len));
}