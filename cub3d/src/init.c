/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:46:58 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/19 11:04:20 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void find_player_position(t_config *config)
{
    int i, j;
    
    i = 0;
    while (config->map[i])
    {
        j = 0;
        while (config->map[i][j])
        {
            if (config->map[i][j] == 'N' || config->map[i][j] == 'S' ||
                config->map[i][j] == 'E' || config->map[i][j] == 'W')
            {
                // Store player position in map coordinates
                config->game.player.x = j * BLOCK + BLOCK / 2;
                config->game.player.y = i * BLOCK + BLOCK / 2;
                
                // Set angle based on direction
                if (config->map[i][j] == 'N')
                    config->game.player.angle = 3 * PI / 2; // Up
                else if (config->map[i][j] == 'S')
                    config->game.player.angle = PI / 2;     // Down
                else if (config->map[i][j] == 'E')
                    config->game.player.angle = 0;          // Right
                else if (config->map[i][j] == 'W')
                    config->game.player.angle = PI;         // Left
                return;
            }
            j++;
        }
        i++;
    }
}

static void	load_texture(t_game *game, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		exit(1);
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line, &tex->endian);
	if (!tex->data)
		exit(1);
}

static void load_all_textures(t_game *game, t_config *config)
{
    load_texture(game, &game->no, config->no);
    load_texture(game, &game->so, config->so);
    load_texture(game, &game->we, config->we);
    load_texture(game, &game->ea, config->ea);
}

void init_game(t_game *game, t_config *config)
{
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
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	if (!game->data)
		exit(1);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
