/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:51:44 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:51:45 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	square_ray(t_ray *ray, t_objects *root)
{
	t_square *sq;
	t_square *temp;

	sq = NULL;
	temp = root->square;
	while (temp != NULL)
	{
		square_closest(ray, &sq, temp);
		temp = temp->next;
	}
	if (sq == NULL)
		return ;
	find_np_square(ray, sq);
	compute_lighting(root, ray);
	compute_color_square(ray, root, sq);
	ray->color = (ray->red << 16) + (ray->green << 8) + (ray->blue);
}

void	square_closest(t_ray *ray, t_square **sq, t_square *temp)
{
	splane_intersec(ray, temp);
	if ((ray->t1 >= ray->t_min && ray->t1 < ray->t_max)
							&& ray->t1 < ray->closest_t)
	{
		temp->p[0] = ray->cam[0] + ray->t1 * ray->vp[0];
		temp->p[1] = ray->cam[1] + ray->t1 * ray->vp[1];
		temp->p[2] = ray->cam[2] + ray->t1 * ray->vp[2];
		if (temp->check == 0)
			find_vertices(ray, temp);
		if (inside_square(ray, temp))
		{
			ray->closest_t = ray->t1;
			*sq = temp;
		}
	}
}

void	splane_intersec(t_ray *ray, t_square *sq)
{
	double oc[3];
	double k1;
	double k2;

	oc[0] = sq->c[0] - ray->cam[0];
	oc[1] = sq->c[1] - ray->cam[1];
	oc[2] = sq->c[2] - ray->cam[2];
	k1 = dot_prod(oc, sq->n);
	k2 = dot_prod(ray->vp, sq->n);
	if (k2 == 0)
		ray->t1 = ray->t_max;
	else
		ray->t1 = k1 / k2;
}

void	find_vertices(t_ray *ray, t_square *temp)
{
	double radius;
	double magni;
	double cp[3];

	radius = temp->side / 2;
	radius = sqrt(radius * radius + radius * radius);
	cp[0] = temp->p[0] - temp->c[0];
	cp[1] = temp->p[1] - temp->c[1];
	cp[2] = temp->p[2] - temp->c[2];
	magni = mag(cp);
	if (magni >= radius - 0.001 && magni <= radius + 0.001)
		find_vertices2(magni, cp, temp);
}

void	find_vertices2(double magni, double *cp, t_square *temp)
{
	temp->check = 1;
	temp->b[0] = temp->p[0];
	temp->b[1] = temp->p[1];
	temp->b[2] = temp->p[2];
	temp->d[0] = temp->c[0] - cp[0];
	temp->d[1] = temp->c[1] - cp[1];
	temp->d[2] = temp->c[2] - cp[2];
	cp[0] = cp[0] / magni;
	cp[1] = cp[1] / magni;
	cp[2] = cp[2] / magni;
	cross_prod(temp->a, cp, temp->n);
	temp->a[0] = temp->a[0] * magni;
	temp->a[1] = temp->a[1] * magni;
	temp->a[2] = temp->a[2] * magni;
	temp->e[0] = temp->c[0] - temp->a[0];
	temp->e[1] = temp->c[1] - temp->a[1];
	temp->e[2] = temp->c[2] - temp->a[2];
	temp->a[0] = temp->c[0] + temp->a[0];
	temp->a[1] = temp->c[1] + temp->a[1];
	temp->a[2] = temp->c[2] + temp->a[2];
}
