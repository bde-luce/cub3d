/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:54:22 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/07 16:55:08 by frteixei         ###   ########.fr       */
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
	cub3d->mlx.mlx = NULL;
	cub3d->mlx.win = NULL;
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

	/* parsing */
	file_convert(&cub3d, argv);
	map_validate(&cub3d);

	/* mlx */
	init_mlx(&cub3d.mlx);
	mlx_key_hook(cub3d.mlx.win, handle_key, &cub3d);
	mlx_hook(cub3d.mlx.win, 17, 0, handle_close, &cub3d);
	mlx_loop(cub3d.mlx.mlx);

	free_all(&cub3d);
	return (0);
}
