/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 17:10:00 by tlavelle          #+#    #+#             */
/*   Updated: 2020/05/15 13:22:41 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char *pointer;
	unsigned char byte;

	pointer = (unsigned char*)s;
	byte = (unsigned char)c;
	while (n != 0)
	{
		*pointer = byte;
		pointer++;
		n--;
	}
	return (s);
}
