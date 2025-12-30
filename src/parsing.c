/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:15:50 by mohhusse          #+#    #+#             */
/*   Updated: 2025/10/02 00:39:05 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img	*init_texture(void)
{
	t_img	*texture;

	texture = malloc(sizeof(t_img));
	if (!texture)
		return (NULL);
	texture->img_ptr = NULL;
	texture->addr = NULL;
	texture->path = NULL;
	return (texture);
}

void	load_texture(t_game *game, t_img **texture, char **split)
{
	if (*texture)
	{
		free_split(split);
		fexit(game, "Invalid texture file");
	}
	(*texture) = init_texture();
	if (*texture == NULL)
	{
		free_split(split);
		fexit(game, "Memory allocation failed");
	}
	(*texture)->path = ft_strdup(split[1]);
	if ((*texture)->path == NULL)
	{
		free_split(split);
		free(*texture);
		*texture = NULL;
		fexit(game, "Invalid texture file");
	}
}

int	parse_params(t_game *game, char **split)
{
	if (!ft_strcmp(split[0], "NO"))
		load_texture(game, &game->n_texture, split);
	else if (!ft_strcmp(split[0], "SO"))
		load_texture(game, &game->s_texture, split);
	else if (!ft_strcmp(split[0], "EA"))
		load_texture(game, &game->e_texture, split);
	else if (!ft_strcmp(split[0], "WE"))
		load_texture(game, &game->w_texture, split);
	else if (!ft_strcmp(split[0], "C"))
		load_color(game, &game->ceiling_col, split);
	else if (!ft_strcmp(split[0], "F"))
		load_color(game, &game->floor_col, split);
	else
		return (0);
	return (1);
}

int	check_loaded_params(t_game *game)
{
	return (game->n_texture != NULL && game->w_texture != NULL
		&& game->s_texture != NULL && game->e_texture != NULL
		&& game->ceiling_col != -1 && game->floor_col != -1);
}

void	parse_identifiers(t_game *game)
{
	char	**split;
	size_t	i;

	i = -1;
	while (++i < game->map_size)
	{
		if (!is_empty(game->map[i]))
		{
			split = ft_split(game->map[i], ' ');
			if (array_size(split) != 2)
			{
				free_split(split);
				break ;
			}
			if (!parse_params(game, split))
			{
				free_split(split);
				break ;
			}
			free_split(split);
		}
	}
	if (!check_loaded_params(game) || i == game->map_size)
		fexit(game, "Invalid map content");
	game->map_start = i;
}
