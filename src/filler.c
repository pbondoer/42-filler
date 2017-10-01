/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pierre@bondoer.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:17:39 by pbondoer          #+#    #+#             */
/*   Updated: 2017/10/01 06:50:53 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>
#include <fcntl.h>

int fd;

int			main()
{
	t_filler	filler;
	char		*line;

	line = NULL;
	fd = open("/dev/ttys004", O_WRONLY);
	dprintf(fd, "\033c--- NEW EXECUTION ---\n\n"); // clear terminal
	if (get_next_line(0, &line) && line && !ft_strncmp(line, "$$$ exec p", 9)
			&& (line[10] == '1' || line[10] == '2'))
	{
		dprintf(fd, "* [%s]\n", line);
		if (line[10] == '1')
			filler.player = 'O';
		else
			filler.player = 'X';
		dprintf(fd, "> PLAYER > %c as %c\n", line[10], filler.player);
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

void		filler_loop(t_filler filler)
{
	char *line;

	while (get_next_line(0, &line) && line)
	{
		dprintf(fd, "\n> LOOP\n");
		dprintf(fd, "* [%s]\n", line);
		if (!ft_strncmp(line, "Plateau ", 8))
			filler.board = read_token(line, 4);
		if (!ft_strncmp(line, "Piece ", 6))
			filler.token = read_token(line, 0);
		//
		ft_strdel(&line);
	}
}

t_token		read_token(char *line, int offset)
{
	t_token	token;
	int		i;

	token.height = ft_atoi(line = ft_strchr(line, ' ') + 1);
	token.width = ft_atoi(ft_strchr(line, ' '));
	if (offset)
	{
		get_next_line(0, &line);
		ft_strdel(&line);
	}
	dprintf(fd, "\n> TOKEN > allocating %d x %d\n", token.height, token.width);
	if (!(token.data = ft_memalloc(token.height * sizeof(char *))))
		dprintf(fd, "ERROR\n");
	i = 0;
	while (i < token.height)
	{
		get_next_line(0, &line);
		dprintf(fd, "> TOKEN > %d > [%s]\n", i, line + offset);
		token.data[i] = line + offset;
		i++;
	}
	return (token);
}
