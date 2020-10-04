#include "minirt.h"

int plane_ray(t_ray *ray, t_plane *pl)
{
	int check;
//	int closest_t;
	int color;

	check = 0;
	plane_intersec(ray, pl);
	if (ray->t1 >= ray->t_min && ray->t1 < ray->t_max)
	{
		check = 1;
	}
	if (check == 0)
		return (0);
	color = (pl->color[0] << 16) + (pl->color[1] << 8) + (pl->color[2]);
	return (color);
}

void plane_intersec(t_ray *ray, t_plane *pl)
{
	double oc_x;
	double oc_y;
	double oc_z;

	oc_x = pl->x - ray->cam_x;
	oc_y = pl->y - ray->cam_y;
	oc_z = pl->z - ray->cam_z;
			
	double k1 = oc_x * pl->n_x + oc_y * pl->n_y + oc_z * pl->n_z;
	double k2 = ray->vp_x * pl->n_x + ray->vp_y * pl->n_y + ray->vp_z *pl->n_z;
	if (k2 == 0)
		ray->t1 = ray->t_max;
	else
		ray->t1 = k1 / k2;
}
