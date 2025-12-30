/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:12:00 by rtraoui           #+#    #+#             */
/*   Updated: 2025/10/29 03:15:58 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_position(t_game *game, double x, double y)
{
	int		map_x;
	int		map_y;
	double	buffer;

	map_x = (int)x;
	map_y = (int)y;
	buffer = 0.2;
	if (map_y < 0 || map_y >= (int)game->map_size)
		return (0);
	if (map_x < 0 || map_x >= (int)ft_strlen(game->map[map_y]))
		return (0);
	if (game->map[map_y][map_x] == '1')
		return (0);
	if (game->map[(int)(y - buffer)][(int)(x)] == '1' ||
		game->map[(int)(y + buffer)][(int)(x)] == '1' ||
		game->map[(int)(y)][(int)(x - buffer)] == '1' ||
		game->map[(int)(y)][(int)(x + buffer)] == '1')
		return (0);
	return (1);
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.plane_x * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.plane_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.plane_x * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.plane_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}
