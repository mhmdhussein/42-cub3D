/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:04:24 by mohhusse          #+#    #+#             */
/*   Updated: 2025/10/29 03:55:39 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include <string.h>

# define WIN_HEIGHT 800
# define WIN_WIDTH 1200
# define TEX_HEIGHT 64
# define TEX_WIDTH 64
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05

// ~~~~~~~~~~ Structs ~~~~~~~~~~

/* Keys Structure */
typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
	int	esc;
}	t_keys;

/* Image Structure */
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	char	*path;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* Player Structure */
typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		plane_x;
	double		plane_y;
	double		dir_x;
	double		dir_y;	
}	t_player;

/* Ray Structue */
typedef struct s_ray
{
	int			map_x;
	int			map_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	char		side;
}	t_ray;

/* Wall Structure */
typedef struct s_wall
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	char	tex_type;
	double	wall_hit_pt;
	int		tex_w;
}	t_wall;

typedef struct s_game
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
	t_player		player;
	t_img			*w_texture;
	t_img			*s_texture;
	t_img			*n_texture;
	t_img			*e_texture;
	char			**map;
	size_t			map_size;
	size_t			map_start;
	int32_t			floor_col;
	int32_t			ceiling_col;
	t_keys			keys;
}	t_game;

// ~~~~~~~~~~ Import ~~~~~~~~~~
void	import_map(t_game *game, int argc, char **argv);
void	remove_newlines(t_game *game);
void	parse_identifiers(t_game *game);
void	parse_map(t_game *game);
void	load_color(t_game *game, int32_t *color, char **split);
int		flood_fill(t_game *game);

// ~~~~~~~~~~ Utils ~~~~~~~~~~
void	pexit(char *msg);
void	fexit(t_game *game, char *msg);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strndup(const char *s, size_t n);
void	free_map(t_game *game);
void	free_split(char **split);
int		array_size(char **split);
int		is_empty(char *s);

// ~~~~~~~~~~ Game ~~~~~~~~~~
void	init_player(t_player *player);
void	init_player_from_map(t_game *game);
void	init_game_struct(t_game *game);
void	init_game(t_game *game);
int		close_game(t_game *game);
int		handle_key_press(int keycode, t_game *game);
int		handle_key_release(int keycode, t_game *game);
void	free_tex(t_game *game, t_img *img);
void	free_textures(t_game *game);

// ~~~~~~~~~~ Render ~~~~~~~~~~
void	load_textures(t_game *game);
int		render_map(t_game *game);
void	calculate_ray(t_game *game, t_ray *ray, int w);
void	calculate_step_and_side_dist(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
void	perp_wall_dist(t_ray *ray);
void	calculate_draw_parameters(t_ray *ray, t_wall *wall);
void	draw_wall_stripe(t_game *game, t_wall *wall, t_ray *ray, int w);
void	draw_ceiling_and_floor(t_game *game, int w, t_wall *wall);
void	calculate_texture_coordinates(t_ray *ray, t_wall *wall, t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
void	put_pixel_to_image(t_img *img, int w, int h, int color);
t_img	*choose_texture(t_game *game, t_wall *wall);

#endif
