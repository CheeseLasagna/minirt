/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:20:11 by tlavelle          #+#    #+#             */
/*   Updated: 2020/05/28 16:54:00 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		wordsnb(char const *s, char c)
{
	int number;

	if (!s)
		return (0);
	number = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		if (*s != 0)
		{
			number++;
			while (*s != c && *s != 0)
				s++;
		}
	}
	return (number);
}

char	**ft_free(char **pointer, int index)
{
	while (index >= 0)
	{
		free(pointer[index]);
		index--;
	}
	free(pointer);
	return (NULL);
}

int		ft_length(const char *s, char c)
{
	int length;

	length = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0' && *s != c)
	{
		length++;
		s++;
	}
	return (length);
}

char	**ft_split(char const *s, char c)
{
	char	**pointer;
	char	*str;
	int		index;
	int		length;
	int		numberofw;

	if (!(numberofw = wordsnb(s, c)) && !s)
		return (NULL);
	index = -1;
	if (!(pointer = (char**)malloc(sizeof(char*) * (numberofw + 1))))
		return (NULL);
	while (++index < numberofw)
	{
		while (*s == c)
			s++;
		length = ft_length(s, c);
		if (!(pointer[index] = (char*)malloc(sizeof(char) * (length + 1))))
			return (ft_free(pointer, index));
		str = pointer[index];
		while (length--)
			*str++ = *s++;
		*str = '\0';
	}
	pointer[index] = NULL;
	return (pointer);
}
