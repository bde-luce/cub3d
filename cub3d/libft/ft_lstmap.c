/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:14:17 by bde-luce          #+#    #+#             */
/*   Updated: 2024/10/24 15:36:59 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst2;
	t_list	*new;

	if (!lst || !f || !del)
		return (NULL);
	lst2 = NULL;
	while (lst != NULL)
	{
		new = malloc(sizeof(t_list));
		if (!new)
		{
			ft_lstclear(&lst, del);
			return (NULL);
		}
		new->content = f(lst->content);
		new->next = NULL;
		ft_lstadd_back(&lst2, new);
		lst = lst->next;
	}
	return (lst2);
}
