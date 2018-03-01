/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pierre@bondoer.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:20:45 by pbondoer          #+#    #+#             */
/*   Updated: 2018/03/01 09:56:06 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "get_next_line.h"

/*
** Point
*/
typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

/*
** Player object
*/
typedef struct	s_player
{
	char		id;
	t_point		start;
}				t_player;

/*
** Standard structure for both the board and pieces
*/

typedef struct	s_token
{
	int			width;
	int			height;
	int			size;
	char		**data;
}				t_token;

/*
** Everything
*/

typedef struct	s_filler
{
	int			inited;
	t_player	player;
	t_player	enemy;
	t_point		target;
	t_token		board;
	t_token		token;
	t_point		*buf_p;
	int			p_count;
	t_point		*buf_e;
	int			e_count;
}				t_filler;

t_point			closest_pair(t_filler filler);
int				try_place(t_filler filler, t_point point);
void			place(t_filler filler);
int				place_around(t_filler filler, t_point p, t_point *result);
t_point			find_placement(t_filler filler);

#endif
