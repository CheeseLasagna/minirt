/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 16:39:38 by tlavelle          #+#    #+#             */
/*   Updated: 2020/07/20 10:44:14 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_len(int n)
{
	int length;

	length = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		length++;
		n = n * -1;
	}
	while (n)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*pointer;
	int		len;
	int		sign;

	sign = 1;
	len = ft_len(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = n * -1;
		sign = 0;
	}
	pointer = (char*)malloc(sizeof(char) * (len + 1));
	if (pointer == NULL)
		return (NULL);
	pointer[len--] = '\0';
	while (len >= 0)
	{
		pointer[len--] = n % 10 + 48;
		n = n / 10;
	}
	if (sign == 0)
		pointer[0] = '-';
	return (pointer);
}
