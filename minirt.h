#ifndef MINIRT_H
# define MINIRT_H

#include "minilibx/mlx.h"
#include "minilibx/mlx_int.h"
#include <X11/X.h>
#include <stdio.h>
#include <math.h>
#include "parser/header.h"

typedef struct	s_image_data
{
	void	*mlx;
	void	*window;
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	int		color;
	int		img_x;
	int		img_y;
	double		viewpoint_w;
	double		viewpoint_h;
	double		d;
}				t_image;

/*typedef struct	s_square
{
	double a[3];
	double b[3];
	double c[3];
	double n[3];
	double vec_ab[3];
	double vec_ac[3];
	double vec_ap[3];
	double p[3];
	int color[3];
}				t_square;*/

typedef struct	s_ray_data
{
	double cam[3];
	double vp[3];
	double t_min;
	double t_max;
	double t1;
	double t2;
	double color;
	double closest_t;
	double p[3];
	double n[3];
	double i;
	double x;
	double y;
	double x1;
	double y1;
	double z1;
	int red;
	int green;
	int blue;
}				t_ray;	

typedef struct	s_matrix
{
	double	matrix[3][3];
}				t_matrix;

typedef struct	s_data
{
	t_image		*img;
	t_ray		*ray;
	t_objects	*root;
}				t_data;

/*WINDOW IMAGE*/
void	window_manage(t_objects *root);
void push_new_img(t_image *img, t_ray *ray, t_objects *root);
void	imgcam(t_image *img, t_ray *ray, t_objects *root);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	render(t_image *img, t_ray *ray, t_objects *root);
void	viewport_xyz(t_image *img, t_ray *ray, t_objects *root);
void vert_zero(t_square *sq);

/*SPHERE*/
void	sphere_ray(t_ray *ray, t_objects *root);
void	sphere_closest(t_ray *ray, t_sphere **sph, t_sphere *temp);
void	sphere_intersec(t_ray *ray, t_sphere *sph);
void	find_np_sphere(t_ray *ray, t_sphere *sph);

/*PLANE*/
void	plane_ray(t_ray *ray, t_objects *root);
void	plane_closest(t_ray *ray, t_plane **pl, t_plane *temp);
void	plane_intersec(t_ray *ray, t_plane *pl);
void	find_np_plane(t_ray *ray, t_plane *pl);

/*TRIANGLE*/
void	triangle_ray(t_ray *ray, t_objects *root);
void	triangle_closest(t_ray *ray, t_triangle **tr, t_triangle *temp);
void	find_normal(t_triangle *tr);
void	tplane_intersec(t_ray *ray, t_triangle *tr);
int		inside_triangle(t_ray *ray, t_triangle *tr);
void	find_np_triangle(t_ray *ray, t_triangle *tr);

/*SQUARE*/
void		square_ray(t_ray *ray, t_objects *root);
void	square_closest(t_ray *ray, t_square **sq, t_square *temp);
void	splane_intersec(t_ray *ray, t_square *sq);
int		inside_square(t_ray *ray, t_square *sq);
void	find_np_square(t_ray *ray, t_square *sq);
void	find_vertices(t_ray *ray, t_square *temp);
void find_vertices2(double magni, double *cp, t_square *temp);
int	cmp(double *a, double *b);
double	orient(t_square *sq, double *a, double *b);

/*CYLINDER*/
void	cylinder_ray(t_ray *ray, t_objects *root);
void	cylinder_closest(t_ray *ray, t_cylinder **cy, t_cylinder *temp);
void	cylinder_intersec(t_ray *ray, t_cylinder *cy);
void	calc_cyl_abc(t_ray *ray, t_cylinder *cy);
int		cylinder_limits(t_ray *ray, t_cylinder *cy);
int		cylinder_limits2(t_ray *ray, t_cylinder *cy);
void	find_np_cylinder(t_ray *ray, t_cylinder *cy);

/*COMP*/
double	dot_prod(double *vec1, double *vec2);
void	cross_prod(double *res, double *vec1, double *vec2);
double mag(double *vec);

/*COLOR*/
void compute_lighting(t_objects *root, t_ray *ray);
void compute_color_sphere(t_ray *ray, t_objects *root, t_sphere *obj);
int	sph_color_red(t_objects *root, t_sphere *obj);
int	sph_color_green(t_objects *root, t_sphere *obj);
int	sph_color_blue(t_objects *root, t_sphere *obj);
void compute_color_plane(t_ray *ray, t_objects *root, t_plane *obj);
int	pl_color_red(t_objects *root, t_plane *obj);
int	pl_color_green(t_objects *root, t_plane *obj);
int	pl_color_blue(t_objects *root, t_plane *obj);
void compute_color_triangle(t_ray *ray, t_objects *root, t_triangle *obj);
int	tr_color_red(t_objects *root, t_triangle *obj);
int	tr_color_green(t_objects *root, t_triangle *obj);
int	tr_color_blue(t_objects *root, t_triangle *obj);
void compute_color_cylinder(t_ray *ray, t_objects *root, t_cylinder *obj);
int	cy_color_red(t_objects *root, t_cylinder *obj);
int	cy_color_green(t_objects *root, t_cylinder *obj);
int	cy_color_blue(t_objects *root, t_cylinder *obj);
void compute_color_square(t_ray *ray, t_objects *root, t_square *obj);
int	sq_color_red(t_objects *root, t_square *obj);
int	sq_color_green(t_objects *root, t_square *obj);
int	sq_color_blue(t_objects *root, t_square *obj);

/*SHADOW*/
int check_shadow(t_ray ray, t_objects *root, double *l);
int sphere_shadow(t_ray *ray, t_objects *root);
int plane_shadow(t_ray *ray, t_objects *root);
int cylinder_shadow(t_ray *ray, t_objects *root);
int triangle_shadow(t_ray *ray, t_objects *root);
int square_shadow(t_ray *ray, t_objects *root);

/*MATRIX*/
void matrix_x(double cos_t, double sin_t, t_matrix *mat);
void matrix_x_rev(double cos_t, double sin_t, t_matrix *mat);
void matrix_y(double cos_t, double sin_t, t_matrix *mat);
void matrix_y_rev(double cos_t, double sin_t, t_matrix *mat);
void matrix_z(double cos_t, double sin_t, t_matrix *mat);
void matrix_z_rev(double cos_t, double sin_t, t_matrix *mat);
void  matrix_multiply(t_matrix *res, t_matrix a, t_matrix b);
void   vector_matrix_multiply(t_matrix m, t_ray *ray);


void calc_angle(double *cos_t, double *sin_t, double *n);

#endif
