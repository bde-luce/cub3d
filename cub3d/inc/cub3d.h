/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/05/13 12:46:43 by bde-luce          #+#    #+#             */
/*   Updated: 2025/05/13 12:46:43 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../src/libft/libft.h"
# include <../mlx_linux/mlx.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_W 1440
# define WIN_H 1020
# define BLOCK 128

# define DEBUG 0

# define CEILING_COLOR 0x87CEEB // Sky Blue
# define FLOOR_COLOR 0x008800   // Green
# define WALL_COLOR 0x8F1A1A    // Red

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359

typedef struct s_player
{
	float x;
	float y;
	float angle;

	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;

	bool left_rotate;
	bool right_rotate;
} t_player;

typedef struct s_game
{
	void *mlx;
	void *win;
	void *img;

	char *data;
	int bpp;
	int size_line;
	int endian;
	t_player player;

	char **map;
} t_game;

typedef struct s_cub3d
{
	char **file;
	char **map;
	int rows;
	char *no;
	char *so;
	char *we;
	char *ea;
	char *f;
	char *c;
	t_game game;
} t_cub3d;

bool	touch(float px, float py, t_game *game);
void	init_player(t_player *player);
void	move_player(t_player *player, t_game *game);
int	key_press(int keycode, t_cub3d *cub3d);
int	key_release(int keycode, t_cub3d *cub3d);

// HOOKS
int	handle_key(int keycode, void *param);
int	handle_close(void *param);

// PARSING
void	file_convert(t_cub3d *cub3d, char **argv);
void	map_validate(t_cub3d *map);
void	free_all(t_cub3d *map);
void	get_map(int i, t_cub3d *cub3d);

#endif