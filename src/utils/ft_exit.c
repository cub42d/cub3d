/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:38:14 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/02 17:44:00 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h"
#include "mlx.h"
#include <stdlib.h>

int	ft_exit(t_view *vu)
{
	(void)vu;
	ft_putendl_fd("EXIT", 1);
	exit(0);
	return (0);
}
