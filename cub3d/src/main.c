/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:54:22 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/09 20:21:13 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_cub3d(t_cub3d *cub3d)
{
	cub3d->file = NULL;
	cub3d->map = NULL;
	cub3d->rows = 0;
	cub3d->no = NULL;
	cub3d->so = NULL;
	cub3d->we = NULL;
	cub3d->ea = NULL;
	cub3d->f = NULL;
	cub3d->c = NULL;
	cub3d->game.mlx = NULL;
	cub3d->game.win = NULL;
}

void find_player_position(t_cub3d *cub3d)
{
    int i, j;
    
    i = 0;
    while (cub3d->map[i])
    {
        j = 0;
        while (cub3d->map[i][j])
        {
            if (cub3d->map[i][j] == 'N' || cub3d->map[i][j] == 'S' ||
                cub3d->map[i][j] == 'E' || cub3d->map[i][j] == 'W')
            {
                // Store player position in map coordinates
                cub3d->game.player.x = j * BLOCK + BLOCK / 2;
                cub3d->game.player.y = i * BLOCK + BLOCK / 2;
                
                // Set angle based on direction
                if (cub3d->map[i][j] == 'N')
                    cub3d->game.player.angle = 3 * PI / 2; // Up
                else if (cub3d->map[i][j] == 'S')
                    cub3d->game.player.angle = PI / 2;     // Down
                else if (cub3d->map[i][j] == 'E')
                    cub3d->game.player.angle = 0;          // Right
                else if (cub3d->map[i][j] == 'W')
                    cub3d->game.player.angle = PI;         // Left
                return;
            }
            j++;
        }
        i++;
    }
}

void	init_player(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;

	player->left_rotate = false;
	player->right_rotate = false;
}

void init_game(t_game *game, t_cub3d *cub3d)
{
	init_player(&game->player);
	game->map = cub3d->map;
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(1);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "Cub3d");
	if (!game->win)
		exit(1);
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img)
		exit(1);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	if (!game->data)
		exit(1);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	key_press(int keycode, t_cub3d *cub3d)
{
	t_player *player = &cub3d->game.player;
	
	if (keycode == 65307)
	{
		mlx_destroy_window(cub3d->game.mlx, cub3d->game.win);
		mlx_destroy_display(cub3d->game.mlx);
		free(cub3d->game.mlx);
		free_all(cub3d);
		exit(0);
	}
	if (keycode == W)
		player->key_up = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_cub3d *cub3d)
{
	t_player *player = &cub3d->game.player;
	
	if (keycode == W)
		player->key_up = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void put_pixel(int x, int y, int color, t_game *game)
{
	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
		return;
	int index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void clear_image(t_game *game)
{
	for (int y = 0; y < WIN_H; y++)
		for (int x = 0; x <WIN_W; x++)
			put_pixel(x, y, 0, game);
}

bool touch(float px, float py, t_game *game)
{
	int x = px / BLOCK;
	int y = py / BLOCK;

	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

void	move_player(t_player *player, t_game *game)
{
	int speed = 10;
	float angle_speed = 0.07;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);

	if (player->left_rotate)
		player->angle -= angle_speed;

	if (player->right_rotate)
		player->angle += angle_speed;
	
	float new_x = player->x;
	float new_y = player->y;

	if (player->angle > 2 * PI)
		player->angle = 0;
	
	if (player->angle < 0)
		player->angle = 2 * PI;

	if (player->key_up)
	{
		new_x += cos_angle * speed;
		new_y += sin_angle * speed;
	}
	if (player->key_down)
	{
		new_x -= cos_angle * speed;
		new_y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		new_x += sin_angle * speed;
		new_y -= cos_angle * speed;
	}
	if (player->key_right)
	{
		new_x -= sin_angle * speed;
		new_y += cos_angle * speed;
	}

	if (!touch(new_x, player->y, game))
        player->x = new_x;
    if (!touch(player->x, new_y, game))
        player->y = new_y;
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, game);
}

void draw_map(t_game *game, int *out_scale)
{
	char **map = game->map;
	int color = 0x0000FF;
	
	// Count map dimensions
	int map_height = 0;
	int map_width = 0;
	while (map[map_height])
	{
		int len = ft_strlen(map[map_height]);
		if (len > map_width)
			map_width = len;
		map_height++;
	}
	
	// Calculate scale to fit window
	int scale_x = WIN_W / map_width;
	int scale_y = WIN_H / map_height;
	int scale = (scale_x < scale_y) ? scale_x : scale_y;
	
	if (scale < 1)
		scale = 1;
	
	*out_scale = scale; // Return the scale for use elsewhere
	
	// Draw scaled map
	for (int y = 0; map[y]; y++)
		for(int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * scale, y * scale, scale, color, game);
}

void draw_minimap_player(t_game *game, int scale)
{
	// Draw player at correct scale
	int player_x = (game->player.x / BLOCK) * scale;
	int player_y = (game->player.y / BLOCK) * scale;
	draw_square(player_x, player_y, 10, 0x00FF00, game);
}

void draw_minimap_ray(float ray_x, float ray_y, int scale, t_game *game)
{
	// Scale the ray position for minimap
	int scaled_x = (ray_x / BLOCK) * scale;
	int scaled_y = (ray_y / BLOCK) * scale;
	put_pixel(scaled_x, scaled_y, 0xFF0000, game);
}

float distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void draw_line(t_player *player, t_game *game, float start_x, int i, int scale)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;

	while(!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			draw_minimap_ray(ray_x, ray_y, scale, game);  // Use scale here
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (DEBUG)
		return;
	
	float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	float height = (BLOCK / dist) * (WIN_W / 2);

	int wall_top = (WIN_H - height) / 2;
	int wall_bottom = wall_top + height;

	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom > WIN_H)
		wall_bottom = WIN_H;
	
	/* CEILING */
	for (int y = 0; y < wall_top; y++)
		put_pixel(i, y, CEILING_COLOR, game);

	/* WALL */
	for (int y = wall_top; y < wall_bottom; y++)
		put_pixel(i, y, WALL_COLOR, game);

	/* FLOOR */
	for (int y = wall_bottom; y < WIN_H; y++)
		put_pixel(i, y, FLOOR_COLOR, game);
}

int	draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(&game->player, game);
	clear_image(game);
	
	int scale = 1;
	if (DEBUG)
	{
		draw_map(game, &scale);
		draw_minimap_player(game, scale);
	}
	
	float fraction = PI / 3 / WIN_W;
	float start_x = player->angle - PI / 6;
	int i = 0;
	while (i < WIN_W)
	{
		draw_line(player, game, start_x, i, scale);  // Pass scale here
		start_x += fraction;
		i++;
	}
	
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3d map.cub\n", 29);
		return (1);
	}
	init_cub3d(&cub3d);

	file_convert(&cub3d, argv);
	map_validate(&cub3d);
	find_player_position(&cub3d);

	init_game(&cub3d.game, &cub3d);
	mlx_hook(cub3d.game.win, 2, 1L<<0, key_press, &cub3d);
	mlx_hook(cub3d.game.win, 3, 1L<<1, key_release, &cub3d);
	mlx_hook(cub3d.game.win, 17, 0, handle_close, &cub3d);
	
	mlx_loop_hook(cub3d.game.mlx, draw_loop, &cub3d.game);
	mlx_loop(cub3d.game.mlx);

	free_all(&cub3d);
	return (0);
}
