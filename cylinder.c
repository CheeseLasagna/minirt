#include "minirt.h"

int cylinder_ray(t_ray *ray, t_cylinder *cy)
{
	int check;
	int color;

	check = 0;
	double closest_t = ray->t_max;
	cylinder_intersec(ray, cy);
	if ((ray->t1 >= ray->t_min && ray->t1 < ray->t_max) && ray->t1 < closest_t)
	{
		closest_t = ray->t1;
		check = 1;
	}
	if ((ray->t2 >= ray->t_min && ray->t2 < ray->t_max) && ray->t2 < closest_t)
	{
		closest_t = ray->t2;
		check = 1;
	}
	if (check == 0)
		return (0);
	color = (cy->color[0] << 16) + (cy->color[1] << 8) + (cy->color[2]);
}

void cylinder_intersec(t_ray *ray, t_cylinder *cy)
{
	double co_x = ray->cam_x - cy->c[0];
	double co_y = ray->cam_y - cy->c[1];
	double co_z = ray->cam_z - cy->c[2];
	double a = ray->vp_x * ray->vp_x + ray->vp_z * ray->vp_z + ray->vp_y * ray->vp_y;
	double b = 2 * (co_x * ray->vp_x + co_z * ray->vp_z + co_y * ray->vp_y);
	double c = co_x * co_x + co_z * co_z + co_y * co_y - cy->radius * cy->radius;
	double discriminant = b * b - 4 * a * c;	
	if (discriminant < 0)
	{
		ray->t1 = ray->t_max;
		ray->t2 = ray->t_max;
	}
	else
	{
		ray->t1 = (-b + sqrt(discriminant)) / (2 * a);
		ray->t2 = (-b - sqrt(discriminant)) / (2 * a);
	}
}
