#include "cub3d.h"

int	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	if (x < 0 || x >= game->win_w || y < 0 || y >= game->win_h)
		return (1);

	char	*dst;
	dst = game->img_addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return 0;
}

void	clear_image(t_game *game)
{
	int	*dst;
	int i;

	dst = (int *)game->img_addr;
	i = 0;
	while (i < (game->win_w * game->win_h))
	{
		dst[i] = 0x000000; // blclear_imageack
		i++;
	}
}

void	render_door_animation(t_game *game, int door_index)
{
	int	tex_w;
	int	tex_h;
	int dx;
	int dy;

	game->tex_opening = mlx_xpm_file_to_image(game->mlx,
			TEX_OPENING, &tex_w, &tex_h);
	if (!game->tex_opening)
	{
		printf("Error: Failed to load door opening texture\n");
		return ;
	}
	dx = game->map->doors[door_index].door_x;
	dy = game->map->doors[door_index].door_y;

	mlx_put_image_to_window(game->mlx, game->win,
		game->tex_opening, dx * 64, dy * 64);
}