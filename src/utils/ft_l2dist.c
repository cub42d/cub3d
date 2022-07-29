/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l2dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:59:58 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/30 01:00:44 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	ft_l2dist(double x0, double y0, double x1, double y1)
{
	double	dx;
	double	dy;

	dx = x0 - x1;
	dy = y0 - y1;
	return (sqrt(dx * dx + dy * dy));
}
