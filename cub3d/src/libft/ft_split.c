/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:35:52 by bde-luce          #+#    #+#             */
/*   Updated: 2024/10/24 19:04:22 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_del(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	return (count);
}

static	int	count_char(int i, char const *s, char c)
{
	int	count;

	count = 0;
	while (s[i] != c && s[i])
	{
		i++;
		count++;
	}
	return (count);
}

static void	free_arr(int i, char **arr)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

static	char	**split(char **arr, char const *s, char c, int l)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < l)
	{
		while (s[k] && s[k] == c)
			k++;
		arr[i] = malloc(sizeof(char) * (count_char(k, s, c) + 1));
		if (!arr[i])
		{
			free_arr(i, arr);
			return (NULL);
		}
		j = 0;
		while (s[k] && s[k] != c)
			arr[i][j++] = s[k++];
		arr[i][j] = '\0';
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**arr;

	if (!s)
		return (NULL);
	i = count_del(s, c);
	arr = malloc(sizeof(char *) * (i + 1));
	if (!arr)
		return (NULL);
	return (split(arr, s, c, i));
}
