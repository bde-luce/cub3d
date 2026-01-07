/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:14:08 by bde-luce          #+#    #+#             */
/*   Updated: 2024/09/13 18:19:09 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_nl(char *buf)
{
	int	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	str_len(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*join_buf(char *rest, char *buf)
{
	char		*str;
	size_t		i;
	size_t		j;

	if (!rest)
	{
		rest = malloc(sizeof(char) * 1);
		if (!rest)
			return (NULL);
		rest[0] = '\0';
	}
	if (!buf)
		return (NULL);
	str = malloc(sizeof(char) * (str_len(rest) + str_len(buf) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (rest[++i])
		str[i] = rest[i];
	j = 0;
	while (buf[j])
		str[i++] = buf[j++];
	str[i] = '\0';
	free(rest);
	return (str);
}

void	copy_line(char *str_copy, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		str_copy[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		str_copy[i++] = '\n';
	str_copy[i] = '\0';
}

void	copy_rest(char *str_copy, char *str, int j)
{
	int	i;

	i = 0;
	while (str[j])
		str_copy[i++] = str[j++];
	str_copy[i] = '\0';
}
