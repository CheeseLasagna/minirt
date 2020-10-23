#include "minirt.h"

void	triangle_ray(t_ray *ray, t_objects *root)
{
	t_triangle *tr;
	t_triangle *temp;

	tr = NULL;
	temp = root->triangle;
	while (temp != NULL)
	{
		triangle_closest(ray, &tr, temp);
		temp = temp->next;
	}
	if (tr == NULL)
		return ;
	find_np_triangle(ray, tr);
	compute_lighting(root, ray);
	compute_color_triangle(ray, root, tr);
	ray->color = (ray->red << 16) + (ray->green << 8) + (ray->blue);
}

void	triangle_closest(t_ray *ray, t_triangle **tr, t_triangle *temp)
{
	find_normal(temp);
	tplane_intersec(ray, temp);
	if ((ray->t1 >= ray->t_min && ray->t1 < ray->t_max)
							&& ray->t1 < ray->closest_t)
	{
		temp->p[0] = ray->cam[0] + ray->t1 * ray->vp[0];
		temp->p[1] = ray->cam[1] + ray->t1 * ray->vp[1];
		temp->p[2] = ray->cam[2] + ray->t1 * ray->vp[2];
		if (inside_triangle(ray, temp))
		{
			ray->closest_t = ray->t1;
			*tr = temp;
		}
	}
}

void	find_normal(t_triangle *tr)
{
	double vec_ab[3];
	double vec_ac[3];

	vec_ab[0] = tr->b[0] - tr->a[0];
	vec_ab[1] = tr->b[1] - tr->a[1];
	vec_ab[2] = tr->b[2] - tr->a[2];
	vec_ac[0] = tr->c[0] - tr->a[0];
	vec_ac[1] = tr->c[1] - tr->a[1];
	vec_ac[2] = tr->c[2] - tr->a[2];
	cross_prod(tr->n, vec_ab, vec_ac);
}

void	tplane_intersec(t_ray *ray, t_triangle *tr)
{
	double oc[3];
	double k1;
	double k2;

	oc[0] = tr->a[0] - ray->cam[0];
	oc[1] = tr->a[1] - ray->cam[1];
	oc[2] = tr->a[2] - ray->cam[2];
	k1 = dot_prod(oc, tr->n);
	k2 = dot_prod(ray->vp, tr->n);
	if (k2 == 0)
		ray->t1 = ray->t_max;
	else
		ray->t1 = k1 / k2;
}

int		inside_triangle(t_ray *ray, t_triangle *tr)
{
	int		i;
	double	testveca[3];
	double	testvecb[3];
	double	testvecc[3];

	i = 0;
	while (i < 3)
	{
		tr->vec_ab[i] = tr->b[i] - tr->a[i];
		tr->vec_bc[i] = tr->c[i] - tr->b[i];
		tr->vec_ca[i] = tr->a[i] - tr->c[i];
		tr->vec_ap[i] = tr->p[i] - tr->a[i];
		tr->vec_bp[i] = tr->p[i] - tr->b[i];
		tr->vec_cp[i] = tr->p[i] - tr->c[i];
		i++;
	}
	cross_prod(testveca, tr->vec_ab, tr->vec_ap);
	cross_prod(testvecb, tr->vec_bc, tr->vec_bp);
	cross_prod(testvecc, tr->vec_ca, tr->vec_cp);
	if ((dot_prod(testveca, tr->n)) < 0 || (dot_prod(testvecb, tr->n)) < 0
						|| (dot_prod(testvecc, tr->n)) < 0)
		return (0);
	return (1);
}
