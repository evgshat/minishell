#include "minishell.h"

static  void heredoc(char *stop)
{
    int fd;
    char *line_in_heredock;
    int len_stop;

    fd = 0;
    fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, MODE_FOR_FILE); // мб вместо O_RDWR надо O_WRONLY
    if (fd == 0)
        exit(1);
    line_in_heredock = readline("heredoc> ");
    // надо еще как-то интерпретировать спец символы в хердоке
    len_stop = ft_strlen(stop) + 1;
    while (ft_strncmp(line_in_heredock, stop, len_stop) != 0)
    {
        write(fd, line_in_heredock, ft_strlen(line_in_heredock));
        write(fd, "\n", 1);
        line_in_heredock = readline("heredoc> ");
    }
    close (fd);
    // printf("heredoc\n");
    // прописать че делать, если line_in_heredock = NULL
}

static void    fd_for_redirect(char *str, char *file, t_data *data)
{
    if (ft_strncmp(str, "<", 2) == 0)
        data->cmd->fd_out = open(file, O_RDONLY);
    else if (ft_strncmp(str, ">", 2) == 0)
    {
        // printf("file = %s\n", file);
         data->cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, MODE_FOR_FILE);
        //   printf("fd_out = %d\n", data->cmd->fd_out);
    }

    else if (ft_strncmp(str, ">>", 3) == 0)
        data->cmd->fd_out = open(file, O_CREAT | O_APPEND | O_WRONLY, MODE_FOR_FILE);
    else if (ft_strncmp(str, "<<", 3) == 0)
    {
        heredoc("!");
        data->cmd->fd_out = open(file, O_RDONLY, MODE_FOR_FILE);
    }
    // return (data->cmd->fd_out);
}

static void is_l_redirect(t_data *data, char **mass)
{
    if (ft_strncmp(*mass, "<", 2) == 0)
    {
        data->cmd->is_left = 1;
        fd_for_redirect(*mass, *(mass + 1), data);
    }
    else if (ft_strncmp(*mass, "<<", 3) == 0)
    {
         data->cmd->is_dub_left = 1;
         fd_for_redirect(*mass, *(mass + 1), data);
    }
}

static void is_r_redirect(t_data *data, char **mass)
{
    if (ft_strncmp(*mass, ">", 2) == 0)
    {
        data->cmd->is_right = 1;
        fd_for_redirect(*mass, *(mass + 1), data);
    }
    if (ft_strncmp(*mass, ">>", 3) == 0)
    {
        data->cmd->is_dub_right = 1;
        fd_for_redirect(*mass, *(mass + 1), data);
    }
}

int find_redirect(t_data *data, char **mass)
{
    char **temp;
    int    res;

    temp = mass;
    res = 0;
    while (*temp)
    {
        if (ft_strncmp(*temp, ">", 2) == 0 || ft_strncmp(*temp, "<", 2) == 0
        || ft_strncmp(*temp, ">>", 3) == 0 || ft_strncmp(*temp, "<<", 3) == 0)
        {
            data->cmd->is_redirect = 1;
            is_l_redirect(data, temp);
            is_r_redirect(data, temp);
            data->cmd->old_fd_in = dup(STDIN_FILENO);
            data->cmd->old_fd_out = dup(STDOUT_FILENO);
            return(res);
        }
        temp = temp + 1;
        res++;
    }
    return (0);
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