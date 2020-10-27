/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoaun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:24:46 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 11:26:08 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		lenun(unsigned int n)
{
	int length;

	length = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

char	*ft_itoaun(unsigned int n)
{
	char	*ptr;
	int		len;

	len = lenun(n);
	ptr = (char*)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[len--] = '\0';
	while (len >= 0)
	{
		ptr[len--] = n % 10 + 48;
		n = n / 10;
	}
	return (ptr);
}
