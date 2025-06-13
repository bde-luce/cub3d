/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:30:05 by bde-luce          #+#    #+#             */
/*   Updated: 2025/05/13 12:30:05 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	free_all(t_map *map)
{
	if (map->file)
		free_arr(map->file);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->f)
		free(map->f);
	if (map->c)
		free(map->c);
	if (map->map)
		free_arr(map->map);
}

void	error_exit(char *str, t_map *map)
{
	printf("Error\n%s\n", str);
	free_all(map);
	exit(1);
}

void	check_file_type(char *file_name, t_map *map)
{
	char	*str;

	str = ft_substr(file_name, ft_strlen(file_name) - 4, 4);
	if (ft_strncmp(str, ".cub", 4) == 0)
	{
		free(str);
		return ;
	}
	free(str);
	error_exit("Wrong type of file (!= .cub)", map);
}
int	nbr_lines(char *file, t_map *map)
{
	int		fd;
	int		nbr_lines;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Error opening file", map);
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

void	file_convert(t_map *map, char **argv)
{
	int		fd;
	int		i;
	char	*line;

	check_file_type(argv[1], map);
	map->file = malloc(sizeof(char *) * (nbr_lines(argv[1], map) + 1));
	if (!map->file)
		error_exit("Problem in memory allocation", map);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_exit("Error opening map file", map);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map->file[i++] = line;
		line = get_next_line(fd);
	}
	map->file[i] = NULL;
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
void	check_info_color(char *info, t_map *map)
{
	char	**rgb;
	int		i;

	rgb = ft_split(info, ',');
	if (!rgb)
		error_exit("Wrong rgb color code", map);
	if (arr_len(rgb) != 3)
		error_exit("Wrong rgb color code", map);
	i = 0;
	while (i < 3)
	{
		if (rgb[i] && (!str_isdigit(rgb[i]) || (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)))
			error_exit("Wrong rgb color code", map);
		i++;
	}
	free_arr(rgb);
}

void	check_info(char *info, char *info_type, t_map *map)
{
	int	fd;

	if (ft_strncmp(info_type, "texture", 8) == 0)
	{
		printf("info_path: %s\n", info);
		fd = open(info, O_RDONLY);
		if (fd == -1)
		{
			free(info);
			error_exit("Invalid path of texture", map);
		}
		close(fd);
	}
	if (ft_strncmp(info_type, "color", 6) == 0)
		check_info_color(info, map);
}

int skip_whitespace(char *str, int *i)
{
	int count = 0;
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
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
	while (str[*i] && str[*i] != ' ' && (str[*i] < 9 || str[*i] > 13))
		(*i)++;
}


char *get_info(char *info_type, char *element, t_map *map)
{
	int i = 0;
	int start_index;
	int	trailing_spaces;
	char *info;

	skip_whitespace(element, &i);
	skip_id_prefix(info_type, &i);
	skip_whitespace(element, &i);
	start_index = i;
	skip_word(element, &i);
	trailing_spaces = skip_whitespace(element, &i);
	if (element[i] && element[i] != ' ' && (element[i] < 9 || element[i] > 13))
		error_exit("Invalid path of texture", map);
	info = ft_substr(element, start_index, ft_strlen(element) - start_index - trailing_spaces);
	check_info(info, info_type, map);
	return info;
}

int	check_elem_id(t_map *map, char *element)
{
	if (ft_strncmp(element, "NO ", 3) == 0)
		map->no = get_info("texture", element, map);
	else if (ft_strncmp(element, "SO ", 3) == 0)
		map->so = get_info("texture", element, map);
	else if (ft_strncmp(element, "WE ", 3) == 0)
		map->we = get_info("texture", element, map);
	else if (ft_strncmp(element, "EA ", 3) == 0)
		map->ea = get_info("texture", element, map);
	else if (ft_strncmp(element, "F ", 2) == 0)
		map->f = get_info("color", element, map);
	else if (ft_strncmp(element, "C ", 2) == 0)
		map->c = get_info("color", element, map);
	else if (ft_strncmp(element, "\r\n", 2) == 0)
		return (0);
	else
		error_exit("Wrong/missing element type", map);
	return (1);
} 

int	elem_is_unique(t_map *map, char *element)
{
	if (ft_strncmp(element, "NO ", 3) == 0 && map->no)
		error_exit("Repeated element NO", map);
	else if (ft_strncmp(element, "SO ", 3) == 0 && map->so)
		error_exit("Repeated element SO", map);
	else if (ft_strncmp(element, "WE ", 3) == 0 && map->we)
		error_exit("Repeated element WE", map);
	else if (ft_strncmp(element, "EA ", 3) == 0 && map->ea)
		error_exit("Repeated element EA", map);
	else if (ft_strncmp(element, "F ", 2) == 0 && map->f)
		error_exit("Repeated element F", map);
	else if (ft_strncmp(element, "C ", 2) == 0 && map->c)
		error_exit("Repeated element C", map);
	else
		return (1);
	return (0);
}

void	validate_elements(int *i, t_map *map)
{
	int	e;

	e = 0;
	while (e != 6)
	{
		if (elem_is_unique(map, map->file[*i]) && check_elem_id(map, map->file[*i]))
			e++;
		printf("e: %d\n", e);
		(*i)++;
	}
}

int	nbr_rows(int i, t_map *map)
{
	int	i_init;

	i_init = i;
	while (map->file[i] != NULL && ft_strncmp(map->file[i], "\r\n", 2) != 0)
		i++;
	return (i - i_init);
}

void	get_map(int i, t_map *map)
{
	int	j;

	j = 0;
	while (map->file[i] && ft_strncmp(map->file[i], "\r\n", 2) == 0)
		i++;
	if (!map->file[i])
		error_exit("No map found", map);
	printf("i_map: %d\n", i);
	map->rows = nbr_rows(i, map);
	printf("nbr_rows: %d\n", map->rows);
	map->map = malloc(sizeof(char *) * (map->rows + 1));
	if (!map->map)
		error_exit("Problem in memory allocation", map);
	while (map->file[i] != NULL && ft_strncmp(map->file[i], "\r\n", 2) != 0)
	{
		map->map[j] = ft_strtrim(map->file[i], "\r\n");								//rever se uso esta funcao ou crio uma especifica
		j++;
		i++;
	}
	map->map[j] = NULL;																
	while (map->file[i] != NULL && ft_strncmp(map->file[i], "\r\n", 2) == 0)		//check_map_is_last
		i++;
	if (map->file[i] != NULL)
		error_exit("Map has to be last content in the file", map);
}

void	print_file(t_map *map)
{
	int	i;

	i = 0;
	while (map->file[i] != NULL)
	{
		printf("[%d]: %s\n", i, map->file[i]);
		i++;
	}
}


void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i] != NULL)
	{
		printf("[%d]:	%s\n", i, map->map[i]);
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

void	check_char_is_valid(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (valid_char(map->map[i][j]) == 1)
				error_exit("Map Character(s) is(are) not valid", map);
			j++;
		}
		i++;
	}
}

void	check_only_1player(t_map *map)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (p > 1)
				error_exit("Only one player allowed", map);
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'W' || map->map[i][j] == 'E')
				p++;
			j++;
		}
		i++;
	}
	if (p == 0)
		error_exit("Invalid map", map);
}

int	is_player_or_zero(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	check_map_is_closed(t_map *map)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	// verificar primeira linha não tem 0
	while (map->map[0][j])
	{
		if (is_player_or_zero(map->map[0][j]))
			error_exit("Map is not closed", map);
		j++;
	}
	j = 0;
	// verificar ultima linha nao tem 0
	while (map->map[map->rows - 1][j])
	{
		if (is_player_or_zero(map->map[map->rows - 1][j]))
			error_exit("Map is not closed", map);
		j++;
	}
	i = 1;
	j = 0;
	// verificar linhas do meio
	while (i < map->rows - 1)
	{
		k = ft_strlen(map->map[i]) - 1;
		// verificar que não começa com 0
		while (map->map[i][j] == ' ')
			j++;
		if (is_player_or_zero(map->map[i][j]))
			error_exit("Map is not closed", map);
		// verificar que não acaba com 0
		while (map->map[i][k] == ' ')
			k--;
		if (is_player_or_zero(map->map[i][k]))
			error_exit("Map is not closed", map);
		//  verificar que não tem um 0 no meio sem fronteira
		while (map->map[i][j + 1])
		{
			while (map->map[i][j] == '1')
				j++;
			if (is_player_or_zero(map->map[i][j]) && (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' ' || map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' '))
				error_exit("Map is not closed", map);
			j++;
		}
		i++;
		j = 0;
	}
}

void	validate_map(t_map *map)												//o argumento deveria ser t_map * ou só t_map
{
	check_char_is_valid(map);
	check_only_1player(map);
	check_map_is_closed(map);
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

void	map_validate(t_map *map)
{
	int	i;

	i = 0;
	print_file(map);
	validate_elements(&i, map);
	printf("i: %d\n", i);
	get_map(i, map);
	print_map(map);
	validate_map(map);
}

void	init_map(t_map *map)
{
	map->file = NULL;
	map->map = NULL;
	map->rows = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f = NULL;
	map->c = NULL;
}

int	main(int argc, char **argv)
{
	t_map	map;
	if (argc == 2)
	{
		init_map(&map);
		file_convert(&map, argv);
		map_validate(&map);
		free_all(&map);
	}
}