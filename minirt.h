#ifndef MINIRT_H
# define MINIRT_H

# include "minilibx/mlx.h"
# include "minilibx/mlx_int.h"
# include <X11/X.h>
# include <stdio.h>
# include <math.h>
# include "parser/header.h"
# include <sys/stat.h>

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
	double	viewpoint_w;
	double	viewpoint_h;
	double	d;
}				t_image;

typedef struct	s_ray_data
{
	double	cam[3];
	double	vp[3];
	double	t_min;
	double	t_max;
	double	t1;
	double	t2;
	double	color;
	double	closest_t;
	double	p[3];
	double	n[3];
	double	i;
	double	x;
	double	y;
	double	x1;
	double	y1;
	double	z1;
	int		red;
	int		green;
	int		blue;
}				t_ray;

typedef struct	s_matrix
{
	double	cos_x;
	double	sin_x;
	double	cos_y;
	double	sin_y;
	double	cos_z;
	double	sin_z;
	double	cos_t;
	double	sin_t;
	double	x[3];
	double	y[3];
	double	z[3];
}				t_matrix;

typedef struct {
	int			bfsize;
	int			reserved1;
	int			reserved2;
	int			bfoffbits;
	int			bisize;
	int			width;
	int			height;
	int			compression;
	int			sizeimage;
	int			bixpelspermeter;
	int			biypelspermeter;
	int			biclrused;
	int			biclrimportant;
	int			biplanes;
	int			bibitcount;
	char		type[2];
}				t_bmp;

typedef struct	s_data
{
	t_image		*img;
	t_ray		*ray;
	t_objects	*root;
}				t_data;

/*
** WINDOW IMAGE
*/
void			window_manage(t_objects *root);
void			push_new_img(t_image *img, t_ray *ray, t_objects *root);
void			imgcam(t_image *img, t_ray *ray, t_objects *root);
void			my_mlx_pixel_put(t_image *img, int x, int y, int color);
void			render(t_image *img, t_ray *ray, t_objects *root);
void			viewport_xyz(t_image *img, t_ray *ray, t_objects *root);
void			find_cs(t_matrix *m, t_objects *root);
void			calc_matrix(t_matrix m, t_ray *ray, double *n, double *b);
double			find_width(double deg);
int				close_k(void);

/*
**SPHERE
*/
void			sphere_ray(t_ray *ray, t_objects *root);
void			sphere_closest(t_ray *ray, t_sphere **sph, t_sphere *temp);
void			sphere_intersec(t_ray *ray, t_sphere *sph);
void			find_np_sphere(t_ray *ray, t_sphere *sph);

/*
**PLANE
*/
void			plane_ray(t_ray *ray, t_objects *root);
void			plane_closest(t_ray *ray, t_plane **pl, t_plane *temp);
void			plane_intersec(t_ray *ray, t_plane *pl);
void			find_np_plane(t_ray *ray, t_plane *pl);

/*
**TRIANGLE
*/
void			triangle_ray(t_ray *ray, t_objects *root);
void			triangle_closest(t_ray *ray, t_triangle **tr, t_triangle *temp);
void			find_normal(t_triangle *tr);
void			tplane_intersec(t_ray *ray, t_triangle *tr);
int				inside_triangle(t_ray *ray, t_triangle *tr);
void			find_np_triangle(t_ray *ray, t_triangle *tr);

/*
**SQUARE
*/
void			square_ray(t_ray *ray, t_objects *root);
void			square_closest(t_ray *ray, t_square **sq, t_square *temp);
void			splane_intersec(t_ray *ray, t_square *sq);
int				inside_square(t_ray *ray, t_square *sq);
void			find_np_square(t_ray *ray, t_square *sq);
void			find_vertices(t_ray *ray, t_square *temp);
void			find_vertices2(double magni, double *cp, t_square *temp);
int				cmp(double *a, double *b);
double			orient(t_square *sq, double *a, double *b);

/*
**CYLINDER
*/
void			cylinder_ray(t_ray *ray, t_objects *root);
void			cylinder_closest(t_ray *ray, t_cylinder **cy, t_cylinder *temp);
void			cylinder_intersec(t_ray *ray, t_cylinder *cy);
void			calc_cyl_abc(t_ray *ray, t_cylinder *cy);
int				cylinder_limits(t_ray *ray, t_cylinder *cy);
int				cylinder_limits2(t_ray *ray, t_cylinder *cy);
void			find_np_cylinder(t_ray *ray, t_cylinder *cy);

/*
**COMP
*/
double			dot_prod(double *vec1, double *vec2);
void			cross_prod(double *res, double *vec1, double *vec2);
double			mag(double *vec);

/*
**COLOR
*/
void			compute_lighting(t_objects *root, t_ray *ray);
void			compute_lighting2(double *l, t_light **light, t_ray *ray,
												t_objects *root);
void			compute_color_sphere(t_ray *ray, t_objects *root,
													t_sphere *obj);
int				sph_color_red(t_objects *root, t_sphere *obj);
int				sph_color_green(t_objects *root, t_sphere *obj);
int				sph_color_blue(t_objects *root, t_sphere *obj);
void			compute_color_plane(t_ray *ray, t_objects *root, t_plane *obj);
int				pl_color_red(t_objects *root, t_plane *obj);
int				pl_color_green(t_objects *root, t_plane *obj);
int				pl_color_blue(t_objects *root, t_plane *obj);
void			compute_color_triangle(t_ray *ray, t_objects *root,
													t_triangle *obj);
int				tr_color_red(t_objects *root, t_triangle *obj);
int				tr_color_green(t_objects *root, t_triangle *obj);
int				tr_color_blue(t_objects *root, t_triangle *obj);
void			compute_color_cylinder(t_ray *ray, t_objects *root,
													t_cylinder *obj);
int				cy_color_red(t_objects *root, t_cylinder *obj);
int				cy_color_green(t_objects *root, t_cylinder *obj);
int				cy_color_blue(t_objects *root, t_cylinder *obj);
void			compute_color_square(t_ray *ray, t_objects *root,
													t_square *obj);
int				sq_color_red(t_objects *root, t_square *obj);
int				sq_color_green(t_objects *root, t_square *obj);
int				sq_color_blue(t_objects *root, t_square *obj);

/*
**SHADOW
*/
int				check_shadow(t_ray ray, t_objects *root, double *l);
int				sphere_shadow(t_ray *ray, t_objects *root);
int				plane_shadow(t_ray *ray, t_objects *root);
int				cylinder_shadow(t_ray *ray, t_objects *root);
int				triangle_shadow(t_ray *ray, t_objects *root);
int				square_shadow(t_ray *ray, t_objects *root);

/*
**BMP
*/
void			print_bmp(t_objects *root);
void			save_bmp(t_data *data);
void			bmp_vars_input(t_bmp *bmp, t_data *data);
void			bmp_write(t_bmp bmp, t_data *data, int fd);
void			draw_img(t_data *data, t_bmp *bmp, int fd);

void			calc_angle(double *cos_t, double *sin_t, double *n);
void			initialise_objects(t_objects *root);

#endif
