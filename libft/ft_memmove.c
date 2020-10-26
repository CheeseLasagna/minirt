/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:17:11 by tlavelle          #+#    #+#             */
/*   Updated: 2020/05/28 16:23:29 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *destination;
	unsigned char *source;

	if (!src && !dest)
		return (NULL);
	destination = (unsigned char*)dest;
	source = (unsigned char*)src;
	if (destination < source)
	{
		while (n-- != 0)
			*destination++ = *source++;
	}
	else
	{
		destination = destination + n - 1;
		source = source + n - 1;
		while (n-- != 0)
			*destination-- = *source--;
	}
	return (dest);
}
