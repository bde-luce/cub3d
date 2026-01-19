/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:00:00 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/19 17:10:13 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** Determines whether the ray hit a vertical (0) or horizontal wall (1)
** by comparing the grid cell crossed between the previous
** and current ray positions.
*/
int	get_side(float prev_x, float prev_y, float ray_x, float ray_y)
{
	int	prev_cell_x;
	int	prev_cell_y;
	int	cell_x;
	int	cell_y;

	prev_cell_x = (int)(prev_x / BLOCK);
	prev_cell_y = (int)(prev_y / BLOCK);
	cell_x = (int)(ray_x / BLOCK);
	cell_y = (int)(ray_y / BLOCK);
	if (prev_cell_x != cell_x)
		return (0);
	else if (prev_cell_y != cell_y)
		return (1);
	return (-1);
}

/*
** Selects the correct wall texture (NO, SO, WE, EA) based on the wall side
** hit and the ray direction.
*/
void	get_right_tex(t_hit *hit, t_game *game)
{
	if (hit->side == 0)
	{
		if (hit->dir_x > 0)
			hit->tex = &game->ea;
		else
			hit->tex = &game->we;
	}
	else
	{
		if (hit->dir_y > 0)
			hit->tex = &game->so;
		else
			hit->tex = &game->no;
	}
}

/*
** Computes the horizontal texture coordinate (tex_x) corresponding to the
** wall hit position, adjusting for wall orientation and ray direction.
*/
void	get_tex_x(t_hit *hit)
{
	float	wall_x;

	if (hit->side == 0)
		wall_x = fmodf(hit->ray_y, BLOCK) / BLOCK;
	else
		wall_x = fmodf(hit->ray_x, BLOCK) / BLOCK;
	if (wall_x < 0)
		wall_x += 1.0f;
	hit->tex_x = (int)(wall_x * (hit->tex->width - 1));
	if (hit->tex_x < 0)
		hit->tex_x = 0;
	if (hit->tex_x >= hit->tex->width)
		hit->tex_x = hit->tex->width - 1;
	if ((hit->side == 0 && hit->dir_x < 0) || (hit->side == 1
			&& hit->dir_y > 0))
		hit->tex_x = hit->tex->width - 1 - hit->tex_x;
}

/*
** Initializes the ray parameters for a single screen column.
*/
void	init_hit_ray(t_hit *hit, t_player *player, float angle, int screen_x)
{
	hit->ray_x = player->x;
	hit->ray_y = player->y;
	hit->dir_x = cos(angle);
	hit->dir_y = sin(angle);
	hit->screen_x = screen_x;
}
