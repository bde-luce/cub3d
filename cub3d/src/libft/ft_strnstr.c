/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:39:09 by bde-luce          #+#    #+#             */
/*   Updated: 2024/10/24 15:39:21 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 1;
	while (big[i] && little[j] && i < len)
	{
		if (big[i] != little[j])
		{
			j = 0;
			i = k;
			k++;
		}
		else
		{
			j++;
			i++;
		}
	}
	if (j < ft_strlen(little))
		return (NULL);
	else
		return ((char *)big + (i - j));
}
