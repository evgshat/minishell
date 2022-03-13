#include "minishell.h"

void	error_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}
