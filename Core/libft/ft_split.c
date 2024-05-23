#include "libft.h"
static int	countword(const char *s, char c)
{
	int i;
    int countw;

    i = 0; // iterate each char
    countw = 0; // to count if its a word
	while (s[i])
	{
		if (!(s[i] == c) && ((s[i+1] == c) || !(s[i+1])))
			countw++;
		i++;
	}
	return (countw);
}

static int wordlen(const char *s, char c)
{
    int i = 0;
    int wlen = 0;

    while (s[i] && s[i] != c)
    {
        wlen++;
        i++;
    }
    return wlen;
}

static char	*writeword(char const *s, int len)
{
    char *word;
	int i;

	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);

	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static char **free_array(char **ptr, int i)
{
    while (i > 0)
    {
        i--;
        free(ptr[i]);
    }
    free(ptr);
    return NULL;
}

static char **split_words(const char *s, char c, int word_count)
{
    char **result;
	int i;
	int j;
	int len;
	
	result = (char **)malloc((word_count + 1) * sizeof(char *));
    if (!result)
        return NULL;

    i = 0;
    j = 0;
	  while (s[i])
    {
		while (s[i] == c)
			i++;
		if (s[i])
		{
			len = wordlen(s + i, c);
            result[j] = writeword(s + i, len);
            if (!result[j])
                return free_array(result, j);
            i += len;
            j++;
        }
	}
    result[j] = NULL;
    return result;
}

char **ft_split(char const *s, char c)
{
    if (!s)
        return NULL;

    int word_count = countword(s, c);
    return split_words(s, c, word_count);
}

// int main()
// {
//     char str[] = "  this is  a string ";
//     char **result = ft_split(str, ' ');

//     if (result != NULL)
//     {
//         int i = 0;
//         while (result[i] != NULL)
//         {
//             printf("%s\n", result[i]);
//             free(result[i]);
//             i++;
//         }
//         free(result);
//     }
//     else
//         printf("Memory allocation failed or empty string\n");
//     return 0;
// }