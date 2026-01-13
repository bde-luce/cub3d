/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:46:58 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/09 19:33:41 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
