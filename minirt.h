#ifndef MINIRT_H
# define MINIRT_H

#include "minilibx/mlx.h"
#include "minilibx/mlx_int.h"
#include <X11/X.h>
#include <stdio.h>
#include <math.h>

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
	int		d;
}				t_image;

typedef struct	s_sphere
{
	double		c[3];
	double		radius;
	int			color[3];		
}				t_sphere;

typedef struct	t_plane_data
{
	double		x;
	double		y;
	double		z;
	double		n[3];
	int			color[3];
}				t_plane;

typedef struct	s_triangle
{
	double a[3];
	double b[3];
	double c[3];
	double n[3];
	double vec_ab[3];
	double vec_bc[3];
	double vec_ca[3];
	double vec_ap[3];
	double vec_bp[3];
	double vec_cp[3];
	double p[3];
	int color[3];
}				t_triangle;

typedef struct	s_square
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
}				t_square;

typedef struct	s_ray_data
{
	double cam_x;
	double cam_y;
	double cam_z;
	double vp_x;
	double vp_y;
	double vp_z;
	double t_min;
	double t_max;
	double t1;
	double t2;
	double color;
	double closest_t;
	double p[3];
	double n[3];
	int red;
	int green;
	int blue;
}				t_ray;	

typedef struct	s_cylinder
{
	double c[3];
	double radius;
	int color[3];
}				t_cylinder;	

typedef struct	s_objects
{
	t_sphere *ptrsph;
}				t_objects;

typedef struct s_light
{
	double i;
	double amb_i;
	double point_i;
	double osel[3];
	double baran[3];
	double pos[3];
	int final[3];
}				t_light;

void	my_mlx_pixel_put(t_image *ptr, int x, int y, int color);
void	basic(t_image *ptr, t_ray *ray);
void	viewport_xyz(t_image *ptr, t_ray *ray, int x, int y);

void		sphere_ray(t_ray *ray, t_sphere *sph, t_light *light);
void	sphere_intersec(t_ray *ray, t_sphere *sph);
void	find_np_sphere(t_ray *ray, t_sphere *sph);

void		plane_ray(t_ray *ray, t_plane *pl, t_light *light);
void	plane_intersec(t_ray *ray, t_plane *pl);
void	find_np_plane(t_ray *ray, t_plane *pl);

void		triangle_ray(t_ray *ray, t_triangle *tr, t_light *light);
void	find_normal(t_triangle *tr);
void	tplane_intersec(t_ray *ray, t_triangle *tr);
int		inside_triangle(t_ray *ray, t_triangle *tr);
void	find_np_triangle(t_ray *ray, t_triangle *tr);

int		square_ray(t_ray *ray, t_square *sq);
void	splane_intersec(t_ray *ray, t_square *sq);
int		inside_square(t_ray *ray, t_square *sq);

int		cylinder_ray(t_ray *ray, t_cylinder *cy);
void	cylinder_intersec(t_ray *ray, t_cylinder *cy);

double	dot_prod(double *vec1, double *vec2);
void	cross_prod(double *res, double *vec1, double *vec2);

void compute_lighting(t_light *light, t_ray *ray);
void compute_color_sphere(t_ray *ray, t_light *light, t_sphere *obj);
void compute_color_plane(t_ray *ray, t_light *light, t_plane *obj);
void compute_color_triangle(t_ray *ray, t_light *light, t_triangle *obj);
double mag(double *vec);

#endif
