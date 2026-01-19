/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:43:52 by frteixei          #+#    #+#             */
/*   Updated: 2026/01/19 17:18:34 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_move_vector(t_player *p, float *dx, float *dy)
{
	float	speed;
	float	cos_a;
	float	sin_a;
	int		fwd;
	int		side;

	speed = 5;
	cos_a = cos(p->angle);
	sin_a = sin(p->angle);
	fwd = p->key_up - p->key_down;
	side = p->key_left - p->key_right;
	*dx = (cos_a * fwd + sin_a * side) * speed;
	*dy = (sin_a * fwd - cos_a * side) * speed;
}

void	apply_move(t_player *p, t_game *game, float dx, float dy)
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

static double	get_player_angle(char c)
{
	if (c == 'N')
		return (3 * PI / 2);
	if (c == 'S')
		return (PI / 2);
	if (c == 'E')
		return (0);
	return (PI);
}

void	find_player_position(t_config *config)
{
	int	i;
	int	j;

	i = 0;
	while (config->map[i])
	{
		j = 0;
		while (config->map[i][j])
		{
			if (ft_strchr("NSEW", config->map[i][j]))
			{
				config->game.player.x = j * BLOCK + BLOCK / 2;
				config->game.player.y = i * BLOCK + BLOCK / 2;
				config->game.player.angle = get_player_angle(config->map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}
