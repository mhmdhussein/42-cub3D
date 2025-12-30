/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:54:37 by mohhusse          #+#    #+#             */
/*   Updated: 2025/10/01 22:49:24 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	pexit(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(1);
}

void	free_split(char **split)
{
	int		i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_map(t_game *game)
{
	size_t		i;

	i = 0;
	if (!game->map)
		return ;
	while (i < game->map_size)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

void	fexit(t_game *game, char *msg)
{
	free_textures(game);
	free_map(game);
	pexit(msg);
}

int	close_game(t_game *game)
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
		free_map(game);
	}
	exit(0);
}
