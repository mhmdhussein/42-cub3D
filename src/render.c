/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:01:35 by rtraoui           #+#    #+#             */
/*   Updated: 2025/10/29 03:51:39 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	process_movement(t_game	*game)
{
	if (game->keys.esc)
		close_game(game);
	if (game->keys.a)
		move_left(game);
	if (game->keys.d)
		move_right(game);
	if (game->keys.w)
		move_forward(game);
	if (game->keys.s)
		move_backward(game);
	if (game->keys.right)
		rotate_right(game);
	if (game->keys.left)
		rotate_left(game);
}

int	render_map(t_game *game)
{
	t_ray	ray;
	t_wall	wall;
	int		w;

	process_movement(game);
	w = 0;
	while (w < WIN_WIDTH)
	{
		calculate_ray(game, &ray, w);
		calculate_step_and_side_dist(game, &ray);
		perform_dda(game, &ray);
		perp_wall_dist(&ray);
		calculate_draw_parameters(&ray, &wall);
		calculate_texture_coordinates(&ray, &wall, game);
		draw_ceiling_and_floor(game, w, &wall);
		draw_wall_stripe(game, &wall, &ray, w);
		w++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->img.img_ptr, 0, 0);
	return (0);
}
