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
	double		x;
	double		y;
	double		z;
	double		radius;
	int			color[3];		
}				t_sphere;

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
	double closest_t;
}				t_ray;	

typedef struct	s_objects
{
	t_sphere *ptrsph;
}				t_objects;

void	my_mlx_pixel_put(t_image *ptr, int x, int y, int color);
void	basic(t_image *ptr, t_ray *ray);
void	viewport_xyz(t_image *ptr, t_ray *ray, int x, int y);
int		sphere_ray(t_ray *ray, t_sphere *sph);
void	sphere_intersec(t_ray *ray, t_sphere *sph);

#endif
