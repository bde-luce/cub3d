#include "../inc/cub3d.h"

int	check_color_range(char *color)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	skip_hwhitespace(color, &i);
	skip_pos_signal(color, &i);
	while (color[i] && !is_hws(color[i]))
	{
		if (color[i] < '0' || color[i] > '9')
			return (0);
		c = c * 10 + color[i] - 48;
		i++;
	}
	skip_hwhitespace(color, &i);
	printf("c: %d\n", c);
	if (color[i] || c > 255)
		return (0);
	return (1);
}

int count_commas(char *s)
{
    int i = 0, c = 0;
    while (s[i])
        if (s[i++] == ',')
            c++;
    return c;
}

void	check_info_color(char *info, t_cub3d *cub3d)
{
	char	**rgb;
	int		i;

	if (count_commas(info) != 2)									//edge case rgb code like 200,,3,100
    {
		free(info);
		error_exit("Wrong rgb color code", cub3d);
	}
	rgb = ft_split(info, ',');
	if (!rgb)
	{
		free(info);
		error_exit("Wrong rgb color code", cub3d);
	}
	if (arr_len(rgb) != 3)
	{
		free_arr(rgb);
		free(info);
		error_exit("Wrong rgb color code", cub3d);
	}
	i = 0;
	while (i < 3)
	{
		if (!check_color_range(rgb[i]))
		{
			free_arr(rgb);
			free(info);
			error_exit("Wrong rgb color code", cub3d);
		}
		i++;
	}
	free_arr(rgb);
}
