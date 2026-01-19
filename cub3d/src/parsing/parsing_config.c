/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:04:43 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/14 15:04:43 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** Frees a NULL-terminated array of strings.
*/
void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

/*
** Frees all dynamically allocated fields inside the config structure.
*/
void	free_config(t_config *config)
{
	if (config->file)
		free_arr(config->file);
	if (config->no)
		free(config->no);
	if (config->so)
		free(config->so);
	if (config->we)
		free(config->we);
	if (config->ea)
		free(config->ea);
	if (config->f)
		free(config->f);
	if (config->c)
		free(config->c);
	if (config->map)
		free_arr(config->map);
}

/*
** Prints an error message, frees allocated resources, and exits the program.
*/
void	error_exit(char *str, t_config *config)
{
	printf("Error\n%s\n", str);
	free_config(config);
	exit(1);
}

void	init_config(t_config *config)
{
	config->file = NULL;
	config->map = NULL;
	config->rows = 0;
	config->no = NULL;
	config->so = NULL;
	config->we = NULL;
	config->ea = NULL;
	config->f = NULL;
	config->c = NULL;
}
