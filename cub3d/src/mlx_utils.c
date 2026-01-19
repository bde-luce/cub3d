/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2026/01/15 15:53:00 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/15 15:53:00 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	rgb_to_int(char *rgb)
{
	char	**c;
	int		r;
	int		g;
	int		b;
	int		color;

	c = ft_split(rgb, ',');
	if (!c)
		return (-1);
	r = ft_atoi(c[0]);
	g = ft_atoi(c[1]);
	b = ft_atoi(c[2]);
	free_arr(c);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

void	cleanup_mlx(t_config *config)
{
	if (config->game.no.img)
		mlx_destroy_image(config->game.mlx, config->game.no.img);
	if (config->game.so.img)
		mlx_destroy_image(config->game.mlx, config->game.so.img);
	if (config->game.we.img)
		mlx_destroy_image(config->game.mlx, config->game.we.img);
	if (config->game.ea.img)
		mlx_destroy_image(config->game.mlx, config->game.ea.img);
	if (config->game.img)
		mlx_destroy_image(config->game.mlx, config->game.img);
	if (config->game.win)
		mlx_destroy_window(config->game.mlx, config->game.win);
	if (config->game.mlx)
	{
		mlx_destroy_display(config->game.mlx);
		free(config->game.mlx);
	}
}
