/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iszero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 01:20:07 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/30 01:26:50 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macro.h"

int	ft_iszero(double d)
{
	if (fabs(d) < (EPS))
		return (1);
	return (0);
}
