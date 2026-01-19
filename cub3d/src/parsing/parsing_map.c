/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:07:25 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/14 15:07:25 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** Checks whether a line contains only whitespace or line breaks.
*/
static int	line_is_empty(char *str)
{
	int	i;

	i = 0;
	skip_hwhitespace(str, &i);
	if (str[i] == '\n' || str[i] == '\r' || str[i] == '\0')
		return (1);
	return (0);
}

/*
** Counts the number of map rows starting at a given index.
*/
static int	nbr_rows(int i, t_config *config)
{
	int	i_init;

	i_init = i;
	while (config->file[i] != NULL && !line_is_empty(config->file[i]))
		i++;
	return (i - i_init);
}

/*
** Extracts the map from the file and ensures it is the last content.
*/
void	get_map(int i, t_config *config)
{
	int	j;

	j = 0;
	while (config->file[i] && line_is_empty(config->file[i]))
		i++;
	if (!config->file[i])
		error_exit("No map found", config);
	config->rows = nbr_rows(i, config);
	config->map = malloc(sizeof(char *) * (config->rows + 1));
	if (!config->map)
		error_exit("Problem in memory allocation", config);
	while (config->file[i] != NULL && !line_is_empty(config->file[i]))
	{
		config->map[j] = ft_strtrim(config->file[i], "\n\r");
		j++;
		i++;
	}
	config->map[j] = NULL;
	while (config->file[i] != NULL && line_is_empty(config->file[i]))
		i++;
	if (config->file[i] != NULL)
		error_exit("Map has to be last content in the file", config);
}
