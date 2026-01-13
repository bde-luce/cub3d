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

void	init_cub3d(t_cub3d *cub3d)
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

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3d map.cub\n", 29);
		return (1);
	}

	ft_bzero(&cub3d, sizeof(t_cub3d));
	init_cub3d(&cub3d);

	file_convert(&cub3d, argv);
	map_validate(&cub3d);
	find_player_position(&cub3d);

	cub3d.game.floor_color   = rgb_to_int(cub3d.f);
	cub3d.game.ceiling_color = rgb_to_int(cub3d.c);

	init_game(&cub3d.game, &cub3d);
	mlx_hook(cub3d.game.win, 2, 1L<<0, key_press, &cub3d);
	mlx_hook(cub3d.game.win, 3, 1L<<1, key_release, &cub3d);
	mlx_hook(cub3d.game.win, 17, 0, handle_close, &cub3d);
	
	mlx_loop_hook(cub3d.game.mlx, draw_loop, &cub3d.game);
	mlx_loop(cub3d.game.mlx);

	free_all(&cub3d);
	return (0);
}
