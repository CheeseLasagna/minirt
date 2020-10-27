/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:43:23 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:43:25 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		skip_space(char **line)
{
	if (**line != ' ')
		return (-1);
	while (**line == ' ')
		(*line)++;
	return (1);
}

int		coordinates(char **line, double *c)
{
	c[0] = atoi_doub_rt(line);
	if (**line != ',')
		return (-1);
	(*line)++;
	c[1] = atoi_doub_rt(line);
	if (**line != ',')
		return (-1);
	(*line)++;
	c[2] = atoi_doub_rt(line);
	return (1);
}

int		direction(char **line, double *n)
{
	n[0] = atoi_doub_rt(line);
	if (**line != ',' || n[0] < -1 || n[0] > 1)
		return (-1);
	(*line)++;
	n[1] = atoi_doub_rt(line);
	if (**line != ',' || n[1] < -1 || n[1] > 1)
		return (-1);
	(*line)++;
	n[2] = atoi_doub_rt(line);
	if (n[2] < -1 || n[2] > 1)
		return (-1);
	return (1);
}

int		color(char **line, int *color)
{
	color[0] = atoi_rt(line);
	if (**line != ',' || color[0] < 0 || color[0] > 255)
		return (-1);
	(*line)++;
	color[1] = atoi_rt(line);
	if (**line != ',' || color[1] < 0 || color[1] > 255)
		return (-1);
	(*line)++;
	color[2] = atoi_rt(line);
	if (color[1] < 0 || color[1] > 255)
		return (-1);
	return (1);
}

void	side(char **line, double *r)
{
	*r = atoi_doub_rt(line);
}
