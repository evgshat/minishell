#include "minishell.h"

// какая-то тема, что что-то там должно быть в алфавитном порядке

void	cmd_export(char *str, t_env **sh_env)
{
	t_env	*temp;
	char	*new_value;
	char	*new_arg;
	int		len_arg;

	temp = *sh_env;
	new_arg = get_arg(str);
	new_value = get_value(str);
	len_arg = ft_strlen(temp->arg) + 1;
	while (temp)
	{
		if (ft_strncmp(temp->arg, new_arg, len_arg) == 0)
		{
			free(temp->value);
			free(new_arg);
			temp->value = new_value;
			return ;
		}
		temp = temp->next;
	}
	free(new_arg);
	free(new_value);
	add_elem_back(sh_env, new_env_elem(str, 1));
}