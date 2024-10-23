/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:24:36 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/23 18:06:47 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int close_window(t_game *game)
{
    cleanup_game(game);
    exit(0);
    return (0);
}

int    init_game(t_struct *m_structs, t_game *game)
{
    game->mlx = mlx_init();
    if (game->mlx == NULL)
    {
        printf("Error: Failed to initialize MLX\n");
        return (1);
    }
    game->win_w = m_structs->map_w * 64;
    game->win_h = m_structs->map_h * 64;
    game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "so_long");
    if (game->win == NULL)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        printf("Error: Failed to create window\n");
        return (1);
    }
    game->player = NULL;
    game->wall = NULL;
    game->collectible = NULL;
    game->floor = NULL;
    game->exit = NULL;
    return (0);
}

void cleanup_game(t_game *game)
{
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->player)
        mlx_destroy_image(game->mlx, game->player);
    if (game->wall)
        mlx_destroy_image(game->mlx, game->wall);
    if (game->collectible)
        mlx_destroy_image(game->mlx, game->collectible);
    if (game->floor)
        mlx_destroy_image(game->mlx, game->floor);
    if (game->exit)
        mlx_destroy_image(game->mlx, game->exit);
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
}

void handle_events(t_game *game)
{
    mlx_hook(game->win, 17, 0, close_window, game);
    mlx_loop(game->mlx);
}

void	load_single(t_game *game, void **img_ptr, char *filename)
{
	int	width;
	int	height;

	*img_ptr = mlx_xpm_file_to_image(game->mlx, filename, &width, &height);
	if (!*img_ptr)
		printf("Error: Failed to load %s\n", filename);
}

void	load_images(t_game *game)
{
	load_single(game, &game->player, "textures/player.xpm");
	load_single(game, &game->wall, "textures/wall.xpm");
	load_single(game, &game->collectible, "textures/collectibles.xpm");
	load_single(game, &game->floor, "textures/floor.xpm");
	load_single(game, &game->exit, "textures/exit.xpm");
	if (!game->wall || !game->floor || !game->player || !game->collectible || !game->exit)
    {
        if (game->player)
			mlx_destroy_image(game->mlx, game->player);
		if (game->wall)
			mlx_destroy_image(game->mlx, game->wall);
		if (game->exit)
			mlx_destroy_image(game->mlx, game->exit);
		if (game->floor)
			mlx_destroy_image(game->mlx, game->floor);
		if (game->collectible)
			mlx_destroy_image(game->mlx, game->collectible);
        printf("Error: Failed to load assets\n");
		exit(1);
	}
}

void    render_map(t_game *game, t_struct *m_struct)
{
    int x;
    int y;

    y = 0;
    while (y < m_struct->map_h)
    {
        x = 0;
        while (x < m_struct->map_w)
        {
            if (m_struct->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->wall, x * 64, y * 64);
            else if (m_struct->map[y][x] == '0')
                mlx_put_image_to_window(game->mlx, game->win, game->floor, x * 64, y * 64);
            else if (m_struct->map[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->player, x * 64, y * 64);
            else if (m_struct->map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->collectible, x * 64, y * 64);
            else if (m_struct->map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->exit, x * 64, y * 64);
            x++;
        }
        y++;
    }
}
