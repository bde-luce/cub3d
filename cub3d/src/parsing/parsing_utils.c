/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:34:10 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/19 16:37:00 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** Checks if a character is a horizontal whitespace (space or tab).
*/
int	is_hws(char c)
{
	return (c == 32 || c == 9);
}

/*
** Returns the length of a NULL-terminated string array.
*/
int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

/*
** Skips an optional '+' sign in a numeric string.
*/
void	skip_pos_signal(char *str, int *i)
{
	if (str[*i] == '+')
		(*i)++;
}

/*
** Skips horizontal whitespace characters in the provided string.
*/
void	skip_hwhitespace(char *str, int *i)
{
	while (is_hws(str[*i]))
		(*i)++;
}

/*
** Counts trailing whitespace characters at the end of a string.
*/
int	count_trailing_ws(char *str)
{
	int	i;
	int	c;

	i = ft_strlen(str) - 1;
	c = 0;
	while (i > 0 && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
	{
		c++;
		i--;
	}
	return (c);
}
