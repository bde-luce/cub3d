/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:46:25 by bde-luce          #+#    #+#             */
/*   Updated: 2024/10/24 15:39:34 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char c, char const *str)
{
	size_t	i;
	size_t	r;

	i = 0;
	r = 0;
	while (str[i] && r == 0)
	{
		if (c == str[i])
			r = 1;
		i++;
	}
	return (r);
}

size_t	getj(size_t i, char const *s1, char const *set)
{
	size_t	j;

	if (s1[i] != '\0')
	{
		j = ft_strlen(s1);
		while (check(s1[j - 1], set) == 1)
			j--;
	}
	else
		j = i;
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*trim;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (check(s1[i], set) == 1 && s1[i])
		i++;
	j = getj(i, s1, set);
	trim = malloc(sizeof(char) * (j - i + 1));
	if (!trim)
		return (NULL);
	k = 0;
	while (i < j)
		trim[k++] = s1[i++];
	trim[k] = '\0';
	return (trim);
}
