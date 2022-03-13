#include "minishell.h"

static int count_var_sh_env(t_env **sh_env)
{
	int		count;
	t_env	*temp;

	temp = *sh_env;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

char 	**convert_sh_env(t_env **sh_env)
{
	int	count_var;
	int	i;
	t_env	*temp;
	char **env_for_ex;

	temp = *sh_env;
	count_var = count_var_sh_env(sh_env);
	env_for_ex = malloc(sizeof(char *) * count_var + 1);
	if (!env_for_ex)
		exit(1);
	i = 0;
	while (temp)
	{
		env_for_ex[i] = ft_strjoin(temp->arg, "=");
		temp = temp->next;
		i++;
	}
	free(temp);
	env_for_ex[count_var] = NULL;
	return (env_for_ex);
}

void	init_bin(t_bin *bin)
{
	bin->pid = 0;
	bin->argv = NULL;
	bin->env_for_ex = NULL;
	bin->cur_dir = NULL;
	bin->path = NULL;
	bin->cur_dir = malloc (sizeof(char) * PWD_MAX);
	bin->path =  malloc (sizeof(char) * PWD_MAX);
}

void	exec_bin(char *str, t_env **sh_env)
{
	t_bin	bin;
	int		res_stat;
	int		count_path;

	init_bin(&bin);
	bin.env_for_ex = convert_sh_env(sh_env);
	bin.pid = fork();
	if (!bin.pid)
		exit(1);
	// printf("child_pid = %d\n", getpid()); // пид ребенка
	// printf("parent_pid = %d\n", getppid()); // пид родителя
	getcwd(bin.path, PWD_MAX);
	count_path = ft_strlen(bin.path);
	bin.path[count_path] = '/';
	bin.path = ft_strjoin(bin.path, str);
	printf("1\n");
	res_stat = stat(bin.path, bin.file_stat);
	printf("%s\n", bin.path);
	printf("2\n");
	if (!res_stat)
		exit(1);
	printf("3\n");
	// if (S_ISDIR(bin.file_stat->st_mode) == 0)
	// {
	// 	printf("4");
	// 	exit(1);
	// }
	if (execve(bin.path, bin.argv, bin.env_for_ex) == -1) // тут походу обрывается
		printf("ko\n");
	else
		printf("ok\n");

	printf("5\n");
	waitpid(bin.pid, bin.status, 0);
	printf("5\n");
	free (bin.cur_dir);
	printf("6\n");
}