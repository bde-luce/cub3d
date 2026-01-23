/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:27:47 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/23 15:54:14 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** Performs the DDA algorithm to find the wall hit by the ray.
*/
static void	perform_dda(t_ray *ray, char **map)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			ray->hit = true;
	}
}

/*
** Computes the perpendicular distance from the player to the wall hit.
*/
static void	get_perp_wall_dist(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->perp_wall_dist
			= (ray->map_x - player->x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist
			= (ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

/*
** Casts rays for each screen column and renders the scene.
*/
int	ray_cast(t_config *config)
{
	t_ray	ray;
	float	x;

	move_player(&config->game.player, &config->game);
	clear_image(&config->game);
	x = 0;
	while (x < WIN_W)
	{
		ft_bzero(&ray, sizeof(t_ray));
		get_ray_direction(&ray, &config->game.player, x);
		get_ray_grid(&ray, &config->game.player);
		get_ray_step(&ray, &config->game.player);
		perform_dda(&ray, config->map);
		get_perp_wall_dist(&ray, &config->game.player);
		draw_column(x, &ray, &config->game);
		x++;
	}
	mlx_put_image_to_window(config->game.mlx, config->game.win,
		config->game.img, 0, 0);
	return (0);
}
