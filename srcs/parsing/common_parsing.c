#include "minishell.h"

char **create_mas(char *line)
{
	char **mas;
	mas = ft_split(line, ' '); // указатель на первом элементе
	if (mas == NULL)
		exit (1);
	return (mas);
}

int	is_cmd(t_data *data, char **mass)
{
	char **temp;

	temp = mass;
	while (*temp != NULL)
	{
		if (ft_strncmp(*temp, "cd", 3) == 0 
		|| ft_strncmp(*temp, "pwd", 4) == 0 
		|| ft_strncmp(*temp, "echo", 5) == 0
		|| ft_strncmp(*temp, "exit", 5) == 0
		|| ft_strncmp(*temp, "export", 7) == 0
		|| ft_strncmp(*temp, "unset", 6) == 0
		|| ft_strncmp(*temp, "env", 4) == 0
		|| ft_strncmp(*temp, "./", 3) == 0 ) 
		{
			data->cmd->is_cmd = 1;
			return (EXIST);
		}
		temp = temp + 1;
	}
	return (NOT_EXIST);
}

// дополнить, что после пайпа что-то должно быть
// дополнить, что пайп не должен быть первым и последним
// как обрабатывать типа " |" и кейсы в этом роде
// пайпы не должны быть подряд
int	is_pipe(t_data *data, char **mass)
{
	char **temp;

	temp = mass;
	while (*temp != NULL)
	{
		if (ft_strncmp(*temp, "|", 2) == 0)
		{
			data->cmd->is_pipe = 1;
			data->cmd->count_pipe++;
		}
		temp = temp + 1;
	}
	if (data->cmd->count_pipe > 0)	
		return (EXIST);
	else
		return (NOT_EXIST);
}

void is_l_redirect(t_data *data, char **mass)
{
	char **temp;

	temp = mass;
	while (*temp != NULL)
	{
		if (ft_strncmp(*temp, "<", 2) == 0)
		{
			data->cmd->is_left = 1;
			data->cmd->count_left++;
			temp = temp + 1;
			fd_for_redirect(*temp, *(temp + 1), data);
			// printf("fd = %d\n", data->cmd->fd_out);
		}
		if (ft_strncmp(*temp, "<<", 3) == 0)
		{
			data->cmd->is_dub_left = 1;
			data->cmd->count_dub_left++;
			fd_for_redirect(*temp, *(temp + 1), data);
			// printf("fd = %d\n", data->cmd->fd_out);
		}
		temp = temp + 1;
	}
}

void is_r_redirect(t_data *data, char **mass)
{
	char **temp;

	temp = mass;
	while (*temp != NULL)
	{
		if (ft_strncmp(*temp, ">", 2) == 0)
		{
			data->cmd->is_right = 1;
			data->cmd->count_right++;
			fd_for_redirect(*temp, *(temp + 1), data);
			// printf("fd = %d\n", data->cmd->fd_out);
		}
		if (ft_strncmp(*temp, ">>", 3) == 0)
		{
			data->cmd->is_dub_right = 1;
			data->cmd->count_dub_right++;
			fd_for_redirect(*temp, *(temp + 1), data);
			// printf("fd = %d\n", data->cmd->fd_out);
		}
		temp = temp + 1;
	}
}

int	is_redirect(t_data *data, char **mass)
{
	char **temp;

	temp = mass;
	while (*temp != NULL)
	{
		if (ft_strncmp(*temp, ">", 2) == 0 || ft_strncmp(*temp, "<", 2) == 0
		|| ft_strncmp(*temp, ">>", 3) == 0 || ft_strncmp(*temp, "<<", 3) == 0)
		{
			data->cmd->is_redirect = 1;
			data->cmd->count_redirect++;
		}
		temp = temp + 1;
	}
	is_l_redirect(data, data->cmd->name_cmd);
	is_r_redirect(data, data->cmd->name_cmd);
	data->cmd->old_fd_in = dup(STDIN_FILENO);
	data->cmd->old_fd_out = dup(STDOUT_FILENO);
	if (data->cmd->count_redirect > 0)	
		return (EXIST);
	else
		return (NOT_EXIST);
	return (NOT_EXIST);
}

void	common_parsing(t_data *data)
{
	char **temp;

	if (data->line == NULL)
		exit
		(1); // отдельная ф-ия с освобождением параметров
	// data->cmd = malloc(sizeof(char *) * 10000); //
	data->cmd->name_cmd = create_mas(data->line);
	temp = data->cmd->name_cmd;
	is_pipe(data, data->cmd->name_cmd);
	is_redirect(data, data->cmd->name_cmd);
	is_cmd(data, data->cmd->name_cmd);
}

