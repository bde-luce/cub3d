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

int	handle_key(int keycode, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (keycode == 65307)
	{
		mlx_destroy_window(cub3d->game.mlx, cub3d->game.win);
		mlx_destroy_display(cub3d->game.mlx);
		free(cub3d->game.mlx);
		free_all(cub3d);
		exit(0);
	}
	return (0);
}

int	handle_close(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	mlx_destroy_window(cub3d->game.mlx, cub3d->game.win);
	mlx_destroy_display(cub3d->game.mlx);
	free(cub3d->game.mlx);
	free_all(cub3d);
	exit(0);
	return (0);
}
