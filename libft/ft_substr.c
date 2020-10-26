/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:49:21 by tlavelle          #+#    #+#             */
/*   Updated: 2020/05/28 15:55:20 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*pointer;
	size_t	counter;
	size_t	reallen;

	counter = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	reallen = ft_strlen(s + start);
	if (reallen < len)
		len = reallen;
	pointer = (char*)malloc(sizeof(char) * (len + 1));
	if (pointer == NULL)
		return (NULL);
	while (counter < len)
	{
		pointer[counter] = s[start + counter];
		counter++;
	}
	pointer[counter] = '\0';
	return (pointer);
}
