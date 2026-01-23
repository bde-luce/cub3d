/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:08:53 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/23 16:08:53 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * Draws a pixel at the given screen coordinates with the specified color.
 */
void	put_pixel(int x, int y, int color, const t_game *game)
{
	int	index;

	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

/**
 * Draws a pixel at the given screen coordinates with the specified color.
 */
void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}
