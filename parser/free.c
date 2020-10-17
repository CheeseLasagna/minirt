#include "header.h"

void	free_root(t_objects *root)
{
	free_camera(root->camera);
	free_ambient(root->ambient);
	free_resol(root->resol);
	free_light(root->light);
	free_plane(root->plane);
	free_sphere(root->sphere);
	free_triangle(root->triangle);
	free_cylinder(root->cylinder);
	free_square(root->square);
	if (root != NULL)
		free(root);
}

void	free_camera(t_camera *root)
{
	t_camera *temp;

	temp = root;
	while (root != NULL)
	{
		root = root->next;
		free(temp);
		temp = root;
	}
}

void	free_resol(t_resol *root)
{
	if (root != NULL)
		free(root);
}

void	free_ambient(t_ambient *root)
{
	if (root != NULL)
		free(root);
}

void	free_light(t_light *root)
{
	t_light *temp;

	temp = root;
	while (root != NULL)
	{
		root = root->next;
		free(temp);
		temp = root;
	}
}
