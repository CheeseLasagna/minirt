#include "header.h"

void	arg_check(int argc, char **argv)
{
	if (argc < 2)
	{
		write(1, "not enough arguments\n", 21);
		exit(EXIT_FAILURE);
	}
	if (argc > 3)
	{
		write(1, "too many arguments\n", 19);
		exit(EXIT_FAILURE);
	}
}

void	open_read(int argc, char **argv, t_objects *root)
{
	char	*line;
	int		i;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while ((i = get_next_line(fd, &line)))
	{
		parse_line(line, root);
		free(line);
	}
	free(line);
	if (root->resol == NULL)
	{
		write(1, "error: Resolution not set\n", 26);
		free_root(root);
		exit(EXIT_FAILURE) ;
	}
	if (root->camera == NULL)
	{
		write(1, "error: camera not set\n", 22);
		free_root(root);
		exit(EXIT_FAILURE) ;
	}
//	print_stuff(root);
//	free_root(root);
}