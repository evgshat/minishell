#ifndef MINISHELL_H
# define MINISHELL_H

#include "readline/readline.h"
#include "readline/rltypedefs.h"
#include <termios.h> // для tcgetattr и tcsetattr
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_data
{
	char			*str;
	struct termios	old_bash;
	struct termios	new_bash;
}	t_data;

void	parser(t_data *data);
void	init_env(t_data *data);


#endif