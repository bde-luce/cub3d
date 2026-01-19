/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:53:29 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/19 17:00:00 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** Computes the projected wall height and vertical screen bounds based on the
** corrected distance from the player to the wall hit.
*/
void	compute_wall_slice(t_hit *hit, t_player *player)
{
	float	dist;
	float	height;

	dist = fixed_dist(player, hit->ray_x, hit->ray_y);
	height = (BLOCK / dist) * (WIN_W / 2);
	hit->top = (WIN_H - height) / 2;
	hit->bottom = hit->top + height;
	if (hit->top < 0)
		hit->top = 0;
	if (hit->bottom > WIN_H)
		hit->bottom = WIN_H;
}

/*
** Renders a single vertical screen column by casting a ray, selecting the
** correct texture, computing the wall slice, and drawing ceiling, wall,
** and floor pixels.
*/
void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	t_hit	hit;
	int		y;

	init_hit_ray(&hit, player, start_x, i);
	cast_ray(&hit, game, start_x);
	get_right_tex(&hit, game);
	get_tex_x(&hit);
	compute_wall_slice(&hit, player);
	y = 0;
	while (y < hit.top)
		put_pixel(i, y++, game->ceiling_color, game);
	draw_texture_line(&hit, game);
	y = hit.bottom;
	while (y < WIN_H)
		put_pixel(i, y++, game->floor_color, game);
}

/*
** Main rendering loop that updates player movement, clears the screen,
** casts rays for all screen columns, and displays the final frame.
*/
int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	move_player(player, game);
	clear_image(game);
	fraction = PI / 3 / WIN_W;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIN_W)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
