/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 13:22:31 by tlavelle          #+#    #+#             */
/*   Updated: 2020/07/17 12:19:30 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	add_rem(char **rem, char **line)
{
	char	*ptr;
	int		len;

	if ((ptr = ft_strchr(*rem, '\n')))
	{
		*ptr++ = '\0';
		*line = ft_strdup(*rem);
		len = ft_strlen(ptr);
		*rem = ft_memcpy(*rem, ptr, len + 1);
	}
	else
	{
		*line = ft_strdup(*rem);
		free(*rem);
		*rem = NULL;
	}
}

void	add_line(char **rem, int br, char **line, char *buff)
{
	char *leaks;

	buff[br] = '\0';
	if ((*rem = ft_strchr(buff, '\n')))
	{
		**rem = '\0';
		*rem = *rem + 1;
		*rem = ft_strdup(*rem);
	}
	leaks = *line;
	*line = ft_strjoin(*line, buff);
	free(leaks);
}

int		get_next_line(int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	int			byrd;
	static char	*rem;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (rem)
		add_rem(&rem, line);
	else
		*line = ft_strdup("");
	byrd = 0;
	while (!rem && (byrd = read(fd, buff, BUFFER_SIZE)))
	{
		if (byrd == -1)
			return (byrd);
		add_line(&rem, byrd, line, buff);
	}
	if (byrd == 0 && !rem)
		return (0);
	return (1);
}
