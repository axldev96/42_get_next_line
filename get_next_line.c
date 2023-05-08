/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 07:52:22 by acaceres          #+#    #+#             */
/*   Updated: 2023/05/04 07:06:17 by acaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_set_lst(int fd, t_list **lst);
char    *ft_set_line(t_list **lst);

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;
	int				set_lst;

	line = 0;
	set_lst = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (ft_lstclear(&lst, free), NULL);
	set_lst = ft_set_lst(fd, &lst);
	if (!set_lst)
		return (ft_lstclear(&lst, free), NULL);
    line = ft_set_line(&lst);
	if (!line)
		return (ft_lstclear(&lst, free), NULL);
    // ft_lstprint(lst);
	return (line);
}

int	ft_set_lst(int fd, t_list **lst)
{
	int		_r;
	t_list	*node;

	_r = 0;
	node = 0;
	while (1)
	{
		if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
			return (0);
		node = (t_list *)malloc(sizeof(t_list));
		if (!node)
			return (0);
		node->content = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!node->content)
			return (free(node), 0);
		_r = read(fd, node->content, BUFFER_SIZE);
		if (_r == 0)
			return (free(node->content), free(node), 1);
		if (_r <= 0)
			return (free(node->content), free(node), 0);
		node->content[_r] = 0;
		node->next = NULL;
		ft_lstadd_back(lst, node);
		if (ft_find_line_break(node) == 1)
			break ;
		node = node->next;
	}
	return (1);
}

char    *ft_set_line(t_list **lst)
{
  char  *line;
  t_list    *current;
  int       i;
  int       j;

  line = 0;
  i = 0;
  j = 0;
  current = *lst;
  while (current)
  {
    while (current->content[i])
    {
      if (current->content[i])
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
