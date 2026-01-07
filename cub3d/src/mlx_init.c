/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:46:58 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/07 16:56:12 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		perror("mlx_init");
		exit(EXIT_FAILURE);
	}
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cub3D");
	if (!mlx->win)
	{
		perror("mlx_new_window");
		exit(EXIT_FAILURE);
	}
}

/*
KEY_ESC		65307
KEY_W		119
KEY_A		97
KEY_S		115
KEY_D		100
KEY_LEFT	65361
KEY_RIGHT	65363
*/

int	handle_key(int keycode, void *param)
{
	t_cub3d *cub3d;

	cub3d = (t_cub3d *)param;
	if (keycode == 65307)
	{
		mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win);
		mlx_destroy_display(cub3d->mlx.mlx);
		free(cub3d->mlx.mlx);
		free_all(cub3d);
		exit(0);
	}
	if (keycode == 119)
		printf("W pressed\n");
	if (keycode == 97)
		printf("A pressed\n");
	if (keycode == 115)
		printf("S pressed\n");
	if (keycode == 100)
		printf("D pressed\n");
	if (keycode == 65361)
		printf("Left arrow\n");
	if (keycode == 65363)
		printf("Right arrow\n");
	return (0);
}

int	handle_close(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}
