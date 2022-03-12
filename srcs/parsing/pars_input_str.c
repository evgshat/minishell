#include "minishell.h"

#define IS_QUOTE(c) (c == '\'' || c == '"')

int	get_num_of_str(t_data* data)
{
	int		i;
	char	quote_flag;
	int		qnty_str;
	int		is_new_str;

	i = -1;
	quote_flag = 0;
	qnty_str = 1;
	is_new_str = 1;
	if (data->line != NULL)
		free(data->line);
	data->line = ft_strtrim(data->line, " ");
	if (data->line == NULL)
		error_exit("malloc error!\n");
	if (ft_strlen(data->line) == 0)
		return (0);
	while(data->line[++i])
	{
		if (data->line[i] == ' ' && quote_flag == 0)
		{
			qnty_str++;
			is_new_str = 1;
			while(data->line[i] == ' ')
				++i;
		}
		if (IS_QUOTE(data->line[i]) && quote_flag == 0)
		{
			if (data->line[i] != ' ')
				is_new_str = 0;
			quote_flag = data->line[i];
		}
		else if (IS_QUOTE(data->line[i]) && quote_flag == data->line[i])
		{
			quote_flag = 0;
			if (is_new_str)
			{
				qnty_str++;
				is_new_str = 0;
			}
		}
	}
	if (quote_flag != 0)
		error_exit("not closed quote\n");
	return (qnty_str);
}

void	pars_input_str(t_data* data)
{
	int		qnty_str;
	char	*start_str;
	char	*end_str;
	char	*str_without_quotes;
	char	*tmp;
	char	quote_flag;
	int		is_new_str;
	char	c;
	int		i;
	int		j;

	qnty_str = get_num_of_str(data);
	data->args = malloc(sizeof(char*) * (qnty_str + 1));
	if (data->args == NULL)
		error_exit("malloc error!\n");
	quote_flag = 0;
	is_new_str = 1;
	start_str = data->line;
	i = 0;
	j = 0;
	while(j < qnty_str)
	{
		if (data->line[i] == '\0')
			data->args[j++] = ft_strdup(start_str);
		if (data->line[i] == ' ' && quote_flag == 0)
		{
			end_str = &(data->line[i]);
			c = data->line[i];
			*end_str = '\0';
			if (is_new_str)
				data->args[j++] = ft_strdup(start_str);
			else
			{
				data->args[j++] = ft_strjoin(str_without_quotes, start_str);
				free(str_without_quotes);
			}
			*end_str = c;
			while(data->line[i] == ' ')
				++i;
			start_str = &data->line[i];
			is_new_str = 1;
		}
		if (IS_QUOTE(data->line[i]) && quote_flag == 0)
		{
			if (data->line[i] != ' ')
			{
				c = data->line[i];
				end_str = &(data->line[i]);
				*end_str = '\0';
				str_without_quotes = ft_strdup(start_str);
				*end_str = c;
				is_new_str = 0;
			}
			start_str = &(data->line[i + 1]);
			quote_flag = data->line[i];
		}
		else if (IS_QUOTE(data->line[i]) && quote_flag == data->line[i])
		{
			quote_flag = 0;
			end_str = &(data->line[i]);
			c = data->line[i];
			*end_str = '\0';
			if (is_new_str)
			{
				data->args[j++] = ft_strdup(start_str);
				is_new_str = 0;
			}
			else
			{
				tmp = str_without_quotes;
				str_without_quotes = ft_strjoin(tmp, start_str);
				free(tmp);
			}
			*end_str = c;
			start_str = end_str + 1;
		}
		++i;
	}
	data->args[qnty_str] = NULL;
}
