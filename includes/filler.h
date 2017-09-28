/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pierre@bondoer.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:20:45 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/28 16:01:07 by pbondoer         ###   ########.fr       */
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
	char		player;
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

#endif
