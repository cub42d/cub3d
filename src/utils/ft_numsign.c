/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numsign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 02:03:55 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/30 02:04:07 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	num_sign(double d)
{
	if (ft_iszero(d))
		return (0);
	else if (d > 0)
		return (1);
	else
		return (-1);
}