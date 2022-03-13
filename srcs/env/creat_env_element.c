#include "minishell.h"

static size_t	find_equal(char *str)
{
	size_t	i;

	i = 0;
	if (*str)
		while (str[i] && str[i] != '=')
			i++;
	return (i);
}

char	*get_arg(char *str)
{
	char	*arg;
	size_t	equal;
	size_t	i;

	i = -1;
	equal = find_equal(str);
	arg = (char *)malloc(equal + 1);
	if (!arg)
		exit(2);
	while (++i < equal)
		arg[i] = str[i];
	arg[i] = '\0';
	return (arg);
}

char	*get_value(char *str)
{
	char	*value;
	size_t	equal;
	size_t	i;

	i = 0;
	equal = find_equal(str) + 1;
	value = (char *)malloc(ft_strlen(str) - equal + 1);
	if (!value)
		exit(2);
	while (str[equal + i])
	{
		value[i] = str[equal + i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

t_env *new_env_elem(char *str, int v)
{
	t_env	*elem;

	elem = (t_env *)malloc(sizeof(t_env));
	if (!elem)
		exit(2);
	elem->arg = get_arg(str);
	elem->value = get_value(str);
	elem->vis = v;
	elem->next = NULL;
	return (elem);
}
