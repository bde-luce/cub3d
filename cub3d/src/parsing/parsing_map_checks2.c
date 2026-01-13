#include "../inc/cub3d.h"

void	check_1st_and_last_line(t_cub3d *cub3d)
{
	int	j;

	// verificar primeira linha não tem 0
	j = 0;
	while (cub3d->map[0][j])
	{
		if (is_player_or_zero(cub3d->map[0][j]))
			error_exit("Map is not closed", cub3d);
		j++;
	}
	// verificar ultima linha nao tem 0
	j = 0;
	while (cub3d->map[cub3d->rows - 1][j])
	{
		if (is_player_or_zero(cub3d->map[cub3d->rows - 1][j]))
			error_exit("Map is not closed", cub3d);
		j++;
	}
}

void	check_middle(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	k;
	int l;
	int	m;

	i = 1;
	while (i < cub3d->rows - 1)
	{
		j = 0;
		k = ft_strlen(cub3d->map[i]) - 1;
		l = ft_strlen(cub3d->map[i - 1]) - 1;
		m = ft_strlen(cub3d->map[i + 1]) - 1;
		while (cub3d->map[i][j] != '\0' && cub3d->map[i][j] != '\n')
		{
			while (cub3d->map[i][j] == '1')
				j++;
			if (is_player_or_zero(cub3d->map[i][j]))
			{
				// verificar se a posição com o valor 0 está para além do fim da linha anterior e da linha seguinte
				if (j == 0 || j == k || j > l || j > m)									
					error_exit("Map is not closed", cub3d);
				if (cub3d->map[i - 1][j] == ' ' || cub3d->map[i + 1][j] == ' ' || cub3d->map[i][j - 1] == ' ' || cub3d->map[i][j + 1] == ' ')
					error_exit("Map is not closed", cub3d);
				j++;
			}
			if (is_hws(cub3d->map[i][j]))
				j++;
		}
		i++;
	}
}

void	check_map_is_closed(t_cub3d *cub3d)
{
	check_1st_and_last_line(cub3d);
	check_middle(cub3d);
}

void	validate_map(t_cub3d *cub3d)
{
	check_char_is_valid(cub3d);
	check_only_1player(cub3d);
	check_map_is_closed(cub3d);
}
