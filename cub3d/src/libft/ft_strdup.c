/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:40:33 by bde-luce          #+#    #+#             */
/*   Updated: 2024/10/24 15:38:30 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;
	size_t	j;

	j = ft_strlen(s) + 1;
	dup = malloc(sizeof(char) * j);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < j)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}
