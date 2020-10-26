/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 16:06:01 by tlavelle          #+#    #+#             */
/*   Updated: 2020/05/28 16:59:40 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *root;
	t_list *current;

	if (!lst)
		return (NULL);
	if (!(current = ft_lstnew(f(lst->content))))
		return (NULL);
	root = current;
	lst = lst->next;
	while (lst != NULL)
	{
		if (!(current = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&root, del);
			return (NULL);
		}
		ft_lstadd_back(&root, current);
		lst = lst->next;
	}
	return (root);
}
