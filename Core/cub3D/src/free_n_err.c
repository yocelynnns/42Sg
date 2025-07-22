/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 01:03:07 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/25 19:11:20 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
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
	if (map_s->no_path)
		free(map_s->no_path);
	if (map_s->so_path)
		free(map_s->so_path);
	if (map_s->ea_path)
		free(map_s->ea_path);
	if (map_s->we_path)
		free(map_s->we_path);
}

void	ft_error(char *s, t_map *map_s)
{
	clean_struct(map_s);
	putstr_fd(s, 2);
	exit(1);
}

void	cleanup_game(t_game *game)
{
	if (game->tex_no)
		mlx_destroy_image(game->mlx, game->tex_no);
	if (game->tex_so)
		mlx_destroy_image(game->mlx, game->tex_so);
	if (game->tex_we)
		mlx_destroy_image(game->mlx, game->tex_we);
	if (game->tex_ea)
		mlx_destroy_image(game->mlx, game->tex_ea);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->mlx)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

int	close_window(t_game *game)
{
	cleanup_game(game);
	clean_struct(game->map);
	exit(0);
}
