#include "minirt.h"

int		sphere_ray(t_ray *ray, t_sphere *sph)
{
	t_sphere *ptrsph;
	int closest_t = ray->t_max;
	int color;

	ptrsph = NULL;
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
	double oc_x = ray->cam_x - sph->x;
	double oc_y = ray->cam_y - sph->y;
	double oc_z = ray->cam_z - sph->z;

	double k1 = ray->vp_x * ray->vp_x + ray->vp_y * ray->vp_y + ray->vp_z * ray->vp_z;
	double k2 = 2 * (oc_x * ray->vp_x + oc_y * ray->vp_y + oc_z * ray->vp_z);
	double k3 = (oc_x * oc_x + oc_y * oc_y + oc_z * oc_z) - sph->radius * sph->radius;

	double discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0)
	{
		ray->t1 = ray->t_max;
		ray->t2 = ray->t_max;
	}
	else
	{
		ray->t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
		ray->t2 = (-k2 - sqrt(discriminant)) / (2 * k1);
	}
}
