#include "../inc/cub3d.h"

int	line_is_empty(char *str)
{
	int	i;

	i = 0;
	skip_hwhitespace(str, &i);
	if (str[i] == '\n')
		return (1);
	return (0);
}

int	nbr_rows(int i, t_cub3d *cub3d)
{
	int	i_init;

	i_init = i;
	while (cub3d->file[i] != NULL && !line_is_empty(cub3d->file[i]))
		i++;
	return (i - i_init);
}

void	get_map(int i, t_cub3d *cub3d)
{
	int	j;

	j = 0;
	while (cub3d->file[i] && line_is_empty(cub3d->file[i]))
		i++;
	if (!cub3d->file[i])
		error_exit("No map found", cub3d);
	printf("i_map: %d\n", i);
	cub3d->rows = nbr_rows(i, cub3d);
	printf("nbr_rows: %d\n", cub3d->rows);
	cub3d->map = malloc(sizeof(char *) * (cub3d->rows + 1));
	if (!cub3d->map)
		error_exit("Problem in memory allocation", cub3d);
	while (cub3d->file[i] != NULL && !line_is_empty(cub3d->file[i]))
	{
		cub3d->map[j] = ft_strtrim(cub3d->file[i], "\n");								//rever se uso esta funcao ou crio uma especifica
		j++;
		i++;
	}
	cub3d->map[j] = NULL;																
	while (cub3d->file[i] != NULL && line_is_empty(cub3d->file[i]))		//check_map_is_last
		i++;
	if (cub3d->file[i] != NULL)
		error_exit("Map has to be last content in the file", cub3d);
}

void	print_map(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (cub3d->map[i] != NULL)
	{
		printf("[%d]:	%s\n", i, cub3d->map[i]);
		i++;
	}
}
