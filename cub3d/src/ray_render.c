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
	int		start;
	int		end;

	get_right_tex(ray, game);
	get_tex_x(ray, &game->player);
	
	// Clamp drawing bounds to screen
	start = ray->draw_start;
	end = ray->draw_end;
	if (start < 0)
		start = 0;
	if (end > WIN_H)
		end = WIN_H;
	
	step = (float)ray->tex->height / (float)(ray->draw_end - ray->draw_start);
	tex_pos = (start - WIN_H / 2.0f
			+ (ray->draw_end - ray->draw_start) / 2.0f) * step;
	
	y = start;
	while (y < end)
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
	int	ceiling_end;
	int	floor_start;

	line_height = WIN_H / ray->perp_wall_dist;
	ray->draw_start = WIN_H / 2 - line_height / 2;
	ray->draw_end = WIN_H / 2 + line_height / 2;
	
	// Clamp ceiling/floor rendering bounds
	ceiling_end = ray->draw_start;
	if (ceiling_end < 0)
		ceiling_end = 0;
	if (ceiling_end > WIN_H)
		ceiling_end = WIN_H;
	
	floor_start = ray->draw_end;
	if (floor_start < 0)
		floor_start = 0;
	if (floor_start > WIN_H)
		floor_start = WIN_H;
	
	// Draw ceiling
	y = 0;
	while (y < ceiling_end)
		put_pixel(x, y++, game->ceiling_color, game);
	
	// Draw textured wall
	draw_texture_line(x, ray, game);
	
	// Draw floor
	y = floor_start;
	while (y < WIN_H)
		put_pixel(x, y++, game->floor_color, game);
}
