#include "get_next_line_bonus.h"

static char	*read_line(int fd, char *str, char *remain)
{
	int		readcheck;
	char	*temp;

	readcheck = 1;
	while (readcheck)
	{
		readcheck = read(fd, str, BUFFER_SIZE);
		if (readcheck == -1)
			return (0);
		else if (readcheck == 0)
			break ;
		str[readcheck] = '\0';
		if (!remain)
			remain = ft_strdup("");
		temp = remain;
		remain = ft_strjoin(temp, str);
		free(temp);
		if (!remain)
			return (NULL);
        temp = NULL;
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (remain);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*get_line(char *peepoo)
{
	char	*temp;
	int		lkoh;

	lkoh = 0;
	while (peepoo[lkoh] != '\0' && peepoo[lkoh] != '\n')
		lkoh++;
	if (peepoo[lkoh] == '\0')
		return (NULL);
	temp = ft_substr(peepoo, lkoh + 1, ft_strlen(peepoo) - lkoh);
	if (!temp)
		return (NULL);
	if (temp[0] == '\0')
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	peepoo[lkoh + 1] = '\0';
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		*peepoo;
	static char	*remain[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd < OPEN_MAX)
		return (NULL);
	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	peepoo = read_line(fd, str, remain[fd]);
	free(str);
    str = NULL;
	if (!peepoo)
		return (NULL);
	remain[fd] = get_line(peepoo);
	return (peepoo);
}