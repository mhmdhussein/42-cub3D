/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:42:01 by mohhusse          #+#    #+#             */
/*   Updated: 2025/10/30 10:14:09 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_map_line(char *s)
{
	int	i;

	if (is_empty(s))
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '1' && s[i] != '0' && s[i] != 'N'
			&& s[i] != 'S' && s[i] != 'W' && s[i] != 'E')
			return (0);
		i++;
	}
	return (1);
}

size_t	check_empty_lines(t_game *game)
{
	size_t	i;
	size_t	j;

	i = game->map_start;
	j = 0;
	while (i < game->map_size && is_map_line(game->map[i]))
	{
		i++;
		j++;
	}
	if (j < 3)
		fexit(game, "Invalid map content");
	if (i != game->map_size)
	{
		while (i < game->map_size)
		{
			if (!is_empty(game->map[i]))
				fexit(game, "Invalid map content");
			i++;
		}
	}
	return (j);
}

void	copy_map(t_game *game, size_t size)
{
	size_t	i;
	size_t	j;
	char	**map;

	map = ft_calloc(size, sizeof(char *));
	if (!map)
		fexit(game, "");
	i = game->map_start;
	j = 0;
	while (size)
	{
		map[j++] = ft_strdup(game->map[i++]);
		size--;
	}
	free_map(game);
	game->map = map;
	game->map_size = j;
}

void	check_player(t_game *game)
{
	size_t	i;
	size_t	j;
	int		player;

	i = 0;
	player = 0;
	while (i < game->map_size)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'W' || game->map[i][j] == 'E')
			{
				if (player)
					fexit(game, "Only one player allowed");
				player = 1;
			}
			j++;
		}
		i++;
	}
	if (!player)
		fexit(game, "No player found");
}

void	parse_map(t_game *game)
{
	size_t	size;

	size = check_empty_lines(game);
	copy_map(game, size);
	check_player(game);
	if (!flood_fill(game))
		fexit(game, "Invalid map content");
}
