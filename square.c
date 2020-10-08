#include "minirt.h"

int square_ray(t_ray *ray, t_square *sq)
{
	int check;
	int color;

	check = 0;
	splane_intersec(ray, sq);
	if (ray->t1 >= ray->t_min && ray->t1 < ray->t_max)
	{
		sq->p[0] = ray->cam_x + ray->t1 * ray->vp_x;		
		sq->p[1] = ray->cam_y + ray->t1 * ray->vp_y;		
		sq->p[2] = ray->cam_z + ray->t1 * ray->vp_z;		
		if (inside_square(ray, sq))
			check = 1;
	}
	if (check == 0)
		return (0);
	color = (sq->color[0] << 16) + (sq->color[1] << 8) + (sq->color[2]);
	return (color);
}

void splane_intersec(t_ray *ray, t_square *sq)
{
	double oc[3];
	double k1;
	double k2;

	oc[0] = sq->a[0] - ray->cam_x;
	oc[1] = sq->a[1] - ray->cam_y;
	oc[2] = sq->a[2] - ray->cam_z;
	k1 = oc[0] * sq->n[0] + oc[1] * sq->n[1] + oc[2] * sq->n[2];
	k2 = ray->vp_x * sq->n[0] + ray->vp_y * sq->n[1] + ray->vp_z * sq->n[2];
	if (k2 == 0)
		ray->t1 = ray->t_max;
	else
		ray->t1 = k1 / k2;
}

int inside_square(t_ray *ray, t_square *sq)
{
	double x;
	double y;
	double sqr_ab;
	double sqr_ac;
	int i;

	i = 0;
	while (i < 3)
	{
		sq->vec_ab[i] = sq->b[i] - sq->a[i];
		sq->vec_ac[i] = sq->c[i] - sq->a[i];
		sq->vec_ap[i] = sq->p[i] - sq->a[i];
		i++;
	}
	sqr_ab = sqrt(sq->vec_ab[0] * sq->vec_ab[0] + sq->vec_ab[1] * sq->vec_ab[1] + sq->vec_ab[2] * sq->vec_ab[2]);
	sqr_ac = sqrt(sq->vec_ac[0] * sq->vec_ac[0] + sq->vec_ac[1] * sq->vec_ac[1] + sq->vec_ac[2] * sq->vec_ac[2]);
	x = (dot_prod(sq->vec_ap, sq->vec_ab) / sqr_ab); 
	y = (dot_prod(sq->vec_ap, sq->vec_ac) / sqr_ac); 
	if (x >= 0 && x <= 1 && y >= 0 && y <= 1)
		return (1);
	return (0);
}
