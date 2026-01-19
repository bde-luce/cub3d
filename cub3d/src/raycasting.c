/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:00:00 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/19 17:19:27 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** Advances the ray step by step in the ray direction until a wall is hit
** and records the wall side hit.
*/
void	cast_ray(t_hit *hit, t_game *game, float start_x)
{
	float	cos_angle;
	float	sin_angle;
	float	prev_x;
	float	prev_y;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	prev_x = hit->ray_x;
	prev_y = hit->ray_y;
	while (!touch(hit->ray_x, hit->ray_y, game))
	{
		prev_x = hit->ray_x;
		prev_y = hit->ray_y;
		hit->ray_x += cos_angle;
		hit->ray_y += sin_angle;
	}
	hit->side = get_side(prev_x, prev_y, hit->ray_x, hit->ray_y);
}

/*
** Draws a vertical textured wall slice on screen by mapping texture pixels
** to the corresponding screen column between the wall's top and bottom.
*/
static int	get_tex_color(t_hit *hit, int tex_y)
{
	int	index;
	int	color;

	index = tex_y * hit->tex->size_line + hit->tex_x * (hit->tex->bpp / 8);
	color = hit->tex->data[index] | (hit->tex->data[index + 1] << 8)
		| (hit->tex->data[index + 2] << 16);
	return (color);
}

static int	clamp_tex_y(int tex_y, int height)
{
	if (tex_y < 0)
		return (0);
	if (tex_y >= height)
		return (height - 1);
	return (tex_y);
}

void	draw_texture_line(t_hit *hit, t_game *game)
{
	int		y;
	float	step;
	float	tex_pos;

	step = (float)hit->tex->height / (float)(hit->bottom - hit->top);
	tex_pos = (hit->top - WIN_H / 2.0f + (hit->bottom - hit->top) / 2.0f)
		* step;
	y = hit->top;
	while (y < hit->bottom)
	{
		put_pixel(hit->screen_x, y,
			get_tex_color(hit, clamp_tex_y((int)tex_pos, hit->tex->height)),
			game);
		tex_pos += step;
		y++;
	}
}
