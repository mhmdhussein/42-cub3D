/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:11:31 by rtraoui           #+#    #+#             */
/*   Updated: 2025/10/29 03:58:37 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	old_dir_y;
	double	old_plane_y;

	old_dir_x = game->player.dir_x;
	old_dir_y = game->player.dir_y;
	game->player.dir_x = old_dir_x * cos(ROT_SPEED)
		- old_dir_y * sin(ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(ROT_SPEED)
		+ old_dir_y * cos(ROT_SPEED);
	old_plane_x = game->player.plane_x;
	old_plane_y = game->player.plane_y;
	game->player.plane_x = old_plane_x * cos(ROT_SPEED)
		- old_plane_y * sin(ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(ROT_SPEED)
		+ old_plane_y * cos(ROT_SPEED);
}

/*
To rotate a vector, multiply it with the rotation matrix

[ cos(a) -sin(a) ]
[ sin(a)  cos(a) ]

we apply it to (dir_x, dir_y) and (plane_x, plane_y)
a = -RPT_SPEED (negative angle rotation to have a clockwise rotation),
by convention
*/

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	old_dir_y;
	double	old_plane_y;

	old_dir_x = game->player.dir_x;
	old_dir_y = game->player.dir_y;
	game->player.dir_x = old_dir_x * cos(-ROT_SPEED)
		- old_dir_y * sin(-ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROT_SPEED)
		+ old_dir_y * cos(-ROT_SPEED);
	old_plane_x = game->player.plane_x;
	old_plane_y = game->player.plane_y;
	game->player.plane_x = old_plane_x * cos(-ROT_SPEED)
		- old_plane_y * sin(-ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROT_SPEED)
		+ old_plane_y * cos(-ROT_SPEED);
}

int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		game->keys.esc = 1;
	else if (keycode == 119 || keycode == 65362)
		game->keys.w = 1;
	else if (keycode == 115 || keycode == 65364)
		game->keys.s = 1;
	else if (keycode == 97)
		game->keys.a = 1;
	else if (keycode == 100)
		game->keys.d = 1;
	else if (keycode == 65363)
		game->keys.left = 1;
	else if (keycode == 65361)
		game->keys.right = 1;
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	if (keycode == 65307)
		game->keys.esc = 0;
	else if (keycode == 119 || keycode == 65362)
		game->keys.w = 0;
	else if (keycode == 115 || keycode == 65364)
		game->keys.s = 0;
	else if (keycode == 97)
		game->keys.a = 0;
	else if (keycode == 100)
		game->keys.d = 0;
	else if (keycode == 65363)
		game->keys.left = 0;
	else if (keycode == 65361)
		game->keys.right = 0;
	return (0);
}
