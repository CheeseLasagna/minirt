#include "minirt.h"

int	cylinder_limits(t_ray *ray, t_cylinder *cy)
{
	double cp[3];

	cy->p[0] = ray->cam[0] + ray->t1 * ray->vp[0];
	cy->p[1] = ray->cam[1] + ray->t1 * ray->vp[1];
	cy->p[2] = ray->cam[2] + ray->t1 * ray->vp[2];
	cp[0] = cy->p[0] - cy->c[0];
	cp[1] = cy->p[1] - cy->c[1];
	cp[2] = cy->p[2] - cy->c[2];
	cy->m = dot_prod(cp, cy->n) / dot_prod(cy->n, cy->n);
	if (cy->m >= 0 && cy->m <= cy->height)
		return (1);
	return (0);
}

int	cylinder_limits2(t_ray *ray, t_cylinder *cy)
{
	double cp[3];

	cy->p[0] = ray->cam[0] + ray->t2 * ray->vp[0];
	cy->p[1] = ray->cam[1] + ray->t2 * ray->vp[1];
	cy->p[2] = ray->cam[2] + ray->t2 * ray->vp[2];
	cp[0] = cy->p[0] - cy->c[0];
	cp[1] = cy->p[1] - cy->c[1];
	cp[2] = cy->p[2] - cy->c[2];
	cy->m = dot_prod(cp, cy->n) / dot_prod(cy->n, cy->n);
	if (cy->m >= 0 && cy->m <= cy->height)
		return (1);
	return (0);
}
