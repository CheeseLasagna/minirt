/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 21:43:11 by tlavelle          #+#    #+#             */
/*   Updated: 2020/05/17 19:06:38 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *first;
	unsigned char *second;

	first = (unsigned char*)s1;
	second = (unsigned char*)s2;
	if (n == 0)
		return (0);
	while (n-- > 0)
	{
		if (*first != *second)
			return (*first - *second);
		first++;
		second++;
	}
	return (0);
}
