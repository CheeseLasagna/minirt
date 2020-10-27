/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:41:59 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:42:01 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		arg_check(int argc, char **argv)
{
	int i;

	if (argc < 2 || argc > 3)
	{
		write(1, "Error\nWrong number of arguments\n", 32);
		exit(0);
	}
	i = ft_strlen(argv[1]);
	if (i < 4 || argv[1][i] != '\0' || argv[1][i - 1] != 't'
		|| argv[1][i - 2] != 'r' || argv[1][i - 3] != '.')
	{
		write(1, "Error\nwrong file type\n", 22);
		exit(0);
	}
	if (argc == 3 && (ft_memcmp(argv[2], "--save", 7)))
	{
		write(1, "Error\nwrong second argument\n", 28);
		exit(0);
	}
	if (argc == 2)
		return (0);
	return (1);
}

void	open_read(int argc, char **argv, t_objects *root)
{
	char	*line;
	int		i;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error\n");
		exit(0);
	}
	while ((i = get_next_line(fd, &line)))
	{
		parse_line(line, root);
		free(line);
	}
	free(line);
	if (root->resol == NULL)
	{
		write(1, "Error\nResolution not set\n", 25);
		free_root(root);
		exit(0);
	}
}
