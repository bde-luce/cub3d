/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:24:54 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/23 15:59:43 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** Returns the color of a texture pixel at the given texture coordinates.
*/
static int	get_tex_color(const t_ray *ray, int tex_y)
{
	int	index;
	int	color;

	index = tex_y * ray->tex->size_line + ray->tex_x * (ray->tex->bpp / 8);
	color = ray->tex->data[index] | (ray->tex->data[index + 1] << 8)
		| (ray->tex->data[index + 2] << 16);
	return (color);
}

/*
** Clamps a texture Y coordinate to valid bounds.
*/
static int	clamp_tex_y(int tex_y, int height)
{
	if (tex_y < 0)
		return (0);
	if (tex_y >= height)
		return (height - 1);
	return (tex_y);
}

/*
** Draws the textured wall slice for a single screen column.
*/
static void	draw_texture_line(float x, t_ray *ray, const t_game *game)
{
	int		y;
	float	step;
	float	tex_pos;

	get_right_tex(ray, game);
	get_tex_x(ray, &game->player);
	step = (float)ray->tex->height / (float)(ray->draw_end - ray->draw_start);
	tex_pos = (ray->draw_start - WIN_H / 2.0f
			+ (ray->draw_end - ray->draw_start) / 2.0f) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		put_pixel(x, y, get_tex_color(ray, clamp_tex_y((int)tex_pos,
					ray->tex->height)), game);
		tex_pos += step;
		y++;
	}
}

/*
** Draws a full vertical column including ceiling, wall, and floor.
*/
void	draw_column(float x, t_ray *ray, const t_game *game)
{
	int	line_height;
	int	y;

	line_height = WIN_H / ray->perp_wall_dist;
	ray->draw_start = WIN_H / 2 - line_height / 2;
	ray->draw_end = WIN_H / 2 + line_height / 2;
	y = 0;
	while (y < ray->draw_start)
		put_pixel(x, y++, game->ceiling_color, game);
	draw_texture_line(x, ray, game);
	y = ray->draw_end;
	while (y < WIN_H)
		put_pixel(x, y++, game->floor_color, game);
}
