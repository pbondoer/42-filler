/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pierre@bondoer.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:17:39 by pbondoer          #+#    #+#             */
/*   Updated: 2017/09/28 16:10:07 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>
#include <fcntl.h>

int			main()
{
	t_filler	filler;
	char		*line;
	int			fd;

	fd = open("./log", O_WRONLY);
	dprintf(fd, "\n--- NEW EXECUTION ---\n\n");
	if (get_next_line(1, &line) && line && !ft_strncmp(line, "$$$ exec p", 9)
			&& (line[10] == '1' || line[10] == '2'))
	{
		dprintf(fd, "success! p%c\n", line[10]);
		if (line[10] == '1')
			filler.player = 'O';
		else
			filler.player = 'X';
	}
	else
		return (1);

	(void)filler;

	return (0);
}
