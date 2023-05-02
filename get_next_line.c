/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 07:52:22 by acaceres          #+#    #+#             */
/*   Updated: 2023/05/02 09:24:10 by acaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	ft_set_lst(int fd, t_list **lst);

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;

	line = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (ft_lstclear(&lst, free), NULL);
	ft_set_lst(fd, &lst);
	ft_lstprint(lst);
	return (line);
}

int	ft_set_lst(int fd, t_list **lst)
{
	int		_r;
	t_list	*node;

	_r = 0;
	node = NULL;
	while (1)
	{
		node = (t_list *)malloc(sizeof(t_list));
		if (!node)
			return (ft_lstclear(lst, free), 0);
		node->content = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!node->content)
			return (free(node), ft_lstclear(lst, free), 0);
		_r = read(fd, node->content, BUFFER_SIZE);
		if (_r == 0)
      break;
		if (_r < 0)
			return (free(node), ft_lstclear(lst, free), 0);
		node->content[_r] = 0;
		ft_lstadd_back(lst, node);
		if (ft_find_line_break(node) == 1)
			break ;
		node = node->next;
	}
	return (1);
}

