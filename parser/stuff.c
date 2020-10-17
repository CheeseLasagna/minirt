#include "header.h"
#include <stdio.h>

void	print_stuff(t_objects *root)
{
	t_plane		*pl;
	t_sphere	*sph;
	t_square	*sq;
	t_cylinder	*cy;
	t_triangle	*tr;
	t_light		*l;
	t_camera	*cam;
	t_ambient	*amb;
	t_resol		*res;

	pl = root->plane;
	sph = root->sphere;
	sq = root->square;
	cy = root->cylinder;
	tr = root->triangle;
	l = root->light;
	cam = root->camera;
	amb = root->ambient;
	res = root->resol;
	printf("PLANE");
	while (pl != NULL)
	{
		printf("\nNEW ELEMENT\n\n");
		printf("c[0] = %f\n", pl->c[0]);
		printf("c[1] = %f\n", pl->c[1]);
		printf("c[2] = %f\n", pl->c[2]);
		printf("n[0] = %f\n", pl->n[0]);
		printf("n[1] = %f\n", pl->n[1]);
		printf("n[2] = %f\n", pl->n[2]);
		printf("color[0] = %d\n", pl->color[0]);
		printf("color[1] = %d\n", pl->color[1]);
		printf("color[2] = %d\n", pl->color[2]);
		printf("\n");
		pl = pl->next;
	}
	printf("SPHERE");
	while (sph != NULL)
	{
		printf("\nNEW ELEMENT\n\n");
		printf("c[0] = %f\n", sph->c[0]);
		printf("c[1] = %f\n", sph->c[1]);
		printf("c[2] = %f\n", sph->c[2]);
		printf("radius = %f\n", sph->radius);
		printf("color[0] = %d\n", sph->color[0]);
		printf("color[1] = %d\n", sph->color[1]);
		printf("color[2] = %d\n", sph->color[2]);
		printf("\n");
		sph = sph->next;
	}
	printf("SQUARE");
	while (sq != NULL)
	{
		printf("\nNEW ELEMENT\n\n");
		printf("c[0] = %f\n", sq->c[0]);
		printf("c[1] = %f\n", sq->c[1]);
		printf("c[2] = %f\n", sq->c[2]);
		printf("n[0] = %f\n", sq->n[0]);
		printf("n[1] = %f\n", sq->n[1]);
		printf("n[2] = %f\n", sq->n[2]);
		printf("side = %f\n", sq->side);
		printf("color[0] = %d\n", sq->color[0]);
		printf("color[1] = %d\n", sq->color[1]);
		printf("color[2] = %d\n", sq->color[2]);
		printf("\n");
		sq = sq->next;
	}
	printf("CYLINDER");
	while (cy != NULL)
	{
		printf("\nNEW ELEMENT\n\n");
		printf("c[0] = %f\n", cy->c[0]);
		printf("c[1] = %f\n", cy->c[1]);
		printf("c[2] = %f\n", cy->c[2]);
		printf("n[0] = %f\n", cy->n[0]);
		printf("n[1] = %f\n", cy->n[1]);
		printf("n[2] = %f\n", cy->n[2]);
		printf("diameter = %f\n", cy->diameter);
		printf("height = %f\n", cy->height);
		printf("color[0] = %d\n", cy->color[0]);
		printf("color[1] = %d\n", cy->color[1]);
		printf("color[2] = %d\n", cy->color[2]);
		printf("\n");
		cy = cy->next;
	}
	printf("TRIANGLE");
	while (tr != NULL)
	{
		printf("\nNEW ELEMENT\n\n");
		printf("a[0] = %f\n", tr->a[0]);
		printf("a[1] = %f\n", tr->a[1]);
		printf("a[2] = %f\n", tr->a[2]);
		printf("b[0] = %f\n", tr->b[0]);
		printf("b[1] = %f\n", tr->b[1]);
		printf("b[2] = %f\n", tr->b[2]);
		printf("c[0] = %f\n", tr->c[0]);
		printf("c[1] = %f\n", tr->c[1]);
		printf("c[2] = %f\n", tr->c[2]);
		printf("color[0] = %d\n", tr->color[0]);
		printf("color[1] = %d\n", tr->color[1]);
		printf("color[2] = %d\n", tr->color[2]);
		printf("\n");
		tr = tr->next;
	}
	printf("LIGHT");
	while (l != NULL)
	{
		printf("\nNEW ELEMENT\n\n");
		printf("c[0] = %f\n", l->c[0]);
		printf("c[1] = %f\n", l->c[1]);
		printf("c[2] = %f\n", l->c[2]);
		printf("brightness = %f\n", l->i);
		printf("color[0] = %d\n", l->color[0]);
		printf("color[1] = %d\n", l->color[1]);
		printf("color[2] = %d\n", l->color[2]);
		printf("\n");
		l = l->next;
	}
	printf("CAMERA");
	while (cam != NULL)
	{
		printf("\nNEW ELEMENT\n\n");
		printf("c[0] = %f\n", cam->c[0]);
		printf("c[1] = %f\n", cam->c[1]);
		printf("c[2] = %f\n", cam->c[2]);
		printf("n[0] = %f\n", cam->n[0]);
		printf("n[1] = %f\n", cam->n[1]);
		printf("n[2] = %f\n", cam->n[2]);
		printf("fov = %d\n", cam->fov);
		printf("\n");
		cam = cam->next;
	}
	printf("AMBIENT");
	if (amb != NULL)
	{
		printf("\nNEW ELEMENT\n\n");
		printf("brightness = %f\n", amb->i);
		printf("color[0] = %d\n", amb->color[0]);
		printf("color[1] = %d\n", amb->color[1]);
		printf("color[2] = %d\n", amb->color[2]);
		printf("\n");
	}
	printf("RESOLUTION");
	if (res != NULL)
	{
		printf("\nNEW ELEMENT\n\n");
		printf("r[0] = %d\n", res->r[0]);
		printf("r[1] = %d\n", res->r[1]);
		printf("\n");
	}
}
