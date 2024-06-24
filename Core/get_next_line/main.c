/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:43:36 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/06/11 17:32:37 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include <string.h>
int	main(void)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("multiple_nl.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free (line);
	}
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free (line);
// line = get_next_line(fd);
// 	printf("%s", line);
// 	free (line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free (line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free (line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free (line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free (line);
}


/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	line = get_next_line(fd);
	if (line != NULL)
	{
		printf("Retrieved line 1: %s", line);
		free(line);
	}
	line = get_next_line(fd);
	if (line != NULL)
	{
		printf("Retrieved line 2: %s", line);
		free(line);
	}
	line = get_next_line(fd);
	if (line != NULL)
	{
		printf("Retrieved line 3: %s", line);
		free(line);
	}
	line = get_next_line(fd);
	if (line != NULL)
	{
		printf("Retrieved line 4: %s", line);
		free(line);
	}
	line = get_next_line(fd);
	if (line != NULL)
	{
		printf("Retrieved line 5: %s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/