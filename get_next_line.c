/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 07:52:22 by acaceres          #+#    #+#             */
/*   Updated: 2023/05/02 22:02:38 by acaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	ft_set_lst(int fd, t_list **lst);
char  *ft_set_line(t_list **lst);

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;
  int       set;

	line = 0;
  set = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (ft_lstclear(&lst, free), NULL);
	set = ft_set_lst(fd, &lst);
  if (!set)
    return (ft_lstclear(&lst, free), NULL);
  line = ft_set_line(&lst);
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
			return (free(node), 0);
		_r = read(fd, node->content, BUFFER_SIZE);
		if (_r <= 0)
			return (free(node->content), free(node), 0);
		node->content[_r] = 0;
		ft_lstadd_back(lst, node);
		if (ft_find_line_break(node) == 1)
			break ;
		node = node->next;
	}
	return (1);
}

char  *ft_set_line(t_list **lst)
{
  t_list  *last_node;
  t_list  *current;
  char  *line;
  int   i;
  int   j;

  line = 0;
  i = 0;
  j = 0;
  current = *lst;
  last_node = *lst;
  while (last_node->next)
  {
    last_node = last_node->next;
    j++;
  }
  while (last_node->content[i] && last_node->content[i + 1] != '\n')
    i++;
  line = (char *)malloc(((BUFFER_SIZE * j) + i) * sizeof(char));
  if (!line)
    return (0);
  i = 0;
  j = 0;
  while (current)
  {
    while (current->content[i])
    {
      if (current->content[i] == '\n')
      {
        line[j++] = current->content[i++];
        line[j] = 0;
        return (line);
      }
      line[j++] = current->content[i++];
    }
    i = 0;
    current = current->next;
  }
  line[j] = 0;
  return (line);
}
