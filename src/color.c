/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:29:36 by mohhusse          #+#    #+#             */
/*   Updated: 2025/10/30 10:36:42 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	str_isnum(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int32_t	rgbtoi(char *s)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	if (s[i] == '+' || s[i] == '-')
		if (s[i++] == '-')
			sign = -1;
	while (ft_isdigit(s[i]))
		num = (num * 10) + (sign * (s[i++] - '0'));
	if (num > 255 || num < 0)
		return (-1);
	return (num);
}

int32_t	get_hex(int r, int g, int b, int a)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int32_t	rgb_to_hex(t_game *game, char **split)
{
	char	**nums;
	int32_t	rgb[3];
	int32_t	hex;

	nums = ft_split(split[1], ',');
	if (array_size(nums) != 3 || !str_isnum(nums[0]) || !str_isnum(nums[1])
		|| !str_isnum(nums[2]))
	{
		free_split(nums);
		free_split(split);
		fexit(game, "Invalid map content");
	}
	rgb[0] = rgbtoi(nums[0]);
	rgb[1] = rgbtoi(nums[1]);
	rgb[2] = rgbtoi(nums[2]);
	if (rgb[0] == -1 || rgb[1] == -1 || rgb[2] == -1)
	{
		free_split(nums);
		free_split(split);
		fexit(game, "Invalid map content");
	}
	hex = get_hex(rgb[0], rgb[1], rgb[2], 1);
	free_split(nums);
	return (hex);
}

void	load_color(t_game *game, int32_t *color, char **split)
{
	if (*color != -1)
	{
		free_split(split);
		fexit(game, "Invalid color");
	}
	*color = rgb_to_hex(game, split);
	if (*color == -1)
	{
		free_split(split);
		fexit(game, "Invalid color");
	}
}
