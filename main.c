/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 07:46:51 by acaceres          #+#    #+#             */
/*   Updated: 2023/05/02 22:06:10 by acaceres         ###   ########.fr       */
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
	int	fd;

	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	return (0);
}
