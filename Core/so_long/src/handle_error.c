/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:47:42 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/25 01:12:08 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "so_long.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	clean_struct(t_map *map_s)
{
	if (map_s->map)
		free_arr(map_s->map);
	if (map_s->map_cp)
		free_arr(map_s->map_cp);
	if (map_s->map_fd != -1)
		close(map_s->map_fd);
}

void	ft_error(char *s, t_map *map_s)
{
	clean_struct(map_s);
	ft_printf("%s", s);
	exit(1);
}

int	close_window(t_game *game)
{
	cleanup_game(game);
	clean_struct(game->map);
	exit(0);
	return (0);
}
