#include "minishell.h"

void run_cmd(char **name_cmd, t_data *data)
{
    if (data->cmd->is_cmd == 1)
    {
        while (*name_cmd != NULL)
        {
            if (ft_strncmp(*name_cmd, "exit", 5) == 0) //handle exit
            {
                printf("exit\n");
                exit(0); // what about free() ?
            }
            if (ft_strncmp(*name_cmd, "env", 4) == 0) //handle envp
                env_print(data->sh_env);
            if (ft_strncmp(*name_cmd, "export", 7) == 0) //handle export
                cmd_export("TEST=test", &data->sh_env); // "USER=test" depends on parsing
            if (ft_strncmp(*name_cmd, "unset", 7) == 0) //handle export
                cmd_unset("TMPDIR", &data->sh_env); // "USER" depends on parsing
            if (ft_strncmp(*name_cmd, "pwd", 4) == 0)
                cmd_pwd();
            if (ft_strncmp(*name_cmd, "cd", 3) == 0)
                cmd_cd("/");
            if (ft_strncmp(*name_cmd, "echo", 5) == 0)
                cmd_echo("-n", "hello\nworld\n");
            if (ft_strncmp(*name_cmd, "./", 3) == 0)
                exec_bin("text.txt", &data->sh_env);
            name_cmd = name_cmd + 1;
        }
    }
    // printf("end cmd\n");
}

char *find_path_ex(char *all_path, char *prog_name)
{
    char *path_for_ex;
    char **mass_path;
//    int  res_ex;
    struct dirent *file;
    DIR *dir;
    int i;

    i = -1;
    // dir = NULL;
    // file = NULL;
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
//    char    *path_for_ex;

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

void run_execve(t_data *data)
{
    char    **env_for_ex;
    char    *path;
    char    *argv[2];
    char    **temp;
    pid_t pid;

    printf("run_execve\n");
    argv[0] = "ls";
    argv[1] = NULL;
    pid = fork();
    if (pid == 0)
    {
         env_for_ex = convert_env(data->sh_env);
         path = value_from_env("PATH\0", data->sh_env, *(data->cmd->name_cmd));
        //  printf("path = %s\n", path);
         temp = env_for_ex;
         execve(path, data->cmd->name_cmd, env_for_ex); //
    }
    waitpid(pid, 0, 0); // поменять второй ноль (на код завершения программы для execve)
}

void run_redirect(t_data *data)
{
    if (data->cmd->is_redirect == 1)
    {
        if (data->cmd->is_right == 1 || data->cmd->is_dub_right == 1)
        {
            dup2(data->cmd->fd_out, 1);
            close(data->cmd->fd_out);
        }
        else if (data->cmd->is_left == 1 || data->cmd->is_dub_left == 1)
        {
            dup2(data->cmd->fd_in, 0);
            close(data->cmd->fd_in);
        }
    }
}

// echo "123" | wc -l
void run_pipe(char **name_cmd, t_data *data)
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
        run_cmd(name_cmd, data);
        run_redirect(data);
        run_execve(data);
        exit(1);
    }
}

void my_programm(char **name_cmd, t_data *data)
{
//    int fd[2];
    t_data *temp;


    temp = data;
    // while (*(temp->cmd->name_cmd) != NULL)
    // {
        if (data->cmd->is_pipe > 0)
        {
            while (data->cmd->count_pipe != 0)
            {
                run_pipe(name_cmd, data);
                wait(0);
                data->cmd->count_pipe--;
            }
        }
        if (data->cmd->is_redirect > 0)
            run_redirect(data);
        run_execve(data);
        run_cmd(name_cmd, data);
        dup2(data->cmd->old_fd_out, 1);
        dup2(data->cmd->old_fd_in, 0);
        temp = temp + 1;
    // }
    // check merge
}