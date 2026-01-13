#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include "mlx.h"
# include "../src/libft/libft.h"

# define WIN_W 1280
# define WIN_H 720
# define BLOCK 64
# define PI 3.14159265359

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define WALL_COLOR 0xFF0000

# define DEBUG 0

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	char	**map;
	int		floor_color;
	int		ceiling_color;
	t_player	player;
}	t_game;

typedef struct s_cub3d
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
}	t_cub3d;

// INIT
void	init_cub3d(t_cub3d *cub3d);
void	init_player(t_player *player);
void	init_game(t_game *game, t_cub3d *cub3d);
void	find_player_position(t_cub3d *cub3d);

// MLX_UTILS
int		rgb_to_int(char *rgb);
void	cleanup_mlx(t_cub3d *cub3d);

// HOOKS
int		key_press(int keycode, t_cub3d *cub3d);
int		key_release(int keycode, t_cub3d *cub3d);
int		handle_key(int keycode, void *param);
int		handle_close(void *param);

// PLAYER
bool	touch(float px, float py, t_game *game);
void	move_player(t_player *player, t_game *game);
float	distance(float x, float y);
float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game);

// IMAGE
void	put_pixel(int x, int y, int color, t_game *game);
void	clear_image(t_game *game);
void	draw_square(int x, int y, int size, int color, t_game *game);

// MINIMAP
void	draw_map(t_game *game, int *out_scale);
void	draw_minimap_player(t_game *game, int scale);
void	draw_minimap_ray(float ray_x, float ray_y, int scale, t_game *game);

// RENDERING
int		draw_loop(t_game *game);
void	draw_line(t_player *player, t_game *game, float start_x, int i, int scale);

// PARSING
// PARSING FILE
void	free_all(t_cub3d *cub3d);
void	file_convert(t_cub3d *cub3d, char **argv);
void	print_file(t_cub3d *cub3d);

// PARSING ELEMENTS
void	skip_id_prefix(char *info_type, int *i);
char	*get_info(char *info_type, char *element, t_cub3d *cub3d);
int		check_elem_id(t_cub3d *cub3d, char *element);
void	check_info(char *info, char *info_type, t_cub3d *cub3d);
void	validate_elements(int *i, t_cub3d *cub3d);

// PARSING COLORS
int		check_color_range(char *color);
void	check_info_color(char *info, t_cub3d *cub3d);
int		count_commas(char *s);

// PARSING MAP CHECKS
void	check_char_is_valid(t_cub3d *cub3d);
void	check_only_1player(t_cub3d *cub3d);
int		is_player_or_zero(char c);
void	check_1st_and_last_line(t_cub3d *cub3d);
void	check_middle(t_cub3d *cub3d);
void	check_map_is_closed(t_cub3d *cub3d);
void	validate_map(t_cub3d *cub3d);

// PARSING MAP
int		line_is_empty(char *str);
int		nbr_rows(int i, t_cub3d *cub3d);
void	get_map(int i, t_cub3d *cub3d);
void	print_map(t_cub3d *cub3d);

// PARSING UTILITIES
void	free_arr(char **arr);
int		arr_len(char **arr);
int		str_isdigit(char *str);
int		is_hws(char c);
int		is_ws(char c);
int		skip_hwhitespace(char *str, int *i);
void	skip_pos_signal(char *str, int *i);
void	skip_word(char *str, int *i);
int		count_trailing_ws(char *str);

// PARSING
void	error_exit(char *str, t_cub3d *cub3d);
void	map_validate(t_cub3d *cub3d);

#endif