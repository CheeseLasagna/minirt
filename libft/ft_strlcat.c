/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:37:35 by tlavelle          #+#    #+#             */
/*   Updated: 2020/05/28 17:23:31 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	int		freespace;
	size_t	index;

	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	freespace = size - destlen - 1;
	index = 0;
	while (freespace > 0 && src[index] != 0)
	{
		dest[destlen + index] = src[index];
		index++;
		freespace--;
	}
	dest[destlen + index] = '\0';
	if (size < destlen)
		return (size + srclen);
	return (destlen + srclen);
}
