#include "minishell.h"

void	cmd_echo(char *flag, char *str)
{
	if (flag != NULL)
	{
		if (ft_strncmp(flag, "-n", 3) == 0)
			printf("%s", str);
	}
	else
	{
		printf("%s", str);
		printf("\n");
	}
}

// я хз