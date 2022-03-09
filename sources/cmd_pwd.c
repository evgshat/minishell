#include "../includes/minishell.h"

void	cmd_pwd(void)
{
	char *pwd;

	pwd = malloc(sizeof(char) * PWD_MAX);
	pwd = getcwd(pwd, PWD_MAX);
	if (pwd == NULL)
		exit (1); // ERROR
	printf("%s\n", pwd);
	free (pwd);
}