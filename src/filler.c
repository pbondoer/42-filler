/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pierre@bondoer.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:17:39 by pbondoer          #+#    #+#             */
/*   Updated: 2018/02/15 19:32:56 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>

t_token		read_token(char *line, int offset)
{
	t_token	token;
	int		i;

	line = ft_strchr(line, ' ') + 1;
	token.height = ft_atoi(line);
	token.width = ft_atoi(ft_strchr(line, ' '));
	token.size = token.height * token.width;
	if (offset)
	{
		get_next_line(0, &line);
		ft_strdel(&line);
	}
	token.data = ft_memalloc(token.height * sizeof(char *));
	i = 0;
	while (i < token.height)
	{
		get_next_line(0, &line);
		token.data[i] = line + offset;
		i++;
	}
	return (token);
}

void		init(t_filler *filler)
{
	t_point p;

	p.y = 0;
	while (p.y < filler->board.height)
	{
		p.x = 0;
		while (p.x < filler->board.width)
		{
			if (filler->board.data[p.y][p.x] == filler->player.id)
				filler->player.start = p;
			else if (filler->board.data[p.y][p.x] == filler->enemy.id)
				filler->enemy.start = p;
			p.x++;
		}
		p.y++;
	}
	filler->target.x = (filler->enemy.start.x - filler->player.start.x < 0 ?
			0 : filler->board.width - 1);
	filler->target.y = (filler->enemy.start.y - filler->player.start.y < 0 ?
			0 : filler->board.height - 1);
	filler->inited = 1;
}

void		filler_loop(t_filler filler)
{
	char	*line;
	int		res;

	while ((res = get_next_line(0, &line)) > -1)
	{
		if (!line)
			continue;
		if (!ft_strncmp(line, "Plateau ", 8))
		{
			filler.board = read_token(line, 4);
			if (!filler.inited)
				init(&filler);
		}
		else if (!ft_strncmp(line, "Piece ", 6))
		{
			filler.token = read_token(line, 0);
			place(filler);
		}
		ft_strdel(&line);
	}
}

int			main(void)
{
	t_filler	filler;
	char		*line;

	line = NULL;
	filler.inited = 0;
	if (get_next_line(0, &line) && line && !ft_strncmp(line, "$$$ exec p", 9)
			&& (line[10] == '1' || line[10] == '2'))
	{
		filler.player.id = (line[10] == '1' ? 'O' : 'X');
		filler.enemy.id = (line[10] == '1' ? 'X' : 'O');
		ft_strdel(&line);
		filler_loop(filler);
	}
	else
		return (1);
	return (0);
}
