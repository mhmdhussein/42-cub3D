/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:05:59 by mohhusse          #+#    #+#             */
/*   Updated: 2025/10/30 10:01:16 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	init_game_struct(&game);
	import_map(&game, argc, argv);
	init_player_from_map(&game);
	init_game(&game);
	mlx_loop_hook(game.mlx_ptr, render_map, &game);
	mlx_hook(game.win_ptr, 2, 1L << 0, handle_key_press, &game);
	mlx_hook(game.win_ptr, 3, 1l << 1, handle_key_release, &game);
	mlx_hook(game.win_ptr, 17, 0, close_game, &game);
	mlx_loop(game.mlx_ptr);
	free_map(&game);
	return (0);
}
