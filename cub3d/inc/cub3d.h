/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:43:52 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/19 16:43:52 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../src/libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_W 1280
# define WIN_H 720
# define PI 3.14159265359
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define DDA_INF_DIST 1e30

typedef struct s_tex
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}			t_tex;

typedef struct s_ray
{
	float		ray_dir_x;
	float		ray_dir_y;
	int			map_x;
	int			map_y;
	float		delta_dist_x;
	float		delta_dist_y;
	float		side_dist_x;
	float		side_dist_y;
	int			side;
	int			step_x;
	int			step_y;
	bool		hit;
	float		perp_wall_dist;
	const t_tex	*tex;
	int			tex_x;
	int			draw_start;
	int			draw_end;
}			t_ray;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}			t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	char		**map;
	int			floor_color;
	int			ceiling_color;
	t_tex		no;
	t_tex		so;
	t_tex		we;
	t_tex		ea;
	t_player	player;
}				t_game;

typedef struct s_config
{
	char	**file;
	char	**map;
	int		rows;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	t_game	game;
}			t_config;

// PARSING
// PARSING CONFIG
void	free_arr(char **arr);
void	free_config(t_config *config);
void	error_exit(char *str, t_config *config);

// PARSING FILE
void	file_convert(t_config *config, char **argv);

// PARSING ELEMENTS
char	*get_info(int i, char *info_type, char *elem, t_config *config);
void	validate_elements(int *i, t_config *config);

// PARSING MAP
void	get_map(int i, t_config *config);

//PARSING MAPCHECK
void	check_map_is_closed(t_config *config);
void	validate_map_content(t_config *config);

// PARSING PIPELINE
void	map_validate(t_config *config);

// PARSING UTILS
int		is_hws(char c);
int		arr_len(char **arr);
void	skip_pos_signal(char *str, int *i);
void	skip_hwhitespace(char *str, int *i);
int		count_trailing_ws(char *str);

// INIT_GAME
void	init_game(t_game *game, t_config *config);

// MLX_UTILS
int		rgb_to_int(char *rgb);
void	cleanup_mlx(t_config *config);

// HOOKS
int		key_press(int keycode, t_config *config);
int		key_release(int keycode, t_config *config);
int		handle_close(void *param);

// PLAYER
// PLAYER_SETUP
void	find_player_position(t_config *config);
// PLAYER_MOVE
void	move_player(t_player *player, t_game *game);
// PLAYER_UTILS
bool	touch(float px, float py, const t_game *game);

// IMAGE
void	put_pixel(int x, int y, int color, const t_game *game);
void	clear_image(t_game *game);

// RAY
//RAY_SETUP
void	get_ray_direction(t_ray *ray, const t_player *player, float x);
void	get_ray_grid(t_ray *ray, const t_player *player);
void	get_ray_step(t_ray *ray, const t_player *player);
// RAY_RENDER
void	draw_column(float x, t_ray *ray, const t_game *game);
// RAY_CAST
int		ray_cast(t_config *config);

// RENDER_UTILS
void	get_right_tex(t_ray *ray, const t_game *game);
void	get_tex_x(t_ray *ray, const t_player *player);

#endif