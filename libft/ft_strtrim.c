/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:30:00 by tlavelle          #+#    #+#             */
/*   Updated: 2020/05/28 16:53:35 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		inset(char const character, char const *set)
{
	while (*set != 0)
	{
		if (character == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*fillup(char *pointer, const char *s1, int len, int index)
{
	char	*counter;

	counter = pointer;
	while (len--)
		*counter++ = s1[index++];
	*counter = '\0';
	return (pointer);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		index;
	int		index2;
	char	*pointer;
	int		len;

	index = 0;
	if (!s1)
		return (NULL);
	index2 = ft_strlen(s1) - 1;
	while (s1[index] && inset(s1[index], set))
		index++;
	if (s1[index] != 0)
	{
		while (index2 >= 0 && inset(s1[index2], set))
			index2--;
	}
	len = index2 - index + 1;
	pointer = (char*)malloc(sizeof(char) * (len + 1));
	if (pointer == NULL)
		return (NULL);
	fillup(pointer, s1, len, index);
	return (pointer);
}
