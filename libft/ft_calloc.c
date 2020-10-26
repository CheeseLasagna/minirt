/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 20:45:12 by tlavelle          #+#    #+#             */
/*   Updated: 2020/05/28 16:37:08 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *pointer;

	pointer = malloc(size * nmemb);
	if (pointer == NULL)
		return (NULL);
	else
	{
		ft_memset(pointer, 0, size * nmemb);
		return (pointer);
	}
}
