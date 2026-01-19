/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mapcheck.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:11:17 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/14 15:11:17 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** Extracts the map from the file and ensures it is the last content.
*/
static int	is_player_or_zero(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

/*
** Validates that a map cell is properly enclosed by walls
*/
static void	check_cell(int i, int j, t_config *config)
{
	int	k;
	int	l;
	int	m;

	k = ft_strlen(config->map[i]) - 1;
	l = ft_strlen(config->map[i - 1]) - 1;
	m = ft_strlen(config->map[i + 1]) - 1;
	if (j == 0 || j == k || j > l || j > m)
		error_exit("Map is not closed", config);
	if (config->map[i - 1][j] == ' ' || config->map[i + 1][j] == ' '
			|| config->map[i][j - 1] == ' ' || config->map[i][j + 1] == ' ')
		error_exit("Map is not closed", config);
}

/*
** Checks the middle rows of the map for proper wall enclosure.
*/
static void	check_middle(t_config *config)
{
	int	i;
	int	j;

	i = 1;
	while (i < config->rows - 1)
	{
		j = 0;
		while (config->map[i][j] != '\0')
		{
			while (config->map[i][j] == '1' || is_hws(config->map[i][j]))
				j++;
			if (is_player_or_zero(config->map[i][j]))
				check_cell(i, j++, config);
			else if (config->map[i][j] != '\0')
				j++;
		}
		i++;
	}
}

/*
** Ensures that the first and last rows of the map contain no walkable cells
** or player positions, ensuring therefore the map is closed
*/
static void	check_1st_and_last_line(t_config *config)
{
	int	j;

	j = 0;
	while (config->map[0][j])
	{
		if (is_player_or_zero(config->map[0][j]))
			error_exit("Map is not closed", config);
		j++;
	}
	j = 0;
	while (config->map[config->rows - 1][j])
	{
		if (is_player_or_zero(config->map[config->rows - 1][j]))
			error_exit("Map is not closed", config);
		j++;
	}
}

/*
** Validates that the map is fully enclosed by walls.
*/
void	check_map_is_closed(t_config *config)
{
	check_1st_and_last_line(config);
	check_middle(config);
}
