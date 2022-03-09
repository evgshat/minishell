#include "../../includes/minishell.h"

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

int    fd_for_redirect(char *str, char *file, t_data *data)
{
    if (ft_strncmp(str, "<", 2) == 0)
        data->cmd->fd_out = open(file, O_RDONLY);
    else if (ft_strncmp(str, ">", 2) == 0)
        data->cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, MODE_FOR_FILE);
    else if (ft_strncmp(str, ">>", 3) == 0)
        data->cmd->fd_out = open(file, O_CREAT | O_APPEND | O_WRONLY, MODE_FOR_FILE);
      else if (ft_strncmp(str, "<<", 3) == 0)
    {
        heredoc("!");
        data->cmd->fd_out = open(file, O_RDONLY, MODE_FOR_FILE);
        
    }
    return (data->cmd->fd_out);
}

// static  void change_file(char *str, char *file)
// {
//     int fd;

//     fd = 0;
//     fd = open(file, );
// }

void    redirect(char *str, char *file, t_data *data)
{
    int fd;

    fd = 0;
    fd = fd_for_redirect(str, file, data);
    if (fd == 0)
    {
        printf("error open\n");
        exit(1);
    }
    printf("%d\n", fd);
    // change_file();
}