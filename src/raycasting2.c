/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:15:55 by rtraoui           #+#    #+#             */
/*   Updated: 2025/10/29 04:07:30 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_color(t_img *tex, t_wall *wall, double tex_pos)
{
	int	tex_h;
	int	color;
	int	*pixel_data;

	pixel_data = (int *)tex->addr;
	tex_h = (int)tex_pos & (TEX_HEIGHT - 1);
	color = pixel_data[TEX_HEIGHT * tex_h + wall->tex_w];
	return (color);
}

void	draw_wall_stripe(t_game *game, t_wall *wall, t_ray *ray, int w)
{
	t_img	*tex;
	double	scale;
	double	tex_pos;
	int		h;
	int		color;

	tex = choose_texture(game, wall);
	scale = 1.0 * TEX_HEIGHT / wall->line_height;
	tex_pos = (wall->draw_start - WIN_HEIGHT / 2 + wall->line_height / 2)
		* scale;
	h = wall->draw_start;
	while (h < wall->draw_end)
	{
		color = get_color(tex, wall, tex_pos);
		if (ray->side == 'H')
			color = (color >> 1) & 8355711;
		put_pixel_to_image(&game->img, w, h, color);
		tex_pos += scale;
		h++;
	}
}

void	draw_ceiling_and_floor(t_game *game, int w, t_wall *wall)
{
	int	h;

	h = 0;
	while (h < wall->draw_start)
	{
		put_pixel_to_image(&game->img, w, h, game->ceiling_col);
		h++;
	}
	h = wall->draw_end;
	while (h < WIN_HEIGHT)
	{
		put_pixel_to_image(&game->img, w, h, game->floor_col);
		h++;
	}
}

void	calculate_texture_coordinates(t_ray *ray, t_wall *wall, t_game *game)
{
	if (ray->side == 'V')
	{
		if (ray->ray_dir_x > 0)
			wall->tex_type = 'e';
		else
			wall->tex_type = 'w';
		wall->wall_hit_pt = game->player.pos_y
			+ ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			wall->tex_type = 's';
		else
			wall->tex_type = 'n';
		wall->wall_hit_pt = game->player.pos_x
			+ ray->perp_wall_dist * ray->ray_dir_x;
	}
	wall->wall_hit_pt -= floor(wall->wall_hit_pt);
	wall->tex_w = (int)(wall->wall_hit_pt * (double)TEX_WIDTH);
	if (ray->side == 'V' && ray->ray_dir_x > 0)
		wall->tex_w = TEX_WIDTH - wall->tex_w - 1;
	if (ray->side == 'H' && ray->ray_dir_y < 0)
		wall->tex_w = TEX_WIDTH - wall->tex_w - 1;
}

void	calculate_draw_parameters(t_ray *ray, t_wall *wall)
{
	wall->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	wall->draw_start = -wall->line_height / 2 + WIN_HEIGHT / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + WIN_HEIGHT / 2;
	if (wall->draw_end >= WIN_HEIGHT)
		wall->draw_end = WIN_HEIGHT - 1;
}
