# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 11:11:22 by hmoon             #+#    #+#              #
#    Updated: 2022/07/30 04:51:35 by hmoon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:=	cub3D
VPATH				:=	$(shell ls -R)

CC					:=	cc
CFLAGS				:=	-Wall -Wextra -Werror -g
RM					:=	rm -rf

#	mlx
LIBMLX_DIR			:=	mlx
LIBMLX_INCLUDE		:=	$(LIBMLX_DIR)
LIBMLX				:=	libmlx.dylib

#	header
INCLUDE				:=	./include/

#	main srcs
SRCS				+=	main.c

#	view srcs
SRCS				+= $(addsuffix .c, draw_wall init_vu move_event \
						raycast_util render)

#	parser srcs
SRCS				+=	$(addsuffix .c, parse_main parse_texture parse_map)

#	utils srcs
SRCS				+=	$(addsuffix .c, ft_calloc ft_close ft_error_exit \
						ft_free ft_iseq ft_malloc ft_max ft_memcpy ft_memset \
						ft_min ft_open ft_perror_exit ft_perror ft_putendl_fd \
						ft_putstr_fd ft_strchr ft_strcmp ft_strlen ft_strutil \
						ft_split ft_strtrim ft_isspace ft_l2dist ft_print_err \
						ft_fov ft_deg2rad ft_iszero ft_rad2dig ft_numsign \
						ft_atoi get_next_line)

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
	@cp $(LIBMLX_DIR)/$(LIBMLX) ./

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
