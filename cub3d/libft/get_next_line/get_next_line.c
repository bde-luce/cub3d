/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:12:25 by bde-luce          #+#    #+#             */
/*   Updated: 2024/09/24 15:03:22 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_buf(int fd, char *rest)
{
	char	*buf;
	int		bytes_rd;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	bytes_rd = 1;
	buf[0] = '\0';
	while (!check_nl(buf) && bytes_rd != 0)
	{
		bytes_rd = read(fd, buf, BUFFER_SIZE);
		if (bytes_rd == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[bytes_rd] = '\0';
		rest = join_buf(rest, buf);
	}
	free(buf);
	return (rest);
}

static char	*get_line(char *rest)
{
	int		i;
	int		b;
	char	*line;

	i = 0;
	if (!rest[i])
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	b = 1;
	if (rest[i] == '\n')
		b = 2;
	line = malloc(sizeof(char) * (i + b));
	if (!line)
		return (NULL);
	copy_line(line, rest);
	return (line);
}

static char	*get_rest(char *rest)
{
	int		j;
	char	*new_rest;

	j = 0;
	while (rest[j] && rest[j] != '\n')
		j++;
	if (rest[j] == '\n')
		j++;
	new_rest = malloc(sizeof(char) * (str_len(rest) - j + 1));
	if (!new_rest)
		return (NULL);
	copy_rest(new_rest, rest, j);
	free(rest);
	if (new_rest[0] == '\0')
	{
		free(new_rest);
		return (NULL);
	}
	return (new_rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = get_buf(fd, rest);
	if (!rest)
		return (NULL);
	line = get_line(rest);
	rest = get_rest(rest);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*str;

	fd = open("text.txt", O_RDONLY);
	//fd = 42;
	while ((str = get_next_line(fd)))
	{
		printf("%s", str);
		free(str);
	}
}*/