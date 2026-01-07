/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:20:03 by bde-luce          #+#    #+#             */
/*   Updated: 2024/10/24 15:39:40 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;
	size_t	l;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen(s);
	if (j < start)
		l = 0;
	else if (j > (len + start))
		l = len;
	else
		l = (j - start);
	substr = malloc(sizeof(char) * (l + 1));
	if (!substr)
		return (NULL);
	while (i < len && start < j)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
