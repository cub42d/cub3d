/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colision_angle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:12:20 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/09 21:48:30 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macro.h"
#include <math.h>

void	ft_colision_angle(double *angle)
{
	if (*angle > M_PI)
		*angle -= _2PI;
	else if (*angle < -M_PI)
		*angle += _2PI;
}
