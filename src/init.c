/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:25:29 by rtraoui           #+#    #+#             */
/*   Updated: 2025/10/30 10:36:01 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *player)
{
	(*player).pos_x = 22.0;
	(*player).pos_y = 11.5;
	(*player).plane_x = 0.0;
	(*player).plane_y = 0.66;
	(*player).dir_x = -1.0;
	(*player).dir_y = 0.0;
}

void	init_game_struct(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->img.img_ptr = NULL;
	game->img.addr = NULL;
	game->w_texture = NULL;
	game->s_texture = NULL;
	game->n_texture = NULL;
	game->e_texture = NULL;
	game->map = NULL;
	game->map_size = 0;
	game->map_start = 0;
	game->floor_col = -1;
	game->ceiling_col = -1;
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.esc = 0;
	init_player(&game->player);
}

void	init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		fexit(game, "Connection initialization failed");
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"cub3D");
	if (!game->win_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		fexit(game, "Failed loading window");
	}
	game->img.img_ptr = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		fexit(game, "Failed to create image");
	}
	game->img.addr = mlx_get_data_addr(game->img.img_ptr,
			&game->img.bpp, &game->img.line_length, &game->img.endian);
	load_textures(game);
}
