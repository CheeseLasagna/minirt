#ifndef HEADER_H
# define HEADER_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get/get_next_line.h"
# include <stdio.h>

typedef struct	s_plane
{
	double			c[3];
	double			n[3];
	int				color[3];
	struct s_plane	*next;
}				t_plane;

typedef struct	s_sphere
{
	double			c[3];
	double			diam;
	int				color[3];
	struct s_sphere	*next;
}				t_sphere;

typedef struct	s_square
{
	double			c[3];
	double			n[3];
	double			side;
	int				color[3];
	struct s_square	*next;
}				t_square;

typedef struct	s_cylinder
{
	double				c[3];
	double				n[3];
	double				diam;
	double				height;
	int					color[3];
	double				a;
	double				b;
	double				d;
	double				m;
	double				p[3];
	struct s_cylinder	*next;
}				t_cylinder;

typedef struct	s_triangle
{
	double				a[3];
	double				b[3];
	double				c[3];
	double				n[3];
	double				vec_ab[3];
	double				vec_bc[3];
	double				vec_ca[3];
	double				vec_ap[3];
	double				vec_bp[3];
	double				vec_cp[3];
	double				p[3];
	int					color[3];
	struct s_triangle	*next;
}				t_triangle;

typedef struct	s_light
{
	double			c[3];
	double			i;
	int				color[3];
	struct s_light	*next;
}				t_light;

typedef struct	s_camera
{
	double				c[3];
	double				n[3];
	int					fov;
	struct s_camera		*prev;
	struct s_camera		*next;
}				t_camera;

typedef struct	s_ambient
{
	double	i;
	int		color[3];
}				t_ambient;

typedef struct	s_resol
{
	int	r[2];
}				t_resol;

typedef struct	s_objects
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_square	*square;
	t_cylinder	*cylinder;
	t_triangle	*triangle;
	t_light		*light;
	t_camera	*camera;
	t_ambient	*ambient;
	t_resol		*resol;
}				t_objects;

void			arg_check(int argc, char **argv);
void			open_read(int argc, char **argv, t_objects *root);
void			parse_line(char *line, t_objects *root);
void			parse_line2(t_objects *root);
void			print_stuff(t_objects *root);

/*CAMERA*/
void			parse_camera(char *line, t_objects *root);
int				fill_camera(char *line, t_camera *cam);

/*AMBIENT*/
void			parse_ambient(char *line, t_objects *root);
int				fill_ambient(char *line, t_ambient *amb);

/*RESOLUTION*/
void			parse_resol(char *line, t_objects *root);
int				fill_resol(char *line, t_resol *res);

/*LIGHT*/
void			parse_light(char *line, t_objects *root);
int				fill_light(char *line, t_light *l);

/*PLANE*/
void			parse_plane(char *line, t_objects *root);
int				fill_plane(char *line, t_plane *pl);

/*SPHERE*/
void			parse_sphere(char *line, t_objects *root);
int				fill_sphere(char *line, t_sphere *sph);

/*SQUARE*/
void			parse_square(char *line, t_objects *root);
int				fill_square(char *line, t_square *sq);

/*CYLINDER*/
void			parse_cylinder(char *line, t_objects *root);
int				fill_cylinder(char *line, t_cylinder *cy);

/*TRIANGLE*/
void			parse_triangle(char *line, t_objects *root);
int				fill_triangle(char *line, t_triangle *tr);

/*ARGUMENTS*/
int				skip_space(char **line);
int				coordinates(char **line, double *c);
int				direction(char **line, double *n);
int				color(char **line, int *color);
void			side(char **line, double *r);
int				brightness(char **line, double *i);
int				fov(char **line, int *fov);
int				resol(char **line, int *r);

/*CONVERTER*/
int				atoi_rt(char **line);
double			atoi_doub_rt(char **line);
double			atoi_doub_rt2(char **line, double number);

/*FREE*/
void			free_root(t_objects *root);
void			free_plane(t_plane *root);
void			free_sphere(t_sphere *root);
void			free_square(t_square *root);
void			free_cylinder(t_cylinder *root);
void			free_triangle(t_triangle *root);
void			free_light(t_light *root);
void			free_camera(t_camera *root);
void			free_ambient(t_ambient *root);
void			free_resol(t_resol *root);

/*LIST MANAGEMENT*/
void			lst_addback_plane(t_plane **root, t_plane *nw);
void			lst_addback_sphere(t_sphere **root, t_sphere *nw);
void			lst_addback_square(t_square **root, t_square *nw);
void			lst_addback_cylinder(t_cylinder **root, t_cylinder *nw);
void			lst_addback_triangle(t_triangle **root, t_triangle *nw);
void			lst_addback_light(t_light **root, t_light *nw);
void			lst_addback_camera(t_camera **root, t_camera *nw);
void			lst_addback_ambient(t_objects *root, t_ambient *nw);
void			lst_addback_resol(t_objects *root, t_resol *nw);

#endif
