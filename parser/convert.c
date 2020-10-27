/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:43:13 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:43:15 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		atoi_rt(char **line)
{
	int sign;
	int number;
	int check;

	sign = 1;
	number = 0;
	check = 0;
	if (**line == '-')
	{
		sign = -1;
		(*line)++;
	}
	while (**line >= '0' && **line <= '9')
	{
		check = 1;
		number = 10 * number + (**line - 48);
		(*line)++;
	}
	if (check == 0)
		**line = '&';
	number = number * sign;
	return (number);
}

double	atoi_doub_rt(char **line)
{
	int		sign;
	double	number;
	int		check;

	sign = 1;
	number = 0;
	check = 0;
	if (**line == '-')
	{
		sign = -1;
		(*line)++;
	}
	while (**line >= '0' && **line <= '9')
	{
		check = 1;
		number = 10 * number + (**line - 48);
		(*line)++;
	}
	if (check == 0)
		**line = '&';
	if (**line == '.')
		number = atoi_doub_rt2(line, number);
	number = number * sign;
	return (number);
}

double	atoi_doub_rt2(char **line, double number)
{
	double ten;

	ten = 10;
	(*line)++;
	while (**line >= '0' && **line <= '9')
	{
		number = number + (**line - 48) / ten;
		ten = ten * 10;
		(*line)++;
	}
	return (number);
}
