/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharlet <lcharlet@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:55:14 by bcaffere          #+#    #+#             */
/*   Updated: 2022/03/12 12:17:17 by hcharlsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <stdio.h>
# include <unistd.h> //getcwd
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>

/* to readline */
# include "../readline/readline.h"
# include "../readline/history.h"

/* to signal */
# include <signal.h>

/* to stat */
# include <sys/stat.h> // stat

size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
void	error_exit(char *msg);

#endif
