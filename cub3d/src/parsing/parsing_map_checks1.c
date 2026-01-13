#include "../inc/cub3d.h"

static int	valid_char(char c)
{
	if (c != '0')
	{
		if (c != '1')
		{
			if (c != 'N')
			{
				if (c != 'S')
				{
					if (c != 'E')
					{
						if (c != 'W')
						{
							if (c != ' ')
								return (1);
						}
					}
				}
			}
		}
	}
	return (0);
}

void	check_char_is_valid(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (cub3d->map[i])
	{
		j = 0;
		while (cub3d->map[i][j])
		{
			if (valid_char(cub3d->map[i][j]) == 1)
				error_exit("Map Character(s) is(are) not valid", cub3d);
			j++;
		}
		i++;
	}
}

void	check_only_1player(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (cub3d->map[i])
	{
		j = 0;
		while (cub3d->map[i][j])
		{
			if (p > 1)
				error_exit("Only one player allowed", cub3d);
			if (cub3d->map[i][j] == 'N' || cub3d->map[i][j] == 'S' || cub3d->map[i][j] == 'W' || cub3d->map[i][j] == 'E')
				p++;
			j++;
		}
		i++;
	}
	if (p == 0)
		error_exit("Invalid map", cub3d);
}

int	is_player_or_zero(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}
