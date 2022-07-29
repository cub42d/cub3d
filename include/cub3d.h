/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 03:13:19 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/30 04:50:22 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parser.h"
# include "vu.h"
# include "macro.h"

typedef struct s_data	t_data;

struct s_data
{
	t_view			*vu;
	t_map			*map;
};

int		key_down_event(int keycode, t_data *data);
int		mouse_move_event(int x, int y, t_data *data);
void	render(t_data *data);

#endif