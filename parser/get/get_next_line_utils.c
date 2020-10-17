/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 14:15:45 by tlavelle          #+#    #+#             */
/*   Updated: 2020/06/17 13:01:30 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	int		len;

	len = ft_strlen(s);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, s, len + 1);
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *pointer;
	char *assign;

	if (!s1 || !s2)
		return (NULL);
	pointer = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	assign = pointer;
	if (pointer == NULL)
		return (NULL);
	while (*s1)
		*assign++ = *s1++;
	while (*s2)
		*assign++ = *s2++;
	*assign = '\0';
	return (pointer);
}

size_t	ft_strlen(const char *s)
{
	size_t count;

	count = 0;
	while (s[count] != '\0')
	{
		count++;
	}
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char*)s);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destination;
	unsigned char	*source;

	if (!dest && !src)
		return (NULL);
	destination = (unsigned char*)dest;
	source = (unsigned char*)src;
	while (n != 0)
	{
		*destination = *source;
		destination++;
		source++;
		n--;
	}
	return (dest);
}
