#include "minirt.h"

int		main(int argc, char **argv)
{
	t_objects *root;

	arg_check(argc, argv);
	root = (t_objects*)malloc(sizeof(t_objects));
	open_read(argc, argv, root);
	window_manage(root);
	return (0);
}
