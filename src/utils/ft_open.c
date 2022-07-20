/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:09:41 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/21 04:28:03 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "macro.h"
#include <fcntl.h>

int	ft_open(const char *file, int flags)
{
	int	fd;

	fd = open(file, flags);
	if (fd == -1)
	{
		ft_putendl_fd(FILE_ERROR, 2);
		ft_perror_exit("open", 1);
	}
	return (fd);
}
