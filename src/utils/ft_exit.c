/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:38:14 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/02 18:08:16 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h"
#include "mlx.h"
#include <stdlib.h>

int	ft_exit(t_view *vu)
{
	mlx_destroy_window(vu->mlx, vu->mlx_win);
	ft_putendl_fd("EXIT", 1);
	exit(0);
	return (0);
}
