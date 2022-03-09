/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaffere <bcaffere@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:54:24 by bcaffere          #+#    #+#             */
/*   Updated: 2022/02/09 17:54:27 by bcaffere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/functions.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*u_dest;
	unsigned char	*u_src;

	if (dest == src)
		return (dest);
	u_dest = (unsigned char *)dest;
	u_src = (unsigned char *)src;
	while (n > 0)
	{
		*u_dest = *u_src;
		u_dest++;
		u_src++;
		n--;
	}
	return (dest);
}
