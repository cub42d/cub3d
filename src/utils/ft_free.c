/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:24:08 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/22 05:30:07 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_double_free(char ***ptr)
{
	int	i;

	i = 0;
	while ((*ptr)[i])
		ft_free((void **) &(*ptr)[i++]);
	free(*ptr);
	*ptr = NULL;
}
