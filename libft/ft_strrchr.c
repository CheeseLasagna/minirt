/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 22:00:03 by tlavelle          #+#    #+#             */
/*   Updated: 2020/05/28 16:32:39 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	while (*s != c)
	{
		if (len == 0)
			return (NULL);
		len--;
		s--;
	}
	return ((char*)s);
}
