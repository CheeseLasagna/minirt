#include "minirt.h"

double	find_width(double deg)
{
	double radian;
	double c;
	double width;

	deg = deg / 2;
	radian = deg * 3.14 / 180;
	c = 1 / cos(radian);
	width = sqrt(c * c - 1);
	width = width * 2;
	return (width);
}

int		close_k(void)
{
	exit(0);
}

int		check_shadow(t_ray ray, t_objects *root, double *l)
{
	ray.cam[0] = ray.p[0];
	ray.cam[1] = ray.p[1];
	ray.cam[2] = ray.p[2];
	ray.vp[0] = l[0];
	ray.vp[1] = l[1];
	ray.vp[2] = l[2];
	ray.t_min = 0.001;
	ray.t_max = 1;
	ray.closest_t = ray.t_max;
	if ((sphere_shadow(&ray, root)) == 1)
		return (1);
	if ((plane_shadow(&ray, root)) == 1)
		return (1);
	if ((cylinder_shadow(&ray, root)) == 1)
		return (1);
	if ((triangle_shadow(&ray, root)) == 1)
		return (1);
	if ((square_shadow(&ray, root)) == 1)
		return (1);
	return (0);
}
