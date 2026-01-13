#include "../inc/cub3d.h"

void	error_exit(char *str, t_cub3d *cub3d)
{
	printf("Error\n%s\n", str);
	free_all(cub3d);
	exit(1);
}

void	map_validate(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	print_file(cub3d);
	validate_elements(&i, cub3d);
	printf("i: %d\n", i);
	get_map(i, cub3d);
	print_map(cub3d);
	validate_map(cub3d);
}
