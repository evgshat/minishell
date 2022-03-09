#SETUP
NAME		=	minishell
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -rf

#FILES AND PATH
HDRS		=	functions.h\
                minishell.h
DIR_HDRS	=	includes/
HDRS_PATH	=	$(addprefix $(DIR_HDRS), $(HDRS))

FNCS		=	ft_memcpy.c\
                ft_putstr_fd.c\
                ft_split.c\
                ft_strdup.c\
                ft_strjoin.c\
                ft_strlen.c\
                ft_strncmp.c
DIR_FNCS	=	functions/
DIRS		=	$(DIR_FNCS)
FNCS_PATH	=	$(addprefix $(DIR_FNCS), $(FNCS))
SRCS 		= 	$(FNCS_PATH)


CMDS		=	cmd_cd.c\
                cmd_echo.c\
                cmd_export.c\
                cmd_pwd.c\
                cmd_unset.c\
                cmd_exit.c\
                copy_env.c\
                creat_env_element.c\
                exec_bin.c\
                minishell.c\
                my_programm.c\
                new_copy_env.c\
                redirect.c
DIR_CMDS	=	sources/
DIRS		+=	$(DIR_CMDS)
CMDS_PATH	=	$(addprefix $(DIR_CMDS), $(CMDS))
SRCS 		+= 	$(CMDS_PATH)

PARS		=	common_parsing.c
DIR_PARS	=	parsing/
DIRS		+=	$(DIR_PARS)
PARS_PATH	=	$(addprefix $(DIR_PARS), $(PARS))
SRCS 		+= 	$(PARS_PATH)

DIR_OBJ 	=	objs/
DIR_SRC		=	srcs/
OBJS		=	$(patsubst %.c, %.o, $(SRCS))
DIR_OBJS	=	$(addprefix $(DIR_OBJ), $(DIRS))
PATH_OBJS	=	$(addprefix $(DIR_OBJ), $(OBJS))

all:			$(NAME)

#COMMANDS
$(NAME):		write_logo $(DIR_OBJS) $(PATH_OBJS)
				@$(CC) $(FLAGS) -I $(DIR_HDRS) -I readline $(PATH_OBJS) readline/libhistory.a readline/libreadline.a -ltermcap -o $(NAME)
				@echo "$(GREEN)\n$(NAME) created!$(DEFAULT)"

write_logo:
				@echo "$(GREEN)\n\
███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\n\
████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\n\
██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\n\
██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\n\
██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗\n\
╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\n\
				$(DEFAULT)"

$(DIR_OBJS):
				@mkdir -p $(DIR_OBJS)

$(DIR_OBJ)%.o:	$(DIR_SRC)%.c $(HDRS_PATH) Makefile
				@$(CC) $(FLAGS) -I $(DIR_HDRS) -I readline  -c $< -o $@
				@echo "$(GREEN)...$(DEFAULT)\c"

clean:
				@$(RM) $(DIR_OBJ)
				@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:			clean
				@$(RM) $(NAME)
				@echo "$(RED)all deleted!$(DEFAULT)"

re:				fclean all

.PHONY:		all clean fclean re write_logo

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
