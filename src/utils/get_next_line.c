/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:20:56 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/20 21:58:30 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

static char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static int	read_buff(int fd, char **save)
{
	char	*buff;
	char	*temp;
	int		ret;

	buff = ft_malloc(sizeof(char) * (43));
	if (!buff)
		buff = NULL;
	ret = read(fd, buff, 42);
	if (ret < 0 || buff == NULL)
	{
		ft_free((void **)&buff);
		return (-1);
	}
	buff[ret] = '\0';
	temp = ft_strjoin(*save, buff);
	ft_free((void **)&(*save));
	ft_free((void **)&buff);
	if (ret > 0)
		return (1);
	else
		return (ret);
}

static void	division(char **save, char **line, int ret)
{
	char	*output;
	char	*backup;
	int		i;

	i = 0;
	if (ret == 0)
	{
		*line = ft_strdup(*save);
		ft_free((void **)&(*save));
	}
	else if (ret > 0)
	{
		while ((*save)[i] != '\n')
			i++;
		output = ft_substr(*save, 0, i);
		*line = output;
		backup = ft_strdup(*save + i + 1);
		ft_free((void **)&(*save));
		*save = backup;
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*save[256];
	int			ret;

	if (fd < 0 || fd > 256 || !line || 42 <= 0)
		return (-1);
	if (save [fd] == NULL)
		save[fd] = ft_strdup("");
	ret = 1;
	while (ret > 0 && (ft_strchr(save[fd], '\n') == 0))
		ret = read_buff(fd, &save[fd]);
	division(&save[fd], line, ret);
	return (ret);
}
