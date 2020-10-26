/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 11:04:47 by tlavelle          #+#    #+#             */
/*   Updated: 2020/05/26 22:00:51 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*first;
	char	*second;
	size_t	length;

	first = (char*)big;
	second = (char*)little;
	length = len;
	if (*second == '\0')
		return ((char*)big);
	if (ft_strlen(little) > ft_strlen(big) || ft_strlen(little) > len)
		return (NULL);
	while (*big != '\0' && length != 0)
	{
		while (length-- != 0 && *first++ == *second++)
		{
			if (*second == '\0')
				return ((char*)big);
		}
		length = --len;
		big++;
		first = (char*)big;
		second = (char*)little;
	}
	return (NULL);
}
