#include "minirt.h"

void	find_np_square(t_ray *ray, t_square *sq)
{
	double magnitude;

	magnitude = mag(sq->n);
	ray->p[0] = ray->cam[0] + ray->closest_t * ray->vp[0];
	ray->p[1] = ray->cam[1] + ray->closest_t * ray->vp[1];
	ray->p[2] = ray->cam[2] + ray->closest_t * ray->vp[2];
	ray->n[0] = sq->n[0] / magnitude;
	ray->n[1] = sq->n[1] / magnitude;
	ray->n[2] = sq->n[2] / magnitude;
}

int		inside_square(t_ray *ray, t_square *sq)
{
	double v1;
	double v2;
	double v3;
	double v4;

	v1 = orient(sq, sq->b, sq->a);
	v2 = orient(sq, sq->a, sq->d);
	v3 = orient(sq, sq->d, sq->e);
	v4 = orient(sq, sq->e, sq->b);
	if ((v1 * v2) <= 0)
		return (0);
	if ((v1 * v3) <= 0)
		return (0);
	if ((v1 * v4) <= 0)
		return (0);
	return (1);
}

double	orient(t_square *sq, double *a, double *b)
{
	double vec1[3];
	double pa[3];
	double pb[3];

	pa[0] = a[0] - sq->p[0];
	pa[1] = a[1] - sq->p[1];
	pa[2] = a[2] - sq->p[2];
	pb[0] = b[0] - sq->p[0];
	pb[1] = b[1] - sq->p[1];
	pb[2] = b[2] - sq->p[2];
	cross_prod(vec1, pa, pb);
	return (dot_prod(vec1, sq->n));
}
