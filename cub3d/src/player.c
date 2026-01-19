/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:53:03 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/19 16:43:52 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_player *p, float x2, float y2)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - p->x;
	delta_y = y2 - p->y;
	angle = atan2(delta_y, delta_x) - p->angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

static void	rotate_player(t_player *p)
{
	float	angle_speed;

	angle_speed = 0.04;
	if (p->left_rotate)
		p->angle -= angle_speed;
	if (p->right_rotate)
		p->angle += angle_speed;
	if (p->angle > 2 * PI)
		p->angle = 0;
	if (p->angle < 0)
		p->angle = 2 * PI;
}

void	move_player(t_player *player, t_game *game)
{
	float	dx;
	float	dy;

	rotate_player(player);
	get_move_vector(player, &dx, &dy);
	apply_move(player, game, dx, dy);
}
