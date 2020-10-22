#include "minirt.h"

void square_ray(t_ray *ray, t_objects *root)
{
	t_square *sq;
	t_square *temp;

	sq = NULL;
	temp = root->square;
	while (temp != NULL)
	{
		square_closest(ray, &sq, temp);
		temp = temp->next;
	}
	if (sq == NULL)
		return ;
	find_np_square(ray, sq);
	compute_lighting(root, ray);
	compute_color_square(ray, root, sq);
	ray->color = (ray->red << 16) + (ray->green << 8) + (ray->blue);
}

void square_closest(t_ray *ray, t_square **sq, t_square *temp)
{
	splane_intersec(ray, temp);
	if ((ray->t1 >= ray->t_min && ray->t1 < ray->t_max) && ray->t1 < ray->closest_t)
	{
		temp->p[0] = ray->cam[0] + ray->t1 * ray->vp[0];  
		temp->p[1] = ray->cam[1] + ray->t1 * ray->vp[1];  
		temp->p[2] = ray->cam[2] + ray->t1 * ray->vp[2];  
/*		printf("b[0] = %f\n", temp->b[0]);
		printf("b[1] = %f\n", temp->b[1]);
		printf("b[2] = %f\n", temp->b[2]);
		if (temp->b[0] == 0 && temp->b[1] == 0 && temp->b[3] == 0)
			find_vertices(ray, temp);*/
		if (inside_square(ray, temp)) 
		{
			ray->closest_t = ray->t1;
			*sq = temp;
		}
	}
}

void splane_intersec(t_ray *ray, t_square *sq)
{
	double oc[3];
	double k1;
	double k2;

	oc[0] = sq->c[0] - ray->cam[0];
	oc[1] = sq->c[1] - ray->cam[1];
	oc[2] = sq->c[2] - ray->cam[2];
	k1 = dot_prod(oc, sq->n);
	k2 = dot_prod(ray->vp, sq->n);
	if (k2 == 0)
		ray->t1 = ray->t_max;
	else
		ray->t1 = k1 / k2;
}

/*void	find_vertices(t_ray *ray, t_square *temp)
{
	double radius;
	double magni;
	double cp[3];
	double vec_ca[3];
	double check[3];

	radius = temp->side / 2;
	radius = sqrt(radius * radius + radius * radius);
	cp[0] = temp->p[0] - temp->c[0];
	cp[1] = temp->p[1] - temp->c[1];
	cp[2] = temp->p[2] - temp->c[2];
	printf("radius = %f\n", radius);
	magni = mag(cp);
	if (magni >= radius - 0.001 && magni <= radius + 0.001)
	{
		temp->b[0] = temp->p[0];
		temp->b[1] = temp->p[1];
		temp->b[2] = temp->p[2];
		printf("ROOT POINT FOUND\n");
		temp->d[0] = temp->c[0] - cp[0];
		temp->d[1] = temp->c[1] - cp[1];
		temp->d[2] = temp->c[2] - cp[2];
		temp->a[0] = temp->c[0] - cp[0];
		temp->a[1] = temp->c[1] + cp[1];
		temp->a[2] = temp->c[2] + cp[2];
	}
	else
	{
		return ;
	}
    vec_ca[0] = temp->a[0] - temp->c[0];
	vec_ca[1] = temp->a[1] - temp->c[1];
	vec_ca[2] = temp->a[2] - temp->c[2];
	cross_prod(check, temp->n, temp->a);
	if ((mag(check)) == 0 || cmp(temp->a, temp->b) || cmp(temp->a, temp->d))
	{
		printf("FIRST ATTEMP FAILED\n");
		temp->a[0] = temp->c[0] + cp[0];
		temp->a[1] = temp->c[1] - cp[1];
		temp->a[2] = temp->c[2] + cp[2];
	}
	else
	{
		printf("vec_ca = %f\n", mag(vec_ca));
   		vec_ca[0] = temp->b[0] - temp->c[0];
		vec_ca[1] = temp->b[1] - temp->c[1];
		vec_ca[2] = temp->b[2] - temp->c[2];
		printf("vec_cb = %f\n", mag(vec_ca));
   		vec_ca[0] = temp->d[0] - temp->c[0];
		vec_ca[1] = temp->d[1] - temp->c[1];
		vec_ca[2] = temp->d[2] - temp->c[2];
		printf("vec_cd = %f\n\n", mag(vec_ca));
	}
	
}*/

int	cmp(double *a, double *b)
{
	if (a[0] != b[0])
		return (0);
	if (a[1] != b[1])
		return (0);
	if (a[2] != b[2])
		return (0);
	return (1);
}

int inside_square(t_ray *ray, t_square *temp)
{
	double radius;
	double magni;
	double cp[3];

	radius = temp->side / 2;
	radius = sqrt(radius * radius + radius * radius);
	cp[0] = temp->p[0] - temp->c[0];
	cp[1] = temp->p[1] - temp->c[1];
	cp[2] = temp->p[2] - temp->c[2];
	magni = mag(cp);
	if (magni <= radius)
		return (1);
	return (0);
}

void find_np_square(t_ray *ray, t_square *sq)
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

void compute_color_square(t_ray *ray, t_objects *root, t_square *obj)
{
	ray->red = ray->i * sq_color_red(root, obj);
	ray->green = ray->i * sq_color_green(root, obj);
	ray->blue = ray->i * sq_color_blue(root, obj);
}

int sq_color_red(t_objects *root, t_square *obj)
{
	int color;
	t_light *l;

	l = root->light;
	color = obj->color[0];
	if (root->ambient->i != 0)
		color = color + root->ambient->color[0];
	while (l != NULL) 
	{
		if (l->i != 0)
			color = color + l->color[0];
		l = l->next;
	}
	if (color > 255)
		color = 255;

	return (color);
}

int sq_color_green(t_objects *root, t_square *obj)
{
	int color;
	t_light *l;

	l = root->light;
	color = obj->color[1];
	if (root->ambient->i != 0)
		color = color + root->ambient->color[1];
	while (l != NULL) 
	{
		if (l->i != 0)
			color = color + l->color[1];
		l = l->next;
	}
	if (color > 255)
		color = 255;
	return (color);
}

int sq_color_blue(t_objects *root, t_square *obj)
{
	int color;
	t_light *l;

	l = root->light;
	color = obj->color[2];
	if (root->ambient->i != 0)
		color = color + root->ambient->color[2];
	while (l != NULL) 
	{
		if (l->i != 0)
			color = color + l->color[2];
		l = l->next;
	}
	if (color > 255)
		color = 255;
	return (color);
}

/*int inside_square(t_ray *ray, t_square *sq)
{
	double x;
	double y;
	double sqr_ab;
	double sqr_ad;
	int i;

	i = 0;
	while (i < 3)
	{
		sq->vec_ab[i] = sq->b[i] - sq->a[i];
		sq->vec_ad[i] = sq->d[i] - sq->a[i];
		sq->vec_ap[i] = sq->p[i] - sq->a[i];
		i++;
	}
	sqr_ab = sqrt(dot_prod(sq->vec_ab, sq->vec_ab));
	sqr_ad = sqrt(dot_prod(sq->vec_ad, sq->vec_ad));
	x = (dot_prod(sq->vec_ap, sq->vec_ab) / sqr_ab); 
	y = (dot_prod(sq->vec_ap, sq->vec_ad) / sqr_ad); 
	if (x >= 0 && x <= 1 && y >= 0 && y <= 1)
		return (1);
	return (0);
}*/
