/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:45:36 by rtraoui           #+#    #+#             */
/*   Updated: 2025/10/29 03:53:49 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_tex(t_game *game, t_img *img)
{
	if (img)
	{
		if (img->path)
		{
			free(img->path);
			img->path = NULL;
		}
		if (img->img_ptr)
			mlx_destroy_image(game->mlx_ptr, img->img_ptr);
		free(img);
	}
}

void	free_textures(t_game *game)
{
	free_tex(game, game->n_texture);
	free_tex(game, game->s_texture);
	free_tex(game, game->e_texture);
	free_tex(game, game->w_texture);
	if (game->img.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}

void	get_data_addr(t_img *texture)
{
	texture->addr = mlx_get_data_addr(texture->img_ptr,
			&texture->bpp, &texture->line_length, &texture->endian);
}

void	load_textures(t_game *game)
{
	game->n_texture->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->n_texture->path, &game->n_texture->width,
			&game->n_texture->height);
	game->s_texture->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->s_texture->path, &game->s_texture->width,
			&game->s_texture->height);
	game->e_texture->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->e_texture->path, &game->e_texture->width,
			&game->e_texture->height);
	game->w_texture->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->w_texture->path, &game->w_texture->width,
			&game->w_texture->height);
	if (!game->n_texture->img_ptr || !game->s_texture->img_ptr
		|| !game->e_texture->img_ptr || !game->w_texture->img_ptr)
		fexit(game, "Failed to load texture.");
	get_data_addr(game->n_texture);
	get_data_addr(game->s_texture);
	get_data_addr(game->e_texture);
	get_data_addr(game->w_texture);
}
