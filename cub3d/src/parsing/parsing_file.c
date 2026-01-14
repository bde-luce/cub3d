/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:05:24 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/14 15:05:24 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_file_type(char *file_name, t_config *config)
{
	int	len;

	len = ft_strlen(file_name);
	if (len < 4 || ft_strncmp(file_name + len - 4, ".cub", 4) != 0)
		error_exit("Wrong type of file (!= .cub)", config);
}

static int	nbr_lines(char *file, t_config *config)
{
	int		fd;
	int		nbr_lines;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Error opening file", config);
	nbr_lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		nbr_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nbr_lines);
}

void	file_convert(t_config *config, char **argv)
{
	int		fd;
	int		i;
	char	*line;

	check_file_type(argv[1], config);
	config->file = malloc(sizeof(char *) * (nbr_lines(argv[1], config) + 1));
	if (!config->file)
		error_exit("Problem in memory allocation", config);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_exit("Error opening file", config);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		config->file[i++] = line;
		line = get_next_line(fd);
	}
	config->file[i] = NULL;
	close(fd);
}
