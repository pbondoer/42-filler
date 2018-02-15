/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pierre@bondoer.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:17:39 by pbondoer          #+#    #+#             */
/*   Updated: 2018/02/15 17:31:09 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define CLS                "\033c"

int fd;

int			main()
{
	t_filler	filler;
	char		*line;

	line = NULL;
	filler.inited = 0;
	fd = open(TTY, O_WRONLY);
	dprintf(fd, CLS "--- NEW EXECUTION ---\n\n"); // clear terminal
	if (get_next_line(0, &line) && line && !ft_strncmp(line, "$$$ exec p", 9)
			&& (line[10] == '1' || line[10] == '2'))
	{
		dprintf(fd, ANSI_COLOR_RED "|%s|\n", line);
		if (line[10] == '1')
		{
			filler.player.id = 'O';
			filler.player.id_alt = 'o';
			filler.enemy.id = 'X';
			filler.enemy.id_alt = 'x';
		}
		else
		{
			filler.player.id = 'X';
			filler.player.id_alt = 'x';
			filler.enemy.id = 'O';
			filler.enemy.id_alt = 'o';
		}
		dprintf(fd, ANSI_COLOR_GREEN "> PLAYER > %c as %c\n", line[10], filler.player.id);
		ft_strdel(&line);
		filler_loop(filler);
	}
	else
	{
		dprintf(fd, "error: [%s]\n", line);
		return (1);
	}
	return (0);
}

// TODO: free previous tokens
void		init(t_filler *filler)
{
	int x;
	int y;

	dprintf(fd, ANSI_COLOR_YELLOW "\n> INIT\n");
	y = 0;
	while (y < filler->board.height)
	{
		x = 0;
		while (x < filler->board.width)
		{
			if (filler->board.data[y][x] == filler->player.id)
			{
				filler->player.start.x = x;
				filler->player.start.y = y;
				dprintf(fd, ANSI_COLOR_GREEN "> PLAYER   > %3d; %3d\n", x, y);
			}
			else if (filler->board.data[y][x] == filler->enemy.id)
			{
				filler->enemy.start.x = x;
				filler->enemy.start.y = y;
				dprintf(fd, ANSI_COLOR_GREEN "> ENEMY    > %3d; %3d\n", x, y);
			}
			x++;
		}
		y++;
	}
	filler->strategy.x = (filler->enemy.start.x - filler->player.start.x < 0 ? 0 : filler->board.width - 1);
	filler->strategy.y = (filler->enemy.start.y - filler->player.start.y < 0 ? 0 : filler->board.height - 1);
	dprintf(fd, ANSI_COLOR_GREEN "> STRATEGY > %3d; %3d\n", filler->strategy.x, filler->strategy.y);
	filler->inited = 1;
}

int			position_valid(t_filler filler, t_point point)
{
	return (point.x >= 0 && point.y >= 0 &&
			point.x < filler.board.width && point.y < filler.board.height);
}

void		populate_closest_array(t_filler filler, t_point **player,
		t_point **enemy, int *p_count, int *e_count)
{
	t_point	point;

	if (*player == NULL)
		*player = ft_memalloc(*p_count * sizeof(t_point));
	if (*enemy == NULL)
		*enemy = ft_memalloc(*e_count * sizeof(t_point));
	ft_bzero(*player, *p_count * sizeof(t_point));
	ft_bzero(*enemy, *e_count * sizeof(t_point));
	*p_count = 0;
	*e_count = 0;
	point.y = 0;
	while (point.y < filler.board.height)
	{
		point.x = 0;
		while (point.x < filler.board.width)
		{
			if (filler.board.data[point.y][point.x] == filler.player.id)
				(*player)[(*p_count)++] = point;
			else if (filler.board.data[point.y][point.x] == filler.enemy.id)
				(*enemy)[(*e_count)++] = point;
			point.x++;
		}
		point.y++;
	}
	
	dprintf(fd, ANSI_COLOR_GREEN "> POINTS > p: %d - e: %d\n", *p_count, *e_count);
}

inline int	dist(t_point a, t_point b)
{
	return (ft_max(a.x, b.x) - ft_min(a.x, b.x) +
			ft_max(a.y, b.y) - ft_min(a.y, b.y));
}

int			try_place(t_filler filler, t_point point)
{
	int x;
	int y;
	int count;

	if (point.y + filler.token.height > filler.board.height ||
		point.x + filler.token.width > filler.board.width)
		return (2);

	//dprintf(fd, ANSI_COLOR_YELLOW "\n> TRY\n");

	count = 0;
	y = 0;
	while (y < filler.token.height)
	{
		x = 0;
		while (x < filler.token.width)
		{
			if (filler.token.data[y][x] == '*' &&
					(filler.board.data[point.y + y][point.x + x] == filler.enemy.id))
				return (1);
			if (filler.token.data[y][x] == '*' &&
					(filler.board.data[point.y + y][point.x + x] == filler.player.id))
				count++;
			if (count > 1)
				return (1);
			x++;
		}
		y++;
	}
	if (count < 1)
		return (1);
	return (0);
}

int		place_around(t_filler filler, t_point p, t_point *result)
{
	t_point		offset;

	offset.y = 0;
	while (offset.y < filler.token.height)
	{
		offset.x = 0;
		while (offset.x < filler.token.width)
		{
			result->x = p.x - offset.x;
			result->y = p.y - offset.y;
			if (filler.token.data[offset.y][offset.x] == '*' &&
					position_valid(filler, *result) &&
					!try_place(filler, *result))
			{
				return (1);
			}
			offset.x++;
		}
		offset.y++;
	}
	return (0);
}

t_point		find_placement(t_filler filler)
{
	t_point		p;
	t_point		temp;

	dprintf(fd, ANSI_COLOR_YELLOW "\n> FIND\n");
	p.y = filler.strategy.y;
	while (filler.strategy.y == 0 ? p.y < filler.board.height : p.y >= 0)
	{
		p.x = filler.strategy.x;
		while(filler.strategy.x == 0 ? p.x < filler.board.width : p.x >= 0)
		{
			if (filler.board.data[p.y][p.x] == filler.player.id)
			{
				if (place_around(filler, p, &temp))
				{
					dprintf(fd, ANSI_COLOR_GREEN "> FINAL     > %3d; %3d\n", temp.y, temp.x);
					return (temp);
				}
			}
			p.x += (filler.strategy.x == 0 ? 1 : -1);
		}
		p.y += (filler.strategy.y == 0 ? 1 : -1);
	}
	return (p);
}

t_point		closest_pair(t_filler filler)
{
	static t_point *player = NULL;
	static t_point *enemy = NULL;
	int		p_count;
	int		e_count;
	int		p_cur;
	int		e_cur;
	t_point	temp;
	t_point	p;
	t_point	e;
	int		last_dist;

	dprintf(fd, ANSI_COLOR_YELLOW "\n> CLOSEST\n");

	p_count = filler.board.size;
	e_count = filler.board.size;
	populate_closest_array(filler, &player, &enemy, &p_count, &e_count);
	last_dist = filler.board.size;
	p_cur = 0;
	while (p_cur < p_count)
	{
		e_cur = 0;
		while (e_cur < e_count)
		{
			if (dist(player[p_cur], enemy[e_cur]) <= last_dist &&
					place_around(filler, player[p_cur], &temp))
			{
				p = temp;
				e = enemy[e_cur];
				last_dist = dist(player[p_cur], enemy[e_cur]);
			}
			e_cur++;
		}
		p_cur++;
	}

	dprintf(fd, ANSI_COLOR_YELLOW "> CLOSEST > %3d;%3d - %3d;%3d\n", p.x, p.y, e.x, e.y);

	if (last_dist == filler.board.size)
	{
		// couldnt find a closest match, try to fill the baord instead
		dprintf(fd, ANSI_COLOR_RED "> CLOSEST > ERROR > No placement found\n");
		p = find_placement(filler);
	}

	return (p);
}

void		place(t_filler filler)
{
	t_point		candidate;

	dprintf(fd, ANSI_COLOR_YELLOW "\n> PLACE\n");
	candidate = closest_pair(filler);

	if (!position_valid(filler, candidate))
	{
		dprintf(fd, ANSI_COLOR_MAGENTA "\n> ERROR > No valid placement found\n");
		candidate.x = 0;
		candidate.y = 0;
		exit(0);
	}
	dprintf(fd, ANSI_COLOR_GREEN "\n> SEND > %3d; %3d\n", candidate.y, candidate.x);
	dprintf(fd, ANSI_COLOR_RED "%d %d\n", candidate.y, candidate.x);
	ft_putnbr(candidate.y);
	ft_putchar(' ');
	ft_putnbr(candidate.x);
	ft_putchar('\n');
}

void		filler_loop(t_filler filler)
{
	char	*line;
	int		res;

	while ((res = get_next_line(0, &line)) > -1)
	{
		if (!line)
		{
			continue;
		}
		dprintf(fd, ANSI_COLOR_YELLOW "\n> LOOP\n");
		dprintf(fd, ANSI_COLOR_RED "|%s|\n", line);
		if (!ft_strncmp(line, "Plateau ", 8))
		{
			dprintf(fd, ANSI_COLOR_YELLOW "\n> BOARD");
			filler.board = read_token(line, 4);
			if (!filler.inited)
				init(&filler);
		}
		else if (!ft_strncmp(line, "Piece ", 6))
		{
			dprintf(fd, ANSI_COLOR_YELLOW "\n> PIECE");
			filler.token = read_token(line, 0);
			place(filler);
		}
		ft_strdel(&line);
	}

	dprintf(fd, ANSI_COLOR_MAGENTA "\n> END > %d\n", res);
}

t_token		read_token(char *line, int offset)
{
	t_token	token;
	int		i;

	token.height = ft_atoi(line = ft_strchr(line, ' ') + 1);
	token.width = ft_atoi(ft_strchr(line, ' '));
	token.size = token.height * token.width;
	if (offset)
	{
		get_next_line(0, &line);
		ft_strdel(&line);
	}
	dprintf(fd, ANSI_COLOR_YELLOW "\n> TOKEN > allocating %d x %d\n", token.height, token.width);
	if (!(token.data = ft_memalloc(token.height * sizeof(char *))))
		dprintf(fd, "ERROR\n");
	i = 0;
	while (i < token.height)
	{
		get_next_line(0, &line);
		dprintf(fd, ANSI_COLOR_CYAN "> TOKEN > %3d > [%s]\n", i, line + offset);
		token.data[i] = line + offset;
		i++;
	}
	return (token);
}
