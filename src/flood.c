/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 22:01:36 by mohhusse          #+#    #+#             */
/*   Updated: 2025/10/30 10:17:35 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_void(char **map, int rows, int r, int c)
{
	size_t	len;
	char	ch;

	if (r < 0 || r >= rows)
		return (1);
	len = ft_strlen(map[r]);
	if (c < 0 || (size_t)c >= len)
		return (1);
	ch = map[r][c];
	return (ch == ' ' || ch == '\t' || ch == '\0');
}

int	is_walkable(char ch)
{
	return (ch == '0' || ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W');
}

int	dfs(t_game *game, int r, int c, char **vis)
{
	char	ch;

	if (is_void(game->map, game->map_size, r, c))
		return (0);
	ch = game->map[r][c];
	if (ch == '1')
		return (1);
	if (!is_walkable(ch))
		return (1);
	if (vis[r][c])
		return (1);
	vis[r][c] = 1;
	return (dfs(game, r - 1, c, vis)
		&& dfs(game, r + 1, c, vis)
		&& dfs(game, r, c - 1, vis)
		&& dfs(game, r, c + 1, vis));
}

void	find_player(char **map, int rows, int *pr, int *pc)
{
	int		i;
	int		j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				*pr = i;
				*pc = j;
				return ;
			}
			j++;
		}
		i++;
	}
	*pr = -1;
	*pc = -1;
}

int	flood_fill(t_game *game)
{
	int				pr;
	int				pc;
	char			**vis;
	size_t			i;
	int				closed;

	find_player(game->map, game->map_size, &pr, &pc);
	if (pr < 0)
		return (0);
	vis = ft_calloc((game->map_size + 1), sizeof(char *));
	if (!vis)
		return (0);
	i = -1;
	while (++i < game->map_size)
	{
		vis[i] = ft_calloc(ft_strlen(game->map[i]) + 1, 1);
		if (!vis[i])
		{
			free_split(vis);
			return (0);
		}
	}
	closed = dfs(game, pr, pc, vis);
	free_split(vis);
	return (closed);
}
