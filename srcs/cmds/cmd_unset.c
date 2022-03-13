#include "minishell.h"

static void	free_elem(t_env	*temp)
{
		free(temp->arg);
		free(temp->value);
		free(temp);
}

// static void	cmd_unset_first(t_env	*temp);
// static void	cmd_unset_middle(t_env	*temp);
// static void	cmd_unset_last(t_env	*temp);


void	cmd_unset(char *str, t_env **sh_env)
{
	t_env	*temp;
	t_env	*tmp_prev;
	t_env	*tmp_next;
	int		len_str;

	temp = *sh_env;
	len_str = strlen(str) + 1;
	if ((temp->next) && ft_strncmp(temp->arg, str, len_str) == 0) // first
	{
		*sh_env = (*sh_env)->next;
		free_elem(temp);
		return ;
	}
	tmp_prev = temp;
	temp = temp->next;
	while (temp->next) // middle
	{
		if ((temp->next) && ft_strncmp(temp->arg, str, len_str) == 0)
		{
			tmp_next = temp->next;
			temp->next = tmp_next;
			tmp_prev->next = tmp_next;
			free_elem(temp);
			return ;
		}
		tmp_prev = temp;
		temp = temp->next;
	}
	if ((!temp->next) && ft_strncmp(temp->arg, str, len_str) == 0) // last
	{
		tmp_prev->next = NULL;
		free_elem(temp);
		return ;
	}
}
