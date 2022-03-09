/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaffere <bcaffere@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:54:42 by bcaffere          #+#    #+#             */
/*   Updated: 2022/02/09 17:54:44 by bcaffere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/functions.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (*str)
		while (str[i])
			i++;
	return (i);
}
