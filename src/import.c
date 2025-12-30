/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:42:52 by mohhusse          #+#    #+#             */
/*   Updated: 2025/10/29 03:14:12 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_cub(char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	return (ft_strcmp(filename + len - 4, ".cub") == 0);
}

size_t	get_map_size(char *filename)
{
	size_t	count;
	int		fd;
	char	*line;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		pexit("Couldn't open file");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

void	import_file(t_game *game, char *filename)
{
	int		fd;
	size_t	i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		pexit("Couldn't open file");
	game->map = ft_calloc(game->map_size, sizeof(char *));
	if (game->map == NULL)
	{
		close(fd);
		pexit("");
	}
	i = 0;
	while (i < game->map_size)
	{
		game->map[i] = get_next_line(fd);
		if (game->map[i] == NULL)
			break ;
		i++;
	}
	close(fd);
}

void	remove_newlines(t_game *game)
{
	char	**new_map;
	size_t	i;

	new_map = ft_calloc(game->map_size, sizeof(char *));
	if (!new_map)
		fexit(game, "");
	i = 0;
	while (i < game->map_size)
	{
		if (!ft_strchr(game->map[i], '\n'))
			new_map[i] = ft_strdup(game->map[i]);
		else
			new_map[i] = ft_strndup(game->map[i], ft_strlen(game->map[i]) - 1);
		i++;
	}
	free_map(game);
	game->map = new_map;
}

void	import_map(t_game *game, int argc, char **argv)
{
	if (argc < 2)
		pexit("Usage: ./cub3D <file.cub>");
	else if (argc > 2)
		pexit("Too many arguments");
	if (argv[1] == NULL || ft_strlen(argv[1]) == 0)
		pexit("");
	if (!is_cub(argv[1]))
		pexit("File of type .cub should be provided");
	game->map_size = get_map_size(argv[1]);
	if (game->map_size == 0)
		pexit("File is empty");
	if (game->map_size < 9)
		pexit("Missing map content");
	import_file(game, argv[1]);
	remove_newlines(game);
	parse_identifiers(game);
	parse_map(game);
}
