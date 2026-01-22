/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:14:39 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/22 19:22:23 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

static void	update_player_vectors(t_player *p)
{
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
	p->plane_x = -p->dir_y * 0.66;
	p->plane_y = p->dir_x * 0.66;
}

static void	get_move_vector(t_player *p, float *dx, float *dy)
{
	float	speed;
	int		fwd;
	int		side;

	speed = 0.05;
	fwd = p->key_up - p->key_down;
	side = p->key_left - p->key_right;
	*dx = (p->dir_x * fwd - p->plane_x * side) * speed;
	*dy = (p->dir_y * fwd - p->plane_y * side) * speed;
}

static void	apply_move(t_player *p, t_game *game, float dx, float dy)
{
	float	new_x;
	float	new_y;

	new_x = p->x + dx;
	new_y = p->y + dy;
	if (!touch(new_x, p->y, game))
		p->x = new_x;
	if (!touch(p->x, new_y, game))
		p->y = new_y;
}

void	move_player(t_player *player, t_game *game)
{
	float	dx;
	float	dy;

	rotate_player(player);
	update_player_vectors(player);
	get_move_vector(player, &dx, &dy);
	apply_move(player, game, dx, dy);
}
