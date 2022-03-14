#include "minishell.h"

void	cmd_echo_for_redirect(char **name_cmd)
{
	if (ft_strncmp(*(name_cmd - 2), "echo", 5) == 0)
        printf("%s\n", *(name_cmd - 1));
    else if (ft_strncmp(*(name_cmd - 3), "echo", 5) == 0)
	{
		if (ft_strncmp(*(name_cmd - 1), "-n", 3) == 0)
				printf("%s\n", *(name_cmd - 2));
	}
}
void	cmd_echo(char **str)
{
	if (*(str + 1) && *(str + 2))
	{
		if (ft_strncmp(*(str + 1), "-n", 3) == 0)
				printf("%s\n", *(str + 2));
	}
	if (*(str + 1))
		printf("%s\n", *(str + 1));
}

// check -n