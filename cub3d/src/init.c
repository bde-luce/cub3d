/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:46:58 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/19 17:18:24 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_player(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

static void	load_texture(t_game *game, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		exit(1);
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->size_line, &tex->endian);
	if (!tex->data)
		exit(1);
}

static void	load_all_textures(t_game *game, t_config *config)
{
	load_texture(game, &game->no, config->no);
	load_texture(game, &game->so, config->so);
	load_texture(game, &game->we, config->we);
	load_texture(game, &game->ea, config->ea);
}

void	init_game(t_game *game, t_config *config)
{
	init_player(&game->player);
	game->map = config->map;
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(1);
	load_all_textures(game, config);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "Cub3d");
	if (!game->win)
		exit(1);
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img)
		exit(1);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
		exit(1);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
