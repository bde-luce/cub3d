/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:35:54 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/22 19:35:54 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	touch(float x, float y, const t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_x < 0)
		return (true);
	if (!game->map[map_y] || !game->map[map_y][map_x])
		return (true);
	if (game->map[map_y][map_x] == '1')
		return (true);
	return (false);
}

// verificar se touch precisa mesmo destes checks todos
