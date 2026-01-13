#include "../inc/cub3d.h"

void skip_id_prefix(char *info_type, int *i)
{
	if (ft_strncmp(info_type, "texture", 8) == 0)
		*i += 2;
	else if (ft_strncmp(info_type, "color", 6) == 0)
		*i += 1;
}

char *get_info(char *info_type, char *element, t_cub3d *cub3d)
{
	int i;
	int start_index;
	int	trailing_ws;
	char *info;

	i = 0;
	skip_hwhitespace(element, &i);
	skip_id_prefix(info_type, &i);
	skip_hwhitespace(element, &i);
	start_index = i;
	trailing_ws = count_trailing_ws(element);
	info = ft_substr(element, start_index, ft_strlen(element) - start_index - trailing_ws);
	check_info(info, info_type, cub3d);
	return info;
}

int	check_elem_id(t_cub3d *cub3d, char *element)
{
	int	i;

	i = 0;
	skip_hwhitespace(element, &i);
	if (element[i] == 'N' && element[i + 1] == 'O' && is_hws(element[i + 2]))
	{
		if (cub3d->no)
			error_exit("Repeated element NO", cub3d);
		cub3d->no = get_info("texture", element, cub3d);
	}
	else if (element[i] == 'S' && element[i + 1] == 'O' && is_hws(element[i + 2]))
	{
		if (cub3d->so)
			error_exit("Repeated element SO", cub3d);
		cub3d->so = get_info("texture", element, cub3d);
	}
	else if (element[i] == 'W' && element[i + 1] == 'E' && is_hws(element[i + 2]))
	{
		if (cub3d->we)
			error_exit("Repeated element WE", cub3d);
		cub3d->we = get_info("texture", element, cub3d);
	}
	else if (element[i] == 'E' && element[i + 1] == 'A' && is_hws(element[i + 2]))
	{
		if (cub3d->ea)
			error_exit("Repeated element EA", cub3d);
		cub3d->ea = get_info("texture", element, cub3d);
	}
	else if (element[i] == 'F' && is_hws(element[i + 1]))
	{
		if (cub3d->f)
			error_exit("Repeated element F", cub3d);
		cub3d->f = get_info("color", element, cub3d);
	}
	else if (element[i] == 'C' && is_hws(element[i + 1]))
	{
		if (cub3d->c)
			error_exit("Repeated element C", cub3d);
		cub3d->c = get_info("color", element, cub3d);
	}
	else if (element[i] == '\n')
		return (0);
	else
		error_exit("Wrong/missing element type", cub3d);
	return (1);
}

void	validate_elements(int *i, t_cub3d *cub3d)
{
	int	e;

	e = 0;
	while (e != 6)
	{
		if (!cub3d->file[*i])
			error_exit("Missing elements", cub3d);
		if (check_elem_id(cub3d, cub3d->file[*i]))
			e++;
		printf("e: %d\n", e);
		(*i)++;
	}
}

void	check_info(char *info, char *info_type, t_cub3d *cub3d)
{
	int	fd;

	if (ft_strncmp(info_type, "texture", 8) == 0)
	{
		fd = open(info, O_RDONLY);
		if (fd == -1)
		{
			free(info);
			error_exit("Invalid path of texture", cub3d);
		}
		close(fd);
	}
	if (ft_strncmp(info_type, "color", 6) == 0)
		check_info_color(info, cub3d);
	printf("info_path: %s\n", info);
}
