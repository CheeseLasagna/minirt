/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoahex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:26:31 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 11:26:33 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lenhex(long unsigned int n)
{
	int length;

	length = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		length++;
		n = n / 16;
	}
	return (length);
}

char	*ft_itoahex(long unsigned int n, int bigsmall)
{
	int					len;
	char				*ptr;
	long unsigned int	y;

	len = ft_lenhex(n);
	if (!(ptr = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ptr[len--] = '\0';
	while (len >= 0)
	{
		y = n % 16;
		if (y > 9)
		{
			if (bigsmall)
				ptr[len--] = y + 55;
			else
				ptr[len--] = y + 87;
		}
		else
			ptr[len--] = y + 48;
		n = n / 16;
	}
	return (ptr);
}
