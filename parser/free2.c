#include "header.h"

void	free_plane(t_plane *root)
{
	t_plane *temp;

	temp = root;
	while (root != NULL)
	{
		root = root->next;
		free(temp);
		temp = root;
	}
}

void	free_sphere(t_sphere *root)
{
	t_sphere *temp;

	temp = root;
	while (root != NULL)
	{
		root = root->next;
		free(temp);
		temp = root;
	}
}

void	free_square(t_square *root)
{
	t_square *temp;

	temp = root;
	while (root != NULL)
	{
		root = root->next;
		free(temp);
		temp = root;
	}
}

void	free_cylinder(t_cylinder *root)
{
	t_cylinder *temp;

	temp = root;
	while (root != NULL)
	{
		root = root->next;
		free(temp);
		temp = root;
	}
}

void	free_triangle(t_triangle *root)
{
	t_triangle *temp;

	temp = root;
	while (root != NULL)
	{
		root = root->next;
		free(temp);
		temp = root;
	}
}
