#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	init_env(&data);
	parser(&data);
}