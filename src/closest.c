/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:28:23 by pbondoer          #+#    #+#             */
/*   Updated: 2018/03/01 09:51:53 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdlib.h>

void		create_arrays(t_filler *filler)
{
	int		size;

	if (filler->buf_p)
		ft_memdel((void **)&filler->buf_p);
	if (filler->buf_e)
		ft_memdel((void **)&filler->buf_e);
	size = filler->board.size;
	if (!(filler->buf_p = ft_memalloc(size * sizeof(t_point))) ||
		!(filler->buf_e = ft_memalloc(size * sizeof(t_point))))
		exit(1);
	ft_bzero(filler->buf_p, size * sizeof(t_point));
	ft_bzero(filler->buf_e, size * sizeof(t_point));
}

void		populate_closest_array(t_filler *filler)
{
	t_point	point;

	create_arrays(filler);
	filler->p_count = 0;
	filler->e_count = 0;
	point.y = 0;
	while (point.y < filler->board.height)
	{
		point.x = 0;
		while (point.x < filler->board.width)
		{
			if (filler->board.data[point.y][point.x] == filler->player.id)
				filler->buf_p[filler->p_count++] = point;
			else if (filler->board.data[point.y][point.x] == filler->enemy.id)
				filler->buf_e[filler->e_count++] = point;
			point.x++;
		}
		point.y++;
	}
}

inline int	dist(t_point a, t_point b)
{
	return (ft_max(a.x, b.x) - ft_min(a.x, b.x) +
			ft_max(a.y, b.y) - ft_min(a.y, b.y));
}

t_point		closest_pair(t_filler filler)
{
	int		p_cur;
	int		e_cur;
	t_point	temp;
	t_point	p;
	int		last_dist;

	populate_closest_array(&filler);
	last_dist = filler.board.size;
	p_cur = 0;
	while (p_cur < filler.p_count)
	{
		e_cur = 0;
		while (e_cur < filler.e_count)
		{
			if (dist(filler.buf_p[p_cur], filler.buf_e[e_cur]) <= last_dist &&
					place_around(filler, filler.buf_p[p_cur], &temp))
			{
				p = temp;
				last_dist = dist(filler.buf_p[p_cur], filler.buf_e[e_cur]);
			}
			e_cur++;
		}
		p_cur++;
	}
	return (last_dist == filler.board.size ? find_placement(filler) : p);
}
