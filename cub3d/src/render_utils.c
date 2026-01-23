/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:28:22 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/23 16:08:15 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** Selects the correct wall texture based on ray side and direction.
*/
void	get_right_tex(t_ray *ray, const t_game *game)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->tex = &game->ea;
		else
			ray->tex = &game->we;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->tex = &game->so;
		else
			ray->tex = &game->no;
	}
}

/*
** Computes the horizontal texture coordinate for the wall hit.
*/
void	get_tex_x(t_ray *ray, const t_player *player)
{
	float	wall_x;

	if (ray->side == 0)
		wall_x = player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = player->x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * ray->tex->width);
	if (ray->tex_x < 0)
		ray->tex_x = 0;
	if (ray->tex_x >= ray->tex->width)
		ray->tex_x = ray->tex->width - 1;
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = ray->tex->width - 1 - ray->tex_x;
}
