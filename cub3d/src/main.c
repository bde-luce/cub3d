/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:54:22 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/15 13:13:00 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_config	config;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3d map.cub\n", 29);
		return (1);
	}

	ft_bzero(&config, sizeof(t_config));

	file_convert(&config, argv);
	map_validate(&config);
	find_player_position(&config);

	config.game.floor_color   = rgb_to_int(config.f);
	config.game.ceiling_color = rgb_to_int(config.c);

	init_game(&config.game, &config);
	mlx_hook(config.game.win, 2, 1L<<0, key_press, &config);
	mlx_hook(config.game.win, 3, 1L<<1, key_release, &config);
	mlx_hook(config.game.win, 17, 0, handle_close, &config);
	
	mlx_loop_hook(config.game.mlx, draw_loop, &config.game);
	mlx_loop(config.game.mlx);

	free_config(&config);
	return (0);
}
