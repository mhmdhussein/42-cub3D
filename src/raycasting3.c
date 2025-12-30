/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:02:10 by rtraoui           #+#    #+#             */
/*   Updated: 2025/10/29 03:51:03 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel_to_image(t_img *img, int w, int h, int color)
{
	char	*dst;
	int		pix_mem;

	if (w >= 0 && w < WIN_WIDTH && h >= 0 && h < WIN_HEIGHT)
	{
		pix_mem = h * img->line_length + w * (img->bpp / 8);
		dst = img->addr + pix_mem;
		*(unsigned int *)dst = color;
	}
}

t_img	*choose_texture(t_game *game, t_wall *wall)
{
	if (wall->tex_type == 'n')
		return (game->n_texture);
	else if (wall->tex_type == 's')
		return (game->s_texture);
	else if (wall->tex_type == 'e')
		return (game->e_texture);
	else
		return (game->w_texture);
}
