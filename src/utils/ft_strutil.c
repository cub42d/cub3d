/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:39:56 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/20 21:55:33 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dstsize >= len_dst)
	{
		while (dst[i] != 0)
			i++;
		while (*src != 0 && i + 1 < dstsize)
			dst[i++] = *src++;
		dst[i] = '\0';
	}
	if (dstsize < len_dst)
		return (len_src + dstsize);
	return (len_dst + len_src);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ret = ft_malloc((len_s1 + len_s2 + 1) * sizeof(char));
	ft_strlcpy(ret, s1, len_s1 + 1);
	ft_strlcat(ret, s2, len_s1 + len_s2 + 1);
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	len_s;

	if (!s || !len || (size_t)ft_strlen(s) <= start)
		return (ft_strdup(""));
	len_s = ft_strlen(s);
	if (len_s + start < len)
		len = len_s - start;
	ret = ft_malloc((len + 1) * sizeof(char));
	if (len_s > start)
		ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}

char	*ft_strdup(const char *s)
{
	char		*temp;
	size_t		i;

	i = 0;
	temp = ft_malloc((ft_strlen(s) + 1) * sizeof(char));
	while (s[i] != '\0')
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
