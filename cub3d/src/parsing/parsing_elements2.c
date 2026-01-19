/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:20:10 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/14 15:20:10 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** Checks whether all 6 required elements are present.
*/
static int	has_6_elements(t_config *config)
{
	return (config->no && config->so && config->we
		&& config->ea && config->f && config->c);
}

/*
** Handles parsing of EA, F and C elements.
*/
static void	check_elem_id_2(t_config *config, char *elem)
{
	int	i;

	i = 0;
	skip_hwhitespace(elem, &i);
	if (elem[i] == 'E' && elem[i + 1] == 'A' && is_hws(elem[i + 2]))
	{
		if (config->ea)
			error_exit("Repeated element EA", config);
		config->ea = get_info(i + 2, "texture", elem, config);
	}
	else if (elem[i] == 'F' && is_hws(elem[i + 1]))
	{
		if (config->f)
			error_exit("Repeated element F", config);
		config->f = get_info(i + 1, "color", elem, config);
	}
	else if (elem[i] == 'C' && is_hws(elem[i + 1]))
	{
		if (config->c)
			error_exit("Repeated element C", config);
		config->c = get_info(i + 1, "color", elem, config);
	}
	else if (elem[i] != '\n' && elem[i] != '\r' && elem[i] != '\0')
		error_exit("Invalid file structure", config);
}

/*
** Identifies and parses a single element line (NO, SO, WE, EA, F, C).
*/
static void	check_elem_id(t_config *config, char *elem)
{
	int	i;

	i = 0;
	skip_hwhitespace(elem, &i);
	if (elem[i] == 'N' && elem[i + 1] == 'O' && is_hws(elem[i + 2]))
	{
		if (config->no)
			error_exit("Repeated element NO", config);
		config->no = get_info(i + 2, "texture", elem, config);
	}
	else if (elem[i] == 'S' && elem[i + 1] == 'O' && is_hws(elem[i + 2]))
	{
		if (config->so)
			error_exit("Repeated element SO", config);
		config->so = get_info(i + 2, "texture", elem, config);
	}
	else if (elem[i] == 'W' && elem[i + 1] == 'E' && is_hws(elem[i + 2]))
	{
		if (config->we)
			error_exit("Repeated element WE", config);
		config->we = get_info(i + 2, "texture", elem, config);
	}
	else
		check_elem_id_2(config, elem);
}

/*
** Parses and validates all required elements before the map.
*/
void	validate_elements(int *i, t_config *config)
{
	while (!has_6_elements(config))
	{
		if (!config->file[*i])
			error_exit("Missing elements", config);
		check_elem_id(config, config->file[*i]);
		(*i)++;
	}
}
