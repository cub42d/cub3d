# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 11:11:22 by hmoon             #+#    #+#              #
#    Updated: 2022/07/21 03:23:53 by hmoon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:=	cub3D
VPATH				:=	$(shell ls -R)

CC					:=	cc
CFLAGS				:=	-Wall -Wextra -Werror
RM					:=	rm -rf

#	mlx
LIBMLX_DIR			:=	mlx
LIBMLX_INCLUDE		:=	$(LIBMLX_DIR)
LIBMLX				:=	libmlx.dylib

#	header
INCLUDE				:=	./include/

#	parser srcs
SRCS				+=

#	util srcs
SRCS				+=	ft_calloc.c ft_close.c ft_error_exit.c \
						ft_free.c ft_malloc.c ft_memset.c ft_open.c \
						ft_perror_exit.c ft_perror.c ft_putendl_fd.c \
						ft_putstr_fd.c ft_strchr.c ft_strlen.c ft_strutil.c \
						ft_strcmp.c get_next_line.c

OBJS_DIR			:=	./objs/
OBJS				:=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

.PHONY				:	all
all					:	$(LIBMLX) $(NAME)

$(NAME)				:	$(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(LIBMLX) $(OBJS) -o $@

$(OBJS_DIR)			:
	@if [ ! -d $(OBJS_DIR) ]; then \
		mkdir -p $(OBJS_DIR); \
	fi

$(OBJS_DIR)%.o		:	%.c
	$(CC) $(CFLAGS) -I$(LIBMLX_INCLUDE) -I$(INCLUDE) -c $< -o $@

$(LIBMLX)			:
	make -C $(LIBMLX_DIR) all
	cp $(LIBMLX_DIR)/$(LIBMLX) ./

.PHONY				:	clean
clean				:
	$(RM) $(OBJ_DIR)

.PHONY				:	fclean
fclean				:
	$(MAKE) clean
	$(RM) $(NAME) $(LIBMLX)
	make -C $(LIBMLX_DIR) clean

.PHONY				:	re
re					:
	$(MAKE) fclean
	$(MAKE) all
