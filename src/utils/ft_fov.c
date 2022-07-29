/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fov.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 01:29:25 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/30 01:32:54 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "macro.h"

double	ft_fov_h(double fov)
{
	return (ft_deg2rad(fov));
}

double	ft_fov_v(double fov)
{
	return (ft_fov_h(fov) * ((double)SY / (double)SX));
}
