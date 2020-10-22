#include "minirt.h"

void render(t_image *img, t_ray *ray, t_objects *root)
{
	root->square->b[0] = 0;
	root->square->b[1] = 0;
	root->square->b[2] = 0;
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

void viewport_xyz(t_image *img, t_ray *ray, t_objects *root)
{
	double magni;
	double cos_t;
	double sin_t;
	double *n;
//	double w[3];
	double x1;
	double y1;
	double z1;
	t_matrix pre;
	t_matrix final;
	t_matrix x;
	t_matrix y;
	t_matrix z;

	n = root->camera->n;
	ray->vp[0] = ray->x * img->viewpoint_w / img->img_x;
	ray->vp[1] = ray->y * img->viewpoint_h / img->img_y;
	ray->vp[2] = img->d;
/*	magni = mag(ray->vp);
	ray->vp[0] = ray->vp[0] / magni;
	ray->vp[1] = ray->vp[1] / magni;
	ray->vp[2] = ray->vp[2] / magni;*/
	if (n[0] == 0 && n[1] == 0 && n[2] == 1)
		return;
	x1 = ray->vp[0];
	y1 = ray->vp[1];
	z1 = ray->vp[2];
	calc_angle(&cos_t, &sin_t, root->camera->n);
	/*if (n[0] > 0)
	{
		ray->vp[0] = x1 * cos_t + z1 * sin_t;
		ray->vp[2] = -(x1 * sin_t) + z1 * cos_t;
	}
	else if (n[0] < 0)
	{
		ray->vp[0] = x1 * cos_t - z1 * sin_t;
		ray->vp[2] = +(x1 * sin_t) + z1 * cos_t;
	}
	
	x1 = ray->vp[0];
	y1 = ray->vp[1];
	z1 = ray->vp[2];
	if (n[1] > 0)
	{
		ray->vp[1] = y1 * cos_t + z1 * sin_t;
		ray->vp[2] = -y1 * sin_t + z1 * cos_t;
	}
	else if (n[1] < 0)
	{
		ray->vp[1] = y1 * cos_t - z1 * sin_t;
		ray->vp[2] = y1 * sin_t + z1 * cos_t;
	}*/
	/*x1 = ray->vp[0];
	y1 = ray->vp[1];
	z1 = ray->vp[2];
	if (n[2] == 0)
	{
		ray->vp[0] = x1 * cos_t - y1 * sin_t;
		ray->vp[1] = x1 * sin_t + y1 * cos_t;
	}*/
	x = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	y = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	z = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	if (n[1] >= 0)
		matrix_x(cos_t, sin_t, &x);	
	else if (n[1] < 0)
		matrix_x_rev(cos_t, sin_t, &x);	
	if (n[0] >= 0)
		matrix_y(cos_t, sin_t, &y);	
	else if (n[0] < 0)
		matrix_y_rev(cos_t, sin_t, &y);	
	if (n[0] > 0 && n[1] == 0 && n[2] == 0)
		matrix_z(cos_t, sin_t, &z);	
	else if (n[0] < 0 && n[1] == 0 && n[2] == 0)
		matrix_z_rev(cos_t, sin_t, &z);	
	matrix_multiply(&pre, x, y);
	matrix_multiply(&final, pre, z);
	vector_matrix_multiply(final, ray);
}

void calc_angle(double *cos_t, double *sin_t, double *n)
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

void matrix_x(double cos_t, double sin_t, t_matrix *mat)
{
	//*mat = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	mat->matrix[1][1] = cos_t;
	mat->matrix[1][2] = -sin_t;
	mat->matrix[2][1] = sin_t;
	mat->matrix[2][2] = cos_t;
}

void matrix_y(double cos_t, double sin_t, t_matrix *mat)
{
	//*mat = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	mat->matrix[0][0] = cos_t;
	mat->matrix[0][2] = -sin_t;
	mat->matrix[2][0] = sin_t;
	mat->matrix[2][2] = cos_t;
}

void matrix_x_rev(double cos_t, double sin_t, t_matrix *mat)
{
	//*mat = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	mat->matrix[1][1] = cos_t;
	mat->matrix[1][2] = sin_t;
	mat->matrix[2][1] = -sin_t;
	mat->matrix[2][2] = cos_t;
}

void matrix_y_rev(double cos_t, double sin_t, t_matrix *mat)
{
	//*mat = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	mat->matrix[0][0] = cos_t;
	mat->matrix[0][2] = sin_t;
	mat->matrix[2][0] = -sin_t;
	mat->matrix[2][2] = cos_t;
}

void matrix_z(double cos_t, double sin_t, t_matrix *mat)
{
	//*mat = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	mat->matrix[0][0] = cos_t;
	mat->matrix[0][1] = -sin_t;
	mat->matrix[1][0] = sin_t;
	mat->matrix[1][1] = cos_t;
}

void matrix_z_rev(double cos_t, double sin_t, t_matrix *mat)
{
	//*mat = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	mat->matrix[0][0] = cos_t;
	mat->matrix[0][1] = sin_t;
	mat->matrix[1][0] = -sin_t;
	mat->matrix[1][1] = cos_t;
}

void		matrix_multiply(t_matrix *res, t_matrix a, t_matrix b)
{
	int			i;
	int			j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			res->matrix[i][j] = a.matrix[i][0] * b.matrix[0][j] +
				a.matrix[i][1] * b.matrix[1][j] +
				a.matrix[i][2] * b.matrix[2][j];
		}
	}
}

void			vector_matrix_multiply(t_matrix m, t_ray *ray)
{
	t_ray	pre;

	pre.x1 = ray->vp[0];
	pre.y1 = ray->vp[1];
	pre.z1 = ray->vp[2];
	ray->vp[0] = pre.x1 * m.matrix[0][0] + pre.y1 * m.matrix[1][0] +
				pre.z1 * m.matrix[2][0];
	ray->vp[1] = pre.x1 * m.matrix[0][1] + pre.y1 * m.matrix[1][1] +
				pre.z1 * m.matrix[2][1];
	ray->vp[2] = pre.x1 * m.matrix[0][2] + pre.y1 * m.matrix[1][2] +
				pre.z1 * m.matrix[2][2];
}
