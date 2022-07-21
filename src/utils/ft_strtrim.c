/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 06:25:26 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/22 06:25:33 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	len_s1;

	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	len_s1 = ft_strlen(s1);
	while (ft_strchr(set, *(s1 + len_s1)) && len_s1 > 0)
		len_s1--;
	ret = ft_substr(s1, 0, len_s1 + 1);
	if (!ret)
		return (NULL);
	return (ret);
}
