/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 05:11:15 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/22 05:11:56 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*temp;

	temp = dst;
	if (!dst && !src)
		return (0);
	while (n--)
	{
		*temp++ = *(unsigned char *)src++;
	}
	return (dst);
}
