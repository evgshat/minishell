#include "minishell.h"

int	check_cmd(char *name_cmd)
{
	if (name_cmd)
	{
		if (ft_strncmp(name_cmd, "cd", 3) == 0
		|| ft_strncmp(name_cmd, "pwd", 4) == 0
		|| ft_strncmp(name_cmd, "echo", 5) == 0
		|| ft_strncmp(name_cmd, "exit", 5) == 0
		|| ft_strncmp(name_cmd, "export", 7) == 0
		|| ft_strncmp(name_cmd, "unset", 6) == 0
		|| ft_strncmp(name_cmd, "env", 4) == 0
		|| ft_strncmp(name_cmd, "./", 3) == 0)
			return (1);
	}
	return (0);
}

void run_cmd(char **name_cmd, t_data *data)
{
    // if (data->cmd->is_cmd == 1) // (data->cmd->is_cmd == 1 && data->cmd->is_redirect == 0)
    if (ft_strncmp(*name_cmd, "exit", 5) == 0)
        cmd_exit();
    else if (ft_strncmp(*name_cmd, "env", 4) == 0)
        env_print(data->sh_env);
    else if (ft_strncmp(*name_cmd, "export", 7) == 0)
        cmd_export(*(name_cmd + 1), &data->sh_env);
    else if (ft_strncmp(*name_cmd, "unset", 7) == 0)
        cmd_unset(*(name_cmd + 1), &data->sh_env);
    else if (ft_strncmp(*name_cmd, "pwd", 4) == 0)
        cmd_pwd();
    else if (ft_strncmp(*name_cmd, "cd", 3) == 0)
        cmd_cd(*(name_cmd + 1));
    else if (ft_strncmp(*name_cmd, "echo", 5) == 0)
        cmd_echo(name_cmd);
    else if (ft_strncmp(*name_cmd, "./", 3) == 0)
        exec_bin(*(name_cmd + 1), &data->sh_env);
}

char *find_path_ex(char *all_path, char *prog_name)
{
    char *path_for_ex;
    char **mass_path;
    struct dirent *file;
    DIR *dir;
    int i;

    i = -1;
    path_for_ex = NULL;
    mass_path = ft_split(all_path, ':');
    while (mass_path[++i] != NULL)
    {
        dir = opendir(mass_path[i]);
        file = readdir(dir);
        if (file != NULL)
        {
            if (ft_strncmp(file->d_name, prog_name, ft_strlen(prog_name) + 1) == 0)
            {
                path_for_ex = ft_strjoin(mass_path[i], "/");
                return(ft_strjoin(path_for_ex, prog_name));
            }
        }
        while (file != NULL)
        {
            file = readdir(dir);
            if (file == NULL)
                break ;
            if (file != NULL)
            {
                if (ft_strncmp(file->d_name, prog_name, ft_strlen(prog_name) + 1) == 0)
                {
                    path_for_ex = ft_strjoin(mass_path[i], "/");
                    return(ft_strjoin(path_for_ex, prog_name));
                }
            }
        }
    }
    return(NULL);
}

char *value_from_env(char *field, t_env *sh_env, char *prog_name)
{
    t_env   *temp;
    int     len;

    temp = sh_env;
    while (temp)
    {
        len = ft_strlen(temp->arg) + 1;
        if (ft_strncmp(temp->arg, field, len) == 0)
            return (find_path_ex(temp->value, prog_name));
        temp = temp->next;
    }
    return (NULL);
}

int count_str(t_env *env)
{
    t_env *temp;
    int res;

    temp = env;
    res = 0;
    while (temp)
    {
        res++;
        temp = temp->next;
    }
    return (res);
}

char **convert_env(t_env *env)
{
    char **res;
    char *new_str;
    char *temp_str;
    int i;
    int count;
    t_env *temp;

    temp = env;
    i = 0;
    count = count_str(env);
    res = malloc(sizeof(char *) * (count + 1));
    if (!res)
        printf("error_malloc\n");
    while (temp)
    {
        new_str = ft_strjoin(temp->arg, "=");
        temp_str = new_str;
        new_str = ft_strjoin(new_str, temp->value);
        free(temp_str);
        res[i] = new_str;
        temp = temp->next;
        i++;
    }
    res[i] = NULL;
    return (res);
}

void run_execve(char **name_cmd, t_data *data)
{
    char    **env_for_ex;
    char    *path;
    char    **temp;
    char    *argv[2];
    pid_t   pid;
    int     res_check_cmd;
    int     res_of_execve;

    argv[0] = *name_cmd;
    argv[1] = NULL;
    pid = fork();
    res_of_execve = 666;
    res_check_cmd = check_cmd(*name_cmd);
    if (pid == 0 && res_check_cmd == 0)
    {
        env_for_ex = convert_env(data->sh_env);
        path = value_from_env("PATH\0", data->sh_env, *name_cmd);
        temp = env_for_ex;
        execve(path, argv, env_for_ex);
        exit(1);
    }
    // wait();
    // waitpid(pid, 0, 0); // поменять второй ноль (на код завершения программы для execve)
}

void run_pipe(char *name_cmd, t_data *data)
{
    pid_t   pid;
    int fd[2];

    if (pipe(fd) != 0)
        exit (1);
    pid = fork();
    if (pid == -1)
        exit (1);
    if (pid == 0)
    {
        printf("its child\n");
        close (fd[0]);
        dup2(fd[1], 1);
        run_cmd(&name_cmd, data);
        run_redirect(data);
        // run_execve(data);
        exit(1);
    }
}

int	is_cmd(t_data *data, char **mass)
{
    if (ft_strncmp(*mass, "cd", 3) == 0
    || ft_strncmp(*mass, "pwd", 4) == 0
    || ft_strncmp(*mass, "echo", 5) == 0
    || ft_strncmp(*mass, "exit", 5) == 0
    || ft_strncmp(*mass, "export", 7) == 0
    || ft_strncmp(*mass, "unset", 6) == 0
    || ft_strncmp(*mass, "env", 4) == 0
    || ft_strncmp(*mass, "./", 3) == 0)
    {
        data->cmd->is_cmd = 1;
        return (1);
    }
    // check_on_red_or_pipe();
	return (0);
}

int	is_pipe(t_data *data, char *mass)
{
    if (ft_strncmp(mass, "|", 2) == 0)
    {
        data->cmd->is_pipe = 1;
        return (1);
    }
    return (0);
}

void my_programm(t_data *data)
{
	char **name_cmd;
    int count;

    name_cmd = data->args;

    while (*name_cmd)
    {
        if (is_pipe(data, *name_cmd) == 1)
            run_pipe(*name_cmd, data);
        count = find_redirect(data, name_cmd);
        printf("%d\n", count);
        if (count > 0)
        {
            run_redirect(data);
            run_cmd(name_cmd, data);
            name_cmd = name_cmd + count + 2;
            // printf("after_find_redirect = %s\n", *name_cmd);
        }
        if ((is_cmd(data, name_cmd)) == 1)
            run_cmd(name_cmd, data);
        // run_execve(name_cmd, data);
        // wait(0);
        dup2(data->cmd->old_fd_out, 1);
        dup2(data->cmd->old_fd_in, 0);
        update_init_date(data);
        name_cmd = name_cmd + 1;
        // printf(" = %s\n", *name_cmd); 
        add_history(data->line);
    }
}