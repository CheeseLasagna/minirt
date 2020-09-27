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
	int		res_x;
	int		res_y;
	int		viewpoint_w;
	int		viewpoint_h;
	int		d;
}				t_image_data;

typedef struct	s_sphere_data
{
	int		x;
	int		y;
	int		z;
	int		radius;
	int		red;
	int		green;
	int		blue;
}				t_sphere_data;

typedef struct	s_ray_data
{
	int cam_x;
	int cam_y;
	int cam_z;
	int vp_intersec_x;
	int vp_intersec_y;
	int vp_intersec_z;
	int t1;
	int t2;
	
}				t_ray_data;	

void	my_mlx_pixel_put(t_image_data *ptr, int x, int y, int color);
void	basic(t_image_data *ptr, t_ray_data *ptrray);
void	canvas_to_viewport(t_image_data *ptr, t_ray_data *ptrray, int x, int y);
int		trace_ray(t_ray_data *ptr, int t_min, int t_max);
void	intersect_sphere(t_ray_data *ptrray, t_sphere_data *ptrsphere);

#endif
