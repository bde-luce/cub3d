/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:05:01 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/14 15:05:01 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	count_commas(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i++] == ',')
			c++;
	}
	return (c);
}

static int	check_color_range(char *color)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	skip_hwhitespace(color, &i);
	skip_pos_signal(color, &i);
	if (!ft_isdigit(color[i]))
		return (0);
	while (color[i] && !is_hws(color[i]))
	{
		if (color[i] < '0' || color[i] > '9')
			return (0);
		c = c * 10 + color[i] - 48;
		i++;
	}
	skip_hwhitespace(color, &i);
	if (color[i] || c > 255)
		return (0);
	return (1);
}

// int rgb_to_int(char *rgb)
// {
//     char **c;
//     int r, g, b;
//     int color;

//     c = ft_split(rgb, ',');
//     if (!c)
//         return (-1);

//     r = ft_atoi(c[0]);
//     g = ft_atoi(c[1]);
//     b = ft_atoi(c[2]);

//     free_arr(c);

//     color = (r << 16) | (g << 8) | b;
//     return (color);
// }

static void	check_info_color(char *info, t_config *config)
{
	char	**rgb;
	int		i;

	if (count_commas(info) != 2)
		error_exit("Wrong rgb color code", config);
	rgb = ft_split(info, ',');
	if (!rgb)
		error_exit("Wrong rgb color code", config);
	if (arr_len(rgb) != 3)
	{
		free_arr(rgb);
		error_exit("Wrong rgb color code", config);
	}
	i = 0;
	while (i < 3)
	{
		if (!check_color_range(rgb[i]))
		{
			free_arr(rgb);
			error_exit("Wrong rgb color code", config);
		}
		i++;
	}
	free_arr(rgb);
}

static void	check_info(char *info, char *info_type, t_config *config)
{
	int	fd;

	if (ft_strncmp(info_type, "texture", 8) == 0)
	{
		fd = open(info, O_RDONLY);
		if (fd == -1)
		{
			free(info);
			error_exit("Invalid path of texture", config);
		}
		close(fd);
	}
	if (ft_strncmp(info_type, "color", 6) == 0)
		check_info_color(info, config);
}

char	*get_info(int i, char *info_type, char *elem, t_config *config)
{
	int		start_i;
	int		trailing_ws;
	char	*info;

	skip_hwhitespace(elem, &i);
	start_i = i;
	trailing_ws = count_trailing_ws(elem);
	info = ft_substr(elem, start_i, ft_strlen(elem) - start_i - trailing_ws);
	check_info(info, info_type, config);
	return (info);
}
