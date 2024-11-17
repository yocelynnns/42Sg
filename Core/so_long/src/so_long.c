/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:30:22 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/25 23:46:07 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "so_long.h"

int	check_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (1);
	return (ft_strcmp(&filename[len - 4], ".ber") == 0);
}

int	read_map(t_map *map_s, char **argv)
{
	char	buf[BUFFER_SIZE];
	int		bytes_read;

	map_s->map_fd = open(argv[1], O_RDONLY);
	if (map_s->map_fd == -1)
		return (perror("Error: Could not open .ber file"), 0);
	bytes_read = read(map_s->map_fd, buf, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		perror("Error: Failed to read map");
		return (close(map_s->map_fd), 0);
	}
	else if (bytes_read == 0)
		return (ft_printf("Error: Map is empty\n"), close(map_s->map_fd), 0);
	else if (bytes_read > 560)
		return (ft_printf("Error: Map too big\n"), close(map_s->map_fd), 0);
	buf[bytes_read] = '\0';
	map_s->map = ft_split(buf, '\n');
	map_s->map_cp = ft_split(buf, '\n');
	if (!map_s->map || !map_s->map_cp)
		return (perror("Error: Failed to split map"), close(map_s->map_fd), 0);
	close(map_s->map_fd);
	return (1);
}

void	map_check(char **argv, t_map *map_s)
{
	if (!read_map(map_s, argv))
		ft_error("", map_s);
	map_dimension(map_s);
	if (!rect_check(map_s))
		ft_error("Error: Map is not a rectangle.\n", map_s);
	if (!wall_check(map_s))
		ft_error("Error: Map is not surrounded by walls.\n", map_s);
	if (!valid_elem(map_s))
		ft_error("Error: Invalid elements in the map.\n", map_s);
	count_elems(map_s);
	check_elem(map_s);
	startfill(map_s);
}

int	main(int argc, char **argv)
{
	t_map		map_s;
	t_temp		temp;
	t_game		game;

	if (argc != 2)
		return (ft_printf("Error!\nUsage: ./so_long <map_file.ber>\n"), 1);
	if (!check_filename(argv[1]))
		return (ft_printf("Error: Invalid file format, only .ber file\n"), 1);
	init_map(&map_s, &temp);
	map_check(argv, &map_s);
	if (init_win(&game, &map_s) == 1)
		exit(1);
	load_images(&game);
	render_map(&game);
	mlx_hook(game.win, ON_KEYDOWN, 1L << 0, key_movement, &game);
	mlx_hook(game.win, ON_EXPOSE, 1L << 15, render_map, &game);
	mlx_hook(game.win, ON_DESTROY, 1L << 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}

// close_window(&game);
// ft_error("Perfect!\n", &map_s);

// ft_printf("%d", map_s.player_y);
// ft_printf("%d", game.map->player_y);
// ft_printf("%d %d\n", game.new_y, game.new_x);
// ft_printf("hook successsssss\n");
// mlx_loop_hook(game.mlx, , &game);

// void free_all(t_map *map_s)
// {
//     int i = 0;
//     if (!map_s->map)
//         return;
//     while (map_s->map[i])
//     {
//         free(map_s->map[i]);
//         i++;
//     }
//     free(map_s->map);
// }

// int i = 0;
// while (map_s.map[i])
// {
//     ft_printf("%s\n", map_s.map[i]);
//     i++;
// }
// ft_printf("-----------------------------\n");
// i = 0;
// while (map_s.map_cp[i])
// {
//     ft_printf("%s\n", map_s.map_cp[i]);
//     i++;
// }