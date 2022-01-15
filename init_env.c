#include "minishell.h"

void init_env(t_data *data)
{
	tcgetattr(STDIN_FILENO, data->old_bash);
}