/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iseq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:04:00 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/21 04:05:07 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && --n)
	{
		if (*s1 != *s2)
			return (*((unsigned char *) s1) - *((unsigned char *) s2));
		s1++;
		s2++;
	}
	return (*((unsigned char *) s1) - *((unsigned char *) s2));
}

int	ft_iseq(char *s1, char *s2)
{
	return (!ft_strncmp(s1, s2, ft_strlen(s1) + 1));
}
