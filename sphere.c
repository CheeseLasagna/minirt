#include "minirt.h"

int		sphere_ray(t_ray *ray, t_sphere *sph)
{
	t_sphere *ptrsph;
	int closest_t;
	int color;

	ptrsph = NULL;
	closest_t = ray->t_max;
	sphere_intersec(ray, sph);
	if ((ray->t1 >= ray->t_min && ray->t1 < ray->t_max) && ray->t1 < closest_t)	
	{
		closest_t = ray->t1;
		ptrsph = sph;
	}
	if ((ray->t2 >= ray->t_min && ray->t2 < ray->t_max) && ray->t2 < closest_t)
	{
		closest_t = ray->t2;
		ptrsph = sph;
	}
	if (ptrsph == NULL)
		return (0);
	color = (sph->color[0] << 16) + (sph->color[1] << 8) + (sph->color[2]);
	return (color);
}

void sphere_intersec(t_ray *ray, t_sphere *sph)
{
	double oc_x;
	double oc_y;
	double oc_z;
	t_calc calc;
	
	oc_x = ray->cam_x - sph->x;
	oc_y = ray->cam_y - sph->y;
	oc_z = ray->cam_z - sph->z;
	calc.k1 = ray->vp_x * ray->vp_x + ray->vp_y * ray->vp_y + ray->vp_z * ray->vp_z;
	calc.k2 = 2 * (oc_x * ray->vp_x + oc_y * ray->vp_y + oc_z * ray->vp_z);
	calc.k3 = (oc_x * oc_x + oc_y * oc_y + oc_z * oc_z) - sph->radius * sph->radius;
	calc.discriminant = calc.k2 * calc.k2 - 4 * calc.k1 * calc.k3;
	if (calc.discriminant < 0)
	{
		ray->t1 = ray->t_max;
		ray->t2 = ray->t_max;
	}
	else
	{
		ray->t1 = (-calc.k2 + sqrt(calc.discriminant)) / (2 * calc.k1);
		ray->t2 = (-calc.k2 - sqrt(calc.discriminant)) / (2 * calc.k1);
	}
}
