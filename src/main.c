/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:49:16 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:49:19 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	initialise_objects(t_objects *root)
{
	root->sphere = NULL;
	root->plane = NULL;
	root->square = NULL;
	root->cylinder = NULL;
	root->triangle = NULL;
	root->light = NULL;
	root->camera = NULL;
	root->ambient = NULL;
	root->resol = NULL;
}

int		main(int argc, char **argv)
{
	int			check;
	t_objects	*root;

	check = arg_check(argc, argv);
	if ((root = (t_objects*)malloc(sizeof(t_objects))) == NULL)
	{
		write(1, "Error\nno memory\n", 16);
		exit(0);
	}
	initialise_objects(root);
	open_read(argc, argv, root);
	if (!check)
		window_manage(root);
	else
		print_bmp(root);
	free_root(root);
	return (0);
}
