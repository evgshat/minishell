#include "minishell.h"

void	parser(t_data *data)
{
	data->str = readline("minishell: ");
	data->str = malloc(10000);
	printf("%s", data->str);
}