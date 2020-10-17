#include "header.h"

void	parse_camera(char *line, t_objects *root)
{
	t_camera *cam;

	cam = (t_camera*)malloc(sizeof(t_camera));
	if (cam == NULL)
	{
		write(1, "no memory\n", 10);
		free_root(root);
		exit(EXIT_FAILURE);
	}
	if ((fill_camera(line, cam)) == -1)
	{
		write(1, "error in arguments\n", 19);
		free_root(root);
		exit(EXIT_FAILURE);
	}
	lst_addback_camera(&(root->camera), cam);
}

int		fill_camera(char *line, t_camera *cam)
{
	line = line + 1;
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((coordinates(&line, cam->c)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((direction(&line, cam->n)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((fov(&line, &(cam->fov))) == -1)
		return (-1);
	skip_space(&line);
	if (*line != '\0')
		return (-1);
	return (1);
}

void	parse_ambient(char *line, t_objects *root)
{
	t_ambient *amb;

	amb = (t_ambient*)malloc(sizeof(t_ambient));
	if (amb == NULL)
	{
		write(1, "no memory\n", 10);
		free_root(root);
		exit(EXIT_FAILURE);
	}
	if ((fill_ambient(line, amb)) == -1)
	{
		write(1, "error in arguments\n", 19);
		free_root(root);
		exit(EXIT_FAILURE);
	}
	lst_addback_ambient(root, amb);
}

int		fill_ambient(char *line, t_ambient *amb)
{
	line = line + 1;
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((brightness(&line, &(amb->i))) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((color(&line, amb->color)) == -1)
		return (-1);
	skip_space(&line);
	if (*line != '\0')
		return (-1);
	return (1);
}

int		fov(char **line, int *fov)
{
	*fov = atoi_rt(line);
	if (*fov < 0 || *fov > 180)
		return (-1);
	return (1);
}
