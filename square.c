#include "minirt.h"

/*void square_ray(t_ray *ray, t_square *sq)
{
	int check;

	check = 0;
	splane_intersec(ray, sq);
	if (ray->t1 >= ray->t_min && ray->t1 < ray->t_max)
	{
		sq->p[0] = ray->cam[0] + ray->t1 * ray->vp[0];		
		sq->p[1] = ray->cam[1] + ray->t1 * ray->vp[1];		
		sq->p[2] = ray->cam[2] + ray->t1 * ray->vp[2];		
		if (inside_square(ray, sq))
			check = 1;
	}
	if (check == 0)
		return ;
	ray->color = (sq->color[0] << 16) + (sq->color[1] << 8) + (sq->color[2]);
}

void splane_intersec(t_ray *ray, t_square *sq)
{
	double oc[3];
	double k1;
	double k2;

	oc[0] = sq->a[0] - ray->cam[0];
	oc[1] = sq->a[1] - ray->cam[1];
	oc[2] = sq->a[2] - ray->cam[2];
	k1 = dot_prod(oc, sq->n);
	k2 = dot_prod(ray->vp, sq->n);
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
	sqr_ab = sqrt(dot_prod(sq->vec_ab, sq->vec_ab));
	sqr_ac = sqrt(dot_prod(sq->vec_ac, sq->vec_ac));
	x = (dot_prod(sq->vec_ap, sq->vec_ab) / sqr_ab); 
	y = (dot_prod(sq->vec_ap, sq->vec_ac) / sqr_ac); 
	if (x >= 0 && x <= 1 && y >= 0 && y <= 1)
		return (1);
	return (0);
}*/
