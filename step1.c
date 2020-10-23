#include "minirt.h"

void	render(t_image *img, t_ray *ray, t_objects *root)
{
	while (ray->x < img->img_x / 2)
	{
		while (ray->y < img->img_y / 2)
		{
			ray->closest_t = ray->t_max;
			ray->color = 0;
			viewport_xyz(img, ray, root);
			sphere_ray(ray, root);
			plane_ray(ray, root);
			triangle_ray(ray, root);
			cylinder_ray(ray, root);
			square_ray(ray, root);
			my_mlx_pixel_put(img, ray->x, ray->y, ray->color);
			ray->y++;
		}
		ray->x++;
		ray->y = img->img_y / -2;
	}
}

void	viewport_xyz(t_image *img, t_ray *ray, t_objects *root)
{
	double		*n;
	double		b[3];
	t_matrix	m;

	n = root->camera->n;
	ray->vp[0] = ray->x * img->viewpoint_w / img->img_x;
	ray->vp[1] = ray->y * img->viewpoint_h / img->img_y;
	ray->vp[2] = img->d;
	if (n[0] == 0 && n[1] == 0 && n[2] == 1)
		return ;
	b[0] = ray->vp[0];
	b[1] = ray->vp[1];
	b[2] = ray->vp[2];
	find_cs(&m, root);
	calc_matrix(m, ray, n, b);
}

void	calc_matrix(t_matrix m, t_ray *ray, double *n, double *b)
{
	if (n[1] > 0)
	{
		ray->vp[1] = b[1] * m.cos_x + b[2] * m.sin_x;
		ray->vp[2] = -b[1] * m.sin_x + b[2] * m.cos_x;
	}
	else if (n[1] < 0)
	{
		ray->vp[1] = b[1] * m.cos_x - b[2] * m.sin_x;
		ray->vp[2] = b[1] * m.sin_x + b[2] * m.cos_x;
	}
	b[0] = ray->vp[0];
	b[1] = ray->vp[1];
	b[2] = ray->vp[2];
	if (n[0] > 0 || (n[0] == 0 && n[2] != 0 && n[1] == 0))
	{
		ray->vp[0] = b[0] * m.cos_y + b[2] * m.sin_y;
		ray->vp[2] = -b[0] * m.sin_y + b[2] * m.cos_y;
	}
	else if (n[0] < 0)
	{
		ray->vp[0] = b[0] * m.cos_y - b[2] * m.sin_y;
		ray->vp[2] = b[0] * m.sin_y + b[2] * m.cos_y;
	}
}

void	find_cs(t_matrix *m, t_objects *root)
{
	m->y[0] = root->camera->n[0];
	m->y[1] = 0;
	m->y[2] = root->camera->n[2];
	m->x[0] = 0;
	m->x[1] = root->camera->n[1];
	m->x[2] = root->camera->n[2];
	m->z[0] = root->camera->n[0];
	m->z[1] = root->camera->n[1];
	m->z[2] = 0;
	calc_angle(&(m->cos_x), &(m->sin_x), m->x);
	calc_angle(&(m->cos_y), &(m->sin_y), m->y);
	calc_angle(&(m->cos_z), &(m->sin_z), m->z);
}

void	calc_angle(double *cos_t, double *sin_t, double *n)
{
	double def[3];
	double vec[3];

	def[0] = 0;
	def[1] = 0;
	def[2] = 1;
	*cos_t = dot_prod(def, n) / (mag(def) * mag(n));
	cross_prod(vec, def, n);
	*sin_t = mag(vec) / (mag(def) * mag(n));
}
