/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_res.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:41:47 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:41:50 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	parse_resol(char *line, t_objects *root)
{
	t_resol *res;

	res = (t_resol*)malloc(sizeof(t_resol));
	if (res == NULL)
	{
		write(1, "Error\nno memory\n", 16);
		free_root(root);
		exit(0);
	}
	if ((fill_resol(line, res)) == -1)
	{
		write(1, "Error\nInvalid arguments in .rt file\n", 36);
		free_root(root);
		exit(0);
	}
	lst_addback_resol(root, res);
}

int		fill_resol(char *line, t_resol *res)
{
	line = line + 1;
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((resol(&line, res->r)) == -1)
		return (-1);
	skip_space(&line);
	if (*line != '\0')
		return (-1);
	return (1);
}

int		resol(char **line, int *r)
{
	r[0] = atoi_rt(line);
	if (r[0] > 1366)
		r[0] = 1366;
	if ((skip_space(line)) == -1)
		return (-1);
	r[1] = atoi_rt(line);
	if (r[1] > 768)
		r[1] = 768;
	return (1);
}
