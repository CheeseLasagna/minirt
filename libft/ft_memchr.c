/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 21:33:55 by tlavelle          #+#    #+#             */
/*   Updated: 2020/05/26 22:35:06 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *pointer;
	unsigned char byte;

	pointer = (unsigned char*)s;
	byte = (unsigned char)c;
	while (n-- != 0)
	{
		if (*pointer == byte)
		{
			return (pointer);
		}
		pointer++;
	}
	return (NULL);
}
