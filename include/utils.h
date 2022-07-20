/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 20:34:25 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/20 22:21:49 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stddef.h>

void	*ft_calloc(size_t count, size_t size);
void	ft_close(int fd);
void	ft_free(void **ptr);
void	*ft_malloc(size_t size);
int		ft_open(const char *file, int flags);
void	ft_perror(const char *s, int errno);
void	ft_perror_exit(const char *s, unsigned int exit_status);
void	ft_putstr_fd(const char *s, int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memset(void *b, int c, size_t len);
int		get_next_line(int fd, char **line);

#endif