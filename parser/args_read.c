#include "header.h"

int	arg_check(int argc, char **argv)
{
	int i;
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
	i = ft_strlen(argv[1]);
	if (i < 4 || argv[1][i] != '\0' || argv[1][i - 1] != 't'
		|| argv[1][i - 2] != 'r' || argv[1][i - 3] != '.')
	{
		write(1, "wrong file type\n", 16);
		exit(0);
	}
	if (argc == 3 && (ft_memcmp(argv[2], "--save", 7))) 
	{
		write(1, "wrong second argument\n", 22);
		exit(0);
	}
	if (argc == 2)
		return (0);
	return (1);
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