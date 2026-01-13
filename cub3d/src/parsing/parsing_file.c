/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:30:05 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/07 17:00:35 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_all(t_cub3d *cub3d)
{
	if (cub3d->file)
		free_arr(cub3d->file);
	if (cub3d->no)
		free(cub3d->no);
	if (cub3d->so)
		free(cub3d->so);
	if (cub3d->we)
		free(cub3d->we);
	if (cub3d->ea)
		free(cub3d->ea);
	if (cub3d->f)
		free(cub3d->f);
	if (cub3d->c)
		free(cub3d->c);
	if (cub3d->map)
		free_arr(cub3d->map);
}

void	check_file_type(char *file_name, t_cub3d *cub3d)
{
	int	len;

	len = ft_strlen(file_name);
	if (len < 4 || ft_strncmp(file_name + len - 4, ".cub", 4) != 0)
		error_exit("Wrong type of file (!= .cub)", cub3d);
}

int	nbr_lines(char *file, t_cub3d *cub3d)
{
	int		fd;
	int		nbr_lines;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Error opening file", cub3d);
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

void	file_convert(t_cub3d *cub3d, char **argv)
{
	int		fd;
	int		i;
	char	*line;

	check_file_type(argv[1], cub3d);
	cub3d->file = malloc(sizeof(char *) * (nbr_lines(argv[1], cub3d) + 1));
	if (!cub3d->file)
		error_exit("Problem in memory allocation", cub3d);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_exit("Error opening map file", cub3d);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		cub3d->file[i++] = line;
		line = get_next_line(fd);
	}
	cub3d->file[i] = NULL;
	close(fd);
}

void	print_file(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (cub3d->file[i] != NULL)
	{
		printf("[%d]: %s\n", i, cub3d->file[i]);
		i++;
	}
}
