/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:41:21 by mohhusse          #+#    #+#             */
/*   Updated: 2025/09/10 14:38:19 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_strcmp(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;

	len = 0;
	while (s[len] && len < n)
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

int	array_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	is_empty(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '\n' && s[i] != '\r' && s[i] != '\t' && s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
