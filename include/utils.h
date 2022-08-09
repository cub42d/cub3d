/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 20:34:25 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/09 21:14:07 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

void			*ft_calloc(size_t size);
void			ft_close(int fd);
void			ft_colision_angle(double *angle);
double			ft_deg2rad(double d);
void			ft_error_exit(char *s);
void			ft_exit(char *s);
double			ft_fov_v(double fov);
double			ft_fov_h(double fov);
void			ft_free(void **ptr);
void			ft_double_free(char ***ptr);
int				ft_iseq(char *s1, char *s2);
int				ft_isspace(char c);
int				ft_iszero(double d);
double			ft_l2dist(double x0, double y0, double x1, double y1);
void			*ft_malloc(size_t size);
int				ft_max(int a, int b);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memset(void *b, int c, size_t len);
int				ft_min(int a, int b);
int				ft_numsign(double d);
int				ft_open(const char *file, int flags);
void			ft_perror(const char *s, int errno);
void			ft_perror_exit(const char *s, unsigned int exit_status);
int				ft_print_err(char *str);
void			ft_putendl_fd(const char *s, int fd);
void			ft_putstr_fd(const char *s, int fd);
double			ft_rad2dig(double d);
char			**ft_split(const char *str, char *sep);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				ft_strlen(const char *s);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				get_next_line(int fd, char **line);

#endif
