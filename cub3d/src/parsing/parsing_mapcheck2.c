/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mapcheck2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:24:28 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/14 15:24:28 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == '	');
}

void	check_only_1player(t_config *config)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (config->map[i])
	{
		j = 0;
		while (config->map[i][j])
		{
			if (!is_valid_map_char(config->map[i][j]))
				error_exit("Map Character(s) is(are) not valid", config);
			if (config->map[i][j] == 'N' || config->map[i][j] == 'S'
					|| config->map[i][j] == 'W' || config->map[i][j] == 'E')
				p++;
			if (p > 1)
				error_exit("Only one player allowed", config);
			j++;
		}
		i++;
	}
	if (p == 0)
		error_exit("Missing player", config);
}
