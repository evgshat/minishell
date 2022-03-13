/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharlet <lcharlet@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:07:48 by bcaffere          #+#    #+#             */
/*   Updated: 2022/03/13 22:47:35 by lcharlet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "functions.h"

# define PWD_MAX 1024
# define MODE_FOR_FILE 0640

/* for parsing */
# define CORRECT 0
# define NOT_CORRECT 1
# define EXIST 2
# define NOT_EXIST 3

typedef struct s_env
{
	char			*arg;
	char			*value;
	struct s_env	*next;
	int				vis;
}	t_env;

typedef struct s_cmd
{
	int	fd_in;
	int	fd_out;

	int	old_fd_in;
	int	old_fd_out;

	int	is_pipe;
	int	count_pipe;

	int	is_redirect;
	int	count_redirect;

	int	is_right;
	int	count_right;

	int	is_dub_right;
	int	count_dub_right;

	int	is_left;
	int	count_left;

	int	is_dub_left;
	int	count_dub_left;

	int	is_cmd;
	int	is_status;
	char **name_cmd;
}	t_cmd;

typedef struct s_bin
{
	int			pid; // ид процесса
	char		*path;
	struct stat	*file_stat;
	char		**argv;
	char		*cur_dir;
	char		**env_for_ex;
	int			*status;
}	t_bin;

typedef struct s_data
{
	char	*line;
	t_env	*sh_env;
	char	**args;
	int		status;
	t_cmd	*cmd;
	// t_bin	*bin;
}	t_data;


/* for execute not my programm */
char 	**convert_sh_env(t_env **sh_env);

/* to work with envp*/
t_env	*new_env_elem(char *str, int v);
t_env	*last_elem(t_env *elem);
void	add_elem_back(t_env **data, t_env *new);
char	*get_arg(char *str);
char	*get_value(char *str);
void	copy_env(t_env **data, char **envp);
void	env_print(t_env *data);

/* cmd */
void	cmd_export(char *str, t_env **envp);
void	cmd_unset(char *str, t_env **sh_env);
void	cmd_pwd(void);
void	cmd_cd(char *str);
void	cmd_echo(char **str);
void	cmd_exit(void);

/* execute my programm */
void	exec_bin(char *str, t_env **sh_env);

/* parsing */
void	common_parsing(t_data *data);
int		get_num_of_str(t_data* data);
void	pars_input_str(t_data* data);

/* my_shell */
void	my_programm(t_data *data);

/* check line*/
int	is_redirect(t_data *data, char *mass);

/* run */
void run_pipe(char *name_cmd, t_data *data);
void run_redirect(t_data *data);
void run_cmd(char **name_cmd, t_data *data);


#endif