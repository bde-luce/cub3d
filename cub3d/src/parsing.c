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

void	error_exit(char *str, t_cub3d *cub3d)
{
	printf("Error\n%s\n", str);
	free_all(cub3d);
	exit(1);
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

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_hws(char c)
{
	return (c == 32 || c == 9 );
}

int	is_ws(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int skip_hwhitespace(char *str, int *i);

void	skip_pos_signal(char *str, int *i)
{
	if (str[*i] == '+')
		(*i)++;
}

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
    	error_exit("Wrong rgb color code", cub3d);
	rgb = ft_split(info, ',');
	if (!rgb)
		error_exit("Wrong rgb color code", cub3d);
	if (arr_len(rgb) != 3)
	{
		free_arr(rgb);
		error_exit("Wrong rgb color code", cub3d);
	}
	i = 0;
	while (i < 3)
	{
		if (!check_color_range(rgb[i]))
		{
			free_arr(rgb);
			error_exit("Wrong rgb color code", cub3d);
		}
		i++;
	}
	free_arr(rgb);
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

int skip_hwhitespace(char *str, int *i)
{
	int count = 0;
	while (is_hws(str[*i]))
	{
		(*i)++;
		count++;
	}
	return count;
}

void skip_id_prefix(char *info_type, int *i)
{
	if (ft_strncmp(info_type, "texture", 8) == 0)
		*i += 2;
	else if (ft_strncmp(info_type, "color", 6) == 0)
		*i += 1;
}

void skip_word(char *str, int *i)
{
	while (str[*i] && str[*i] != 32 && (str[*i] < 9 || str[*i] > 13))
		(*i)++;
}

int	count_trailing_ws(char *str)
{
	int	i;
	int	c;

	i = ft_strlen(str) - 1;
	c = 0;
	while (i > 0 && is_ws(str[i]))
	{
		c++;
		i--;
	}
	return (c);
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

void	validate_map(t_cub3d *cub3d)												//o argumento deveria ser t_map * ou só t_map
{
	check_char_is_valid(cub3d);
	check_only_1player(cub3d);
	check_map_is_closed(cub3d);
}

//validação da info de cor para o chao e para o teto ✅
//acrescentar verificação de se a info dos elements é válida e nao apenas os ids ✅
//verificar que não ha info para alem do id e da texture do element ✅
//validação de que o mapa existe e o file não acaba a seguir aos elements ✅
//validação que não há mais info a seguir ao map ✅
//validar no mapa:
//- se os caracteres são válidos ✅
//- se há apenas 1 player ✅
//- se o mapa é fechado
		// - falta por o raciocinio do 0 não poder estar na fronteira do mapa no player✅
				// - maybe criar funcao que verifica se o map[i][j] é um char de player e se for fazer apenas uma verificação para player e nao para as 4 letras possiveis
				// - ou até fazer verificação de que é player ou 0✅

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
