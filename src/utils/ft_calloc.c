/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:18:28 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/20 22:21:42 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_calloc(size_t count, size_t size)
{
	const size_t	mem = count * size;
	void			*p;

	p = ft_malloc(sizeof(size_t) * mem);
	if (!p)
		return (NULL);
	ft_memset(p, 0x00, mem);
	return (p);
}
