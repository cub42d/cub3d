# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 11:11:22 by hmoon             #+#    #+#              #
#    Updated: 2022/07/17 15:18:40 by hyunkkim         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME				:=	cub3D
VPATH				:=	$(shell ls -R)

CC					:=	cc
CFLAGS				:=	-Wall -Wextra -Werror
RM					:=	rm -f

#	mlx
LIBMLX_DIR			:=	mlx
LIBMLX_INCLUDE		:=	$(LIBMLX_DIR)
LIBMLX				:=	libmlx.dylib

#	header
INCLUDE				:=	./include/
INCLUDE_FILES		:=	$(addsuffix .h, $(addprefix $(INCLUDE), \
						ray_casting))
#	srcs
SRCS				:=	$(addsuffix .c, \
						main)

OBJS_DIR			:=	./objs/
OBJS				:=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

.PHONY				:	all
all					:	$(LIBMLX) $(NAME)

$(NAME)				:	$(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBMLX) -o $@

$(OBJ_DIR)			:
	@if [ ! -d $(OBJ_DIR) ]; then \
		mkdir -p $(OBJ_DIR); \
	fi

$(OBJS_DIR)%.o		:	%.c
	$(CC) $(CFLAGS) -I$(LIBMLX_INCLUDE) -I$(INCLUDE) -c $< -o $@

$(LIBFT)			:
	make -C $(LIBFT_DIR) all

$(LIBMLX)			:
	make -C $(LIBMLX_DIR) all
	cp $(LIBMLX_DIR)/$(LIBMLX) ./

.PHONY				:	clean
clean				:
	$(RM) $(OBJS)

.PHONY				:	fclean
fclean				:
	$(MAKE) clean
	$(RM) $(NAME) $(LIBMLX)
	make -C $(LIBMLX_DIR) clean

.PHONY				:	re
re					:
	$(MAKE) fclean
	$(MAKE) all
