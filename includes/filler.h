/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pierre@bondoer.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:20:45 by pbondoer          #+#    #+#             */
/*   Updated: 2018/02/15 14:04:07 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "get_next_line.h"

# define TTY "/dev/ttys000"

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
	char		id_alt;
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
	t_point		strategy;
	t_token		board;
	t_token		token;
}				t_filler;

/*
** Framework to build a player
*/

void			filler_loop(t_filler filler);
t_token			read_token(char *line, int offset);

#endif
