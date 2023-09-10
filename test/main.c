/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:59:41 by acaceres          #+#    #+#             */
/*   Updated: 2023/09/10 05:37:30 by acaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("41_no_nl", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("line: %s", line);
		free(line);
		if (!line)
			return (0);
	}
	return (0);
}
