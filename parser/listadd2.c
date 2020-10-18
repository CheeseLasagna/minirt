#include "header.h"

void	lst_addback_light(t_light **root, t_light *nw)
{
	t_light *temp;

	temp = *root;
	if (*root == NULL)
	{
		nw->next = NULL;
		*root = nw;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	nw->next = NULL;
	temp->next = nw;
}

void	lst_addback_camera(t_camera **root, t_camera *nw)
{
	t_camera *temp;

	temp = *root;
	if (*root == NULL)
	{
		nw->next = NULL;
		nw->prev = NULL;
		*root = nw;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	nw->next = NULL;
	nw->prev = temp;
	temp->next = nw;
}

void	lst_addback_ambient(t_objects *root, t_ambient *nw)
{
	if (root->ambient == NULL)
	{
		root->ambient = nw;
		return ;
	}
	else
	{
		write(1, "Error: Ambient lighting can only be set once\n", 45);
		free_root(root);
		exit(EXIT_FAILURE);
	}
}

void	lst_addback_resol(t_objects *root, t_resol *nw)
{
	if (root->resol == NULL)
	{
		root->resol = nw;
		return ;
	}
	else
	{
		write(1, "Error: Resolution can only be set once\n", 39);
		free_root(root);
		exit(EXIT_FAILURE);
	}
}
