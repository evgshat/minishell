#include "minishell.h"

// int	is_cmd(t_data *data, char **mass)
// {
// 	while (*mass != NULL)
// 	{
// 		if (ft_strncmp(*mass, "cd", 3) == 0
// 		|| ft_strncmp(*mass, "pwd", 4) == 0
// 		|| ft_strncmp(*mass, "echo", 5) == 0
// 		|| ft_strncmp(*mass, "exit", 5) == 0
// 		|| ft_strncmp(*mass, "export", 7) == 0
// 		|| ft_strncmp(*mass, "unset", 6) == 0
// 		|| ft_strncmp(*mass, "env", 4) == 0
// 		|| ft_strncmp(*mass, "./", 3) == 0)
// 		{
// 			data->cmd->is_cmd = 1;
// 			return (1);
// 		}
// 		mass = mass + 1;
// 	}
// 	return (0);
// }

// int	is_redirect(t_data *data, char **mass)
// {
// 	while (*mass != NULL)
// 	{
// 		if (ft_strncmp(*mass, ">", 2) == 0 || ft_strncmp(*mass, "<", 2) == 0
// 		|| ft_strncmp(*mass, ">>", 3) == 0 || ft_strncmp(*mass, "<<", 3) == 0)
// 		{
// 			data->cmd->is_redirect = 1;
// 			// data->cmd->count_redirect++;
// 			return(1);
// 		}
// 	}
// 	return (0);
// }

// int	is_pipe(t_data *data, char **mass)
// {
// 	while (*mass != NULL)
// 	{
// 		if (ft_strncmp(*mass, "|", 2) == 0)
// 		{
// 			data->cmd->is_pipe = 1;
// 			// data->cmd->count_pipe++;
// 			return (1);
// 		}
// 		mass = mass + 1;
// 	}
// 		return (0);
// }

// void common_parsing(t_data *data)
// {
// 	char **name_cmd;

// 	name_cmd = data->args;
// 	if (is_pipe(data, name_cmd) == 1)
// 	{
// 		fd_for_redirect(*name_cmd, *(name_cmd + 1), data);
// 		run_pipe(name_cmd, data);
// 	}
// 	if (is_redirect(data, name_cmd) == 1)
// 		run_redirect(data);
// 	if (is_cmd(data, name_cmd) == 1)
// 		run_cmd(name_cmd, data);
// }

// char **create_mas(char *line)
// {
// 	char **mas;
// 	mas = ft_split(line, ' '); // указатель на первом элементе
// 	if (mas == NULL)
// 		exit (1);
// 	return (mas);
// }

// int	is_cmd(t_data *data, char **mass)
// {
// 	char **temp;

// 	temp = mass;
// 	while (*temp != NULL)
// 	{
// 		if (ft_strncmp(*temp, "cd", 3) == 0
// 		|| ft_strncmp(*temp, "pwd", 4) == 0
// 		|| ft_strncmp(*temp, "echo", 5) == 0
// 		|| ft_strncmp(*temp, "exit", 5) == 0
// 		|| ft_strncmp(*temp, "export", 7) == 0
// 		|| ft_strncmp(*temp, "unset", 6) == 0
// 		|| ft_strncmp(*temp, "env", 4) == 0
// 		|| ft_strncmp(*temp, "./", 3) == 0)
// 		{
// 			data->cmd->is_cmd = 1;
// 			return (0);
// 		}
// 		temp = temp + 1;
// 	}
// 	return (1);
// }

// // дополнить, что после пайпа что-то должно быть
// // дополнить, что пайп не должен быть первым и последним
// // как обрабатывать типа " |" и кейсы в этом роде
// // пайпы не должны быть подряд
// int	is_pipe(t_data *data, char **mass)
// {
// 	char **temp;

// 	temp = mass;
// 	while (*temp != NULL)
// 	{
// 		if (ft_strncmp(*temp, "|", 2) == 0)
// 		{
// 			data->cmd->is_pipe = 1;
// 			data->cmd->count_pipe++;
// 		}
// 		temp = temp + 1;
// 	}
// 	if (data->cmd->count_pipe > 0)
// 		return (EXIST);
// 	else
// 		return (NOT_EXIST);
// }

// void is_l_redirect(t_data *data, char **mass)
// {
// 	char **temp;

// 	temp = mass;
// 	while (*temp != NULL)
// 	{
// 		if (ft_strncmp(*temp, "<", 2) == 0)
// 		{
// 			data->cmd->is_left = 1;
// 			data->cmd->count_left++;
// 			temp = temp + 1;
// 			fd_for_redirect(*temp, *(temp + 1), data);
// 		}
// 		if (ft_strncmp(*temp, "<<", 3) == 0)
// 		{
// 			data->cmd->is_dub_left = 1;
// 			data->cmd->count_dub_left++;
// 			fd_for_redirect(*temp, *(temp + 1), data);
// 		}
// 		temp = temp + 1;
// 	}
// }

// void is_r_redirect(t_data *data, char **mass)
// {
// 	char **temp;

// 	temp = mass;
// 	while (*temp != NULL)
// 	{
// 		if (ft_strncmp(*temp, ">", 2) == 0)
// 		{
// 			data->cmd->is_right = 1;
// 			data->cmd->count_right++;
// 			fd_for_redirect(*temp, *(temp + 1), data);
// 		}
// 		if (ft_strncmp(*temp, ">>", 3) == 0)
// 		{
// 			data->cmd->is_dub_right = 1;
// 			data->cmd->count_dub_right++;
// 			fd_for_redirect(*temp, *(temp + 1), data);
// 		}
// 		temp = temp + 1;
// 	}
// }

// char	*is_redirect(t_data *data, char **mass)
// {
// 	int	i;

// 	i = 0;
// 	while (mass[i] != NULL)
// 	{
// 		if (ft_strncmp(mass[i], ">", 2) == 0 || ft_strncmp(mass[i], "<", 2) == 0
// 		|| ft_strncmp(mass[i], ">>", 3) == 0 || ft_strncmp(mass[i], "<<", 3) == 0)
// 		{
// 			data->cmd->is_redirect = 1;
// 			data->cmd->count_redirect++;
// 			return(mass[i]);
// 		}
// 		i++;
// 	}
// 	is_l_redirect(data, data->cmd->name_cmd);
// 	is_r_redirect(data, data->cmd->name_cmd);
// 	data->cmd->old_fd_in = dup(STDIN_FILENO);
// 	data->cmd-> = dup(STDOUT_FILENO);
// 	return (NULL);
// }

// int	is_quotes(t_data *data)
// {
// 	char	*temp_line;
// 	int		i;
// 	int		count;

// 	i = 0;
// 	count = 0;
// 	temp_line = data->line;
// 	while (temp_line[i] != '\0')
// 	{
// 		if (temp_line[i] == '"')
// 			count++;
// 		if (count == 2)
// 			break;
// 		i++;
// 	}
// 	if (count == 1)
// 	{
// 		printf("error\none_quotes\n");
// 		exit(1);
// 	}
// 	else if (count == 2)
// 		return (1);
// 	return (0);
// }


// void	common_parsing(t_data *data)
// {
// 	char **temp;

// 	if (data->line == NULL)
// 		exit
// 		(1); // отдельная ф-ия с освобождением параметров
// 	// data->cmd = malloc(sizeof(char *) * 10000); //
// 	data->cmd->name_cmd = create_mas(data->line);
// 	temp = data->cmd->name_cmd;
// 	is_quotes(data);
// 	is_pipe(data, data->cmd->name_cmd);
// 	// if (is_redirect(data, data->cmd->name_cmd) != NULL)
// 		// run_redirect(data->cmd->name_cmd);
// 	is_cmd(data, data->cmd->name_cmd);
// }



