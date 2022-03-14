/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharlet <lcharlet@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:10:04 by bcaffere          #+#    #+#             */
/*   Updated: 2022/03/13 22:08:07 by lcharlet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* initialization all data*/
void	update_init_date(t_data *data)
{
	data->line = NULL;
	data->args = NULL;
	data->sh_env = NULL;
	data->status = 0;
	data->cmd = malloc(sizeof(char *) * 10000);
	data->cmd->fd_in = 0;
	data->cmd->fd_out = 1;
	data->cmd->is_pipe = 0;
	data->cmd->count_pipe = 0;
	data->cmd->is_redirect = 0;
	data->cmd->count_redirect = 0;
	data->cmd->is_right = 0;
	data->cmd->count_right = 0;
	data->cmd->is_dub_right = 0;
	data->cmd->count_dub_right = 0;
	data->cmd->is_left = 0;
	data->cmd->count_left = 0;
	data->cmd->is_dub_left = 0;
	data->cmd->count_dub_left = 0;
	data->cmd->is_cmd = 0;
	data->cmd->is_status = 0;
}

void	init_date(t_data *data, char **envp)
{
	data->line = NULL;
	data->args = NULL;
	data->sh_env = NULL;
	data->status = 0;

	// инициализация bin-a
	// data->bin = malloc(sizeof(t_bin));

	// инициализация листа команд
	data->cmd = malloc(sizeof(char *) * 10000);
	data->cmd->fd_in = 0;
	data->cmd->fd_out = 1;
	data->cmd->is_pipe = 0;
	data->cmd->count_pipe = 0;
	data->cmd->is_redirect = 0;
	data->cmd->count_redirect = 0;
	data->cmd->is_right = 0;
	data->cmd->count_right = 0;
	data->cmd->is_dub_right = 0;
	data->cmd->count_dub_right = 0;
	data->cmd->is_left = 0;
	data->cmd->count_left = 0;
	data->cmd->is_dub_left = 0;
	data->cmd->count_dub_left = 0;
	data->cmd->is_cmd = 0;
	data->cmd->is_status = 0;
	// data->cmd->name_cmd = NULL;
	copy_env(&(data->sh_env), envp);
}

void	err_msg(char *str)
{
	printf("minishell: %s: command not found\n", str);
}

/* function handling push Ctrl+C */
void	handler_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data	data;
	char *si = malloc(50);
	(void) argc;
	(void) argv;
	if (si == NULL)
		printf("errorchik\n");

	init_date(&data, envp);
	signal(SIGINT, handler_ctrl_c);
	si[0] = 'e';
	si[1] = 'c';
	si[2] = 'h';
	si[3] = 'o';
	si[4] = ' ';
	si[5] = 'e';
	si[6] = ' ';
	si[7] = '>';
	si[8] = ' ';
	si[9] = 'q';
	// while (argc && argv)
	// {
		data.line = readline("minishell > ");
		if (data.line == NULL)
		{
			printf("\b\bexit\n");
			exit (1);
		}
		pars_input_str(&data);
		// int i = -1;

		// while (data.args[++i])
		// 	printf("%s\n", data.args[i]);
		my_programm(&data);
	// }
	rl_clear_history();
	return (0);
}

// void	swing(int *x)
// {
// 	if (*x == 0)
// 		(*x)++;
// 	else
// 		(*x)--;
// }

// int	check_good_line(char *str)
// {
// 	int	dquote;
// 	int	quote;

// 	dquote = 0;
// 	quote = 0;
// 	while (*str)
// 	{
// 		if (*str == '"' && !quote)
// 			swing(&dquote);
// 		else if (*str == '\'' && !dquote)
// 			swing(&quote);
// 		else if (*str == ' ' && !ft_strncmp(str, " | ", 3) && quote && dquote)
// 			return (1);
// 		str++;
// 	}
// 	if (*str == '\0' && (quote || dquote))
// 		return (1);
// 	return (0);
// }
