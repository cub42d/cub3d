/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 20:22:34 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/20 21:53:45 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include <errno.h>

void	*ft_malloc(size_t size)
{
	void	*temp;

	temp = malloc(size);
	if (!temp)
	{
		ft_perror("malloc", errno);
		exit(EXIT_FAILURE);
	}
	return (temp);
}
