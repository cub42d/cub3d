/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:20:56 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/23 17:03:24 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "macro.h"
#include <stdlib.h>
#include <unistd.h>

static int	read_buff(int fd, char **save)
{
	char	*buff;
	char	*temp;
	int		ret;

	buff = ft_malloc(sizeof(char) * (43));
	ret = read(fd, buff, 42);
	if (ret < 0 || buff == NULL)
	{
		ft_free((void **)&buff);
		ft_error_exit("Error: get_next_line");
	}
	buff[ret] = '\0';
	temp = ft_strjoin(*save, buff);
	ft_free((void **)&(*save));
	ft_free((void **)&buff);
	*save = temp;
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
		if (*save && **save == '\0')
			*line = NULL;
		else
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
	static char	*save[257];
	int			ret;

	if (fd < 0 || fd > 256 || !line)
		ft_error_exit(MAP_ERROR);
	if (save[fd] == NULL)
		save[fd] = ft_strdup("");
	ret = 1;
	while (ret > 0 && (ft_strchr(save[fd], '\n') == 0))
		ret = read_buff(fd, &save[fd]);
	division(&save[fd], line, ret);
	return (ret);
}
