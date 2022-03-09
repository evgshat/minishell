/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaffere <bcaffere@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:54:38 by bcaffere          #+#    #+#             */
/*   Updated: 2022/02/09 17:54:40 by bcaffere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/functions.h"

char	*ft_strdup(const char *src)
{
	char	*cp;
	size_t	len;

	len = ft_strlen(src) + 1;
	cp = (char *)malloc(sizeof(char) * len);
	if (!cp)
		return (NULL);
	ft_memcpy(cp, src, len);
	return (cp);
}
