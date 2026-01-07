/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:09:32 by bde-luce          #+#    #+#             */
/*   Updated: 2024/10/24 15:37:44 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	void	*temp;

	temp = (void *)src;
	if (!dest && !src)
		return (dest);
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			((char *)dest)[i] = ((char *)temp)[i];
			i++;
		}
	}
	else
	{
		while (n--)
			((char *)dest)[n] = ((char *)temp)[n];
	}
	return (dest);
}
