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
#include <stdio.h>
#include <string.h>

int		ft_set_lst(int fd, t_list **lst);
char	*ft_set_line(t_list **lst);

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
ft_lstprint(lst);
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

char	*ft_set_line(t_list **lst)
{
	t_list	*new_node;
	t_list	*last_node;
	t_list	*current;
	char	*line;
	int		i;
	int		j;
  int   h;

	if (!*lst)
		return (0);
	line = 0;
	i = 0;
	j = 0;
  h = 0;
	new_node = 0;
	current = *lst;
	last_node = *lst;
	while (last_node->next)
	{
		last_node = last_node->next;
		j++;
	}
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	line = (char *)malloc(((BUFFER_SIZE * j) + i) * sizeof(char));
	if (!line)
		return (free(line), NULL);
	j = i + 2;
	while (last_node->content[i])
		i++;
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (free(line), NULL);
	new_node->content = (char *)malloc((i - 1 - j + 1) * sizeof(char));
	if (!new_node->content)
		return (free(new_node->content), free(new_node), free(line), NULL);
	new_node->next = NULL;
  while (j < i)
    new_node->content[h++] = last_node->content[j++];
  new_node->content[h] = 0;
	i = 0;
	j = 0;
	while (current)
	{
		while (current->content[i])
		{
			if (current->content[i] == '\n')
			{
				line[j++] = current->content[i++];
				line[j] = '\0';
        ft_lstclear(lst, free);
        ft_lstadd_back(lst, new_node);
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
