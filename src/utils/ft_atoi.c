/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:39:06 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/30 04:39:09 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	is_white_minus(const char *str, int *minus)
{
	int	i;

	i = 0;
	*minus = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*minus *= -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	long long	ret;
	long long	tmp;
	int			minus;
	int			i;

	ret = 0;
	i = is_white_minus(str, &minus);
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = ret * 10 + str[i] - '0';
		if (tmp < ret)
			return ((minus + 1) / -2);
		ret = tmp;
		i++;
	}
	return ((int)ret * minus);
}
