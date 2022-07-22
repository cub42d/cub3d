/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:08:05 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/20 21:16:57 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include <errno.h>

void	ft_perror_exit(const char *s, unsigned int exit_status)
{
	ft_perror(s, errno);
	exit(exit_status);
}
