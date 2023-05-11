/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 07:46:51 by acaceres          #+#    #+#             */
/*   Updated: 2023/05/08 15:16:17 by acaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

void	ft_lstprint(t_list *node)
{
	if (!node)
		write(1, "Node doesn't exist", 18);
	while (node)
	{
		while (*(char *)node->content)
			write(1, (char *)node->content++, 1);
		node = node->next;
	}
}

int	main(void)
{
	int		fd;
    char	*line;

	fd = open("the_bible.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("Line = %s", line);
		free(line);
	}
	close(fd);
	return (0);
}
