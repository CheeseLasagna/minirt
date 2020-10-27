/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:50:34 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:50:38 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	compute_lighting(t_objects *root, t_ray *ray)
{
	double	l[3];
	t_light	*light;

	light = root->light;
	ray->i = 0;
	if (root->ambient->i != 0)
		ray->i = ray->i + root->ambient->i;
	compute_lighting2(l, &light, ray, root);
	if (ray->i > 1)
		ray->i = 1;
}

void	compute_lighting2(double *l, t_light **light, t_ray *ray,
												t_objects *root)
{
	double dot;

	while (*light != NULL)
	{
		if ((*light)->i != 0)
		{
			l[0] = (*light)->c[0] - ray->p[0];
			l[1] = (*light)->c[1] - ray->p[1];
			l[2] = (*light)->c[2] - ray->p[2];
			if ((check_shadow(*ray, root, l)))
			{
				*light = (*light)->next;
				continue ;
			}
			dot = dot_prod(ray->n, l);
			if (dot > 0)
				ray->i += (*light)->i * (dot / (mag(ray->n) * mag(l)));
		}
		*light = (*light)->next;
	}
}

void	cross_prod(double *res, double *vec1, double *vec2)
{
	res[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	res[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	res[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

double	dot_prod(double *vec1, double *vec2)
{
	double result;

	result = vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
	return (result);
}

double	mag(double *vec)
{
	double x;

	x = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	return (x);
}
