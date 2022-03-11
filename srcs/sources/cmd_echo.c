#include "../../includes/minishell.h"

void	cmd_echo(char **str)
{
	if (*(str + 1) && *(str + 2))
	{
		if (ft_strncmp(*(str + 1), "-n", 3) == 0)
				printf("%s\n", *(str + 2));
	}
	else if (*(str + 1))
		printf("%s\n", *(str + 1));
}

// check -n