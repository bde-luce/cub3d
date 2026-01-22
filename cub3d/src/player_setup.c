/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:21:09 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/22 19:21:11 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	get_player_dir(t_player *player, char dir)
{
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	if (dir == 'N')
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
}

static void	get_player_angle(t_player *player, char dir)
{
	if (dir == 'N')
		player->angle = 3 * PI / 2;
	else if (dir == 'S')
		player->angle = PI / 2;
	else if (dir == 'E')
		player->angle = 0;
	else
		player->angle = PI;
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
				config->game.player.x = j + 0.5;
				config->game.player.y = i + 0.5;
				get_player_dir(&config->game.player, config->map[i][j]);
				get_player_angle(&config->game.player, config->map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}
