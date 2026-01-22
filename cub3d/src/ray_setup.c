/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:23:08 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/22 19:50:27 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_ray_direction(t_ray *ray, const t_player *player, float x)
{
	float	camera_x;

	camera_x = (2.0f * (x / WIN_W)) - 1.0f;
	ray->ray_dir_x = player->dir_x + player->plane_x * camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * camera_x;
}

void	get_ray_grid(t_ray *ray, const t_player *player)
{
	ray->map_x = (int)(player->x);
	ray->map_y = (int)(player->y);
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = DDA_INF_DIST;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = DDA_INF_DIST;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	get_ray_step(t_ray *ray, const t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}
