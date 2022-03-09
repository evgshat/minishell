#include "../../includes/minishell.h"

t_env	*last_elem(t_env *elem)
{
	t_env	*tmp;

	tmp = elem;
	while (elem)
	{
		tmp = elem;
		elem = elem->next;
	}
	return (tmp);
}

void	add_elem_back(t_env **data, t_env *new)
{
	t_env	*tmp;

	if (!*data)
		*data = new;
	else
	{
		tmp = last_elem(*data);
		tmp->next = new;
	}
}

void	copy_env(t_env **data, char **envp)
{
	while (*envp)
	{
		add_elem_back(data, new_env_elem(*envp, 1));
		envp++;
	}
}

void	env_print(t_env *data)
{
	while (data)
	{
		printf("%s=%s\n", data->arg, data->value);
		data = data->next;
	}
}
