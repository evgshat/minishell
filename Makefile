#SETUP
NAME		=	minishell
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -rf

#FILES AND PATH
HDRS		=	minishell.h funtions.c
DIR_HDRS	=	includes/
HDRS_PATH	=	$(addprefix $(DIR_HDRS), $(HDRS))

FNCS		=	ft_strlen.c ft_memcpy.c ft_split.c ft_strdup.c ft_strncmp.c ft_strjoin.c ft_putstr_fd.c
DIR_FNCS	=	functions/
FNCS_PATH	=	$(addprefix $(DIR_FNCS), $(FNCS))
FNCS_OBJ	=	$(FNCS_PATH:.c=.o)

SRCS		=	minishell.c copy_env.c creat_env_element.c cmd_export.c cmd_unset.c cmd_pwd.c cmd_cd.c cmd_echo.c exec_bin.c redirect.c my_programm.c new_copy_env.c
DIR_SRCS	=	sources/
SRCS_PATH	=	$(addprefix $(DIR_SRCS), $(SRCS))
SRCS_OBJ	=	$(SRCS_PATH:.c=.o)

PARS		=	common_parsing.c
DIR_PARS	=	parsing/
PARS_PATH	=	$(addprefix $(DIR_PARS), $(PARS))
PARS_OBJ	=	$(PARS_PATH:.c=.o)

#COMMANDS
$(NAME):		$(FNCS_OBJ) $(SRCS_OBJ) $(PARS_OBJ)
				$(CC) ${FLAGS} -I $(DIR_HDRS) -I readline $(FNCS_OBJ) $(SRCS_OBJ) $(PARS_OBJ) readline/libhistory.a readline/libreadline.a -ltermcap -o $(NAME)
				@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

%.o: %.c $(HDRS_PATH) Makefile
				${CC} -I $(DIR_HDRS) -I readline  -c $< -o $@

all:			$(NAME)

clean:
				@$(RM) $(FNCS_OBJ) $(SRCS_OBJ) $(PARS_OBJ)
				@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:			clean
				@$(RM) $(NAME)
				@echo -e "$(RED)all deleted!$(DEFAULT)"

re:				fclean all

.PHONY:		all clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
