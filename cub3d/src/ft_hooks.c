#include "cub3d.h"
void open_door(t_game *game)
{
	int i;
	int px = (int)game->p->x;
	int py = (int)game->p->y;
	int dx, dy;

	printf("Space pressed!\n");
	i = 0;
	while (i < game->map->door_count)
	{
		dx = game->map->doors[i].door_x;
		dy = game->map->doors[i].door_y;
		if (((px == dx && (py == dy - 1 || py == dy + 1)) ||
			(py == dy && (px == dx - 1 || px == dx + 1))) &&
			game->player_next_to_door)
		{
			if (game->map->doors[i].door_state == 0)
			{
				game->map->doors[i].door_state = 1;
				game->map->map[dy][dx] = '0';
				game->map->doors[i].redraw = 1;
				printf("door opened!\n");
			}
			else
			{
				game->map->doors[i].door_state = 0;
				game->map->map[dy][dx] = 'D';
				game->map->doors[i].redraw = 0;
				printf("door closed!\n");
			}
			printf("door state : %d -> %d\n", i, game->map->doors[i].door_state);
			break;
		}
		i++;
	}
	game->press_space = 0; // Reset flag to avoid repeated toggling
}

int update_game(t_game *game)
{
	if (game->move_forward)
		move_forward(game);
	if (game->move_backward)
		move_backward(game);
	if (game->move_left)
		move_left(game);
	if (game->move_right)
		move_right(game);
	if (game->rotate_left)
		rotate_left(game);
	if (game->rotate_right)
		rotate_right(game);
	if (game->press_space)
		open_door(game);
	check_player_to_door(game);
	render_frame(game);
	return (0);
}

int handle_down(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_window(game);
	else if (key == KEY_W)
		game->move_forward =  1;
	else if (key == KEY_S)
		game->move_backward = 1;
	else if (key == KEY_A)
		game->move_left = 1;
	else if (key == KEY_D)
		game->move_right = 1;
	else if (key == KEY_LEFT)
		game->rotate_left = 1;
	else if (key == KEY_RIGHT)
		game->rotate_right = 1;
	else if (key == KEY_SPACE)
		game->press_space = 1;
	return (0);
}

int handle_up(int key, t_game *game)
{
	if (key == KEY_W)
		game->move_forward = 0;
	else if (key == KEY_S)
		game->move_backward = 0;
	else if (key == KEY_A)
		game->move_left = 0;
	else if (key == KEY_D)
		game->move_right = 0;
	else if (key == KEY_LEFT)
		game->rotate_left = 0;
	else if (key == KEY_RIGHT)
		game->rotate_right = 0;
	return (0);
}