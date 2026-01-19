/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:08:14 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/14 15:08:14 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** Runs all map-related validations.
*/
static void	check_map(t_config *config)
{
	validate_map_content(config);
	check_map_is_closed(config);
}

/*
** Full parsing pipeline: elements → map → validations.
*/
void	map_validate(t_config *config)
{
	int	i;

	i = 0;
	validate_elements(&i, config);
	get_map(i, config);
	check_map(config);
}
