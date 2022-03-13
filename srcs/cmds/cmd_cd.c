#include "minishell.h"

static char	*find_home(char *pwd)
{
	char *home;
	int	count_ch;
	int	i;

	count_ch = 0;
	i = 0;
	home = malloc(sizeof(char) * PWD_MAX);
	if (!home)
		exit (1);
	while (pwd[i] != '\0')
	{
		if (pwd[i] == '/')
			count_ch++;
		if (count_ch < 3)
			home[i] = pwd[i];
		else
			break ;
		i++;
	}
	// home[i] = '/'; // хз, надо ли
	home[++i] = '\0';
	return (home);
}

void	cmd_cd(char *str)
{
	char	*path;
	int		len_path;
	int		i;
	int		res;
	char	*home;		// для абсолютного пути
	int		len_home;	// для абсолютного пути

	// path = malloc(sizeof(char) * PWD_MAX);
	// if (!path)
	// 	exit(1);
	path = NULL;
	path = getcwd(path, PWD_MAX);
	if (!path)
		exit(1);
	// если путь абсолютный
	home = find_home(path);
	len_home = ft_strlen(home);
	// если путь абсолютный, if
	if (ft_strncmp(home, str, len_home) == 0)
	{
		res = chdir(str);
		printf("path = %s res = %d\n", str, res);
		if (res == -1)
			exit (1);
		return ;
	}
	len_path = ft_strlen(path);
	path[len_path] = '/';
	len_path++;
	// printf("first = %s\n", path);
	i = 0;
	while (str[i] != '\0')
		path[len_path++] = str[i++];
	path[len_path] = '\0';
	res = chdir(path);
	// printf("path = %s res = %d\n", path, res);
	if (res == -1)
		exit (1);
	// printf("path = %s res = %d\n", path, res);
	// printf("%s\n", path);
	// free (path);
	free (home);
}