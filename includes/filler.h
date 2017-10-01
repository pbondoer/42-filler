/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pierre@bondoer.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:20:45 by pbondoer          #+#    #+#             */
/*   Updated: 2017/10/01 06:50:27 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "get_next_line.h"

# define TTY "/dev/pts/3"

/*
** Standard structure for both the board and pieces
*/

typedef struct	s_token
{
	int			width;
	int			height;
	char		**data;
}				t_token;

/*
** Everything
*/

typedef struct	s_filler
{
	char		player;
	t_token		board;
	t_token		token;
}				t_filler;

/*
** Framework to build a player
*/

void			filler_loop(t_filler filler);
t_token			read_token(char *line, int offset);

#endif
