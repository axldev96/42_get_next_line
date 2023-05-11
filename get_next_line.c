/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 07:52:22 by acaceres          #+#    #+#             */
/*   Updated: 2023/05/11 03:50:10 by acaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_set_lst(int fd, t_list **lst);
char	*ft_set_line(t_list **lst);
size_t	ft_setsize_lastnode(t_list *lst);
int		ft_fill_list(t_list **lst, t_list *last_node);

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;
	int				set_lst;
	int				list_filled;
	t_list			*last_node;

	line = 0;
	set_lst = 0;
	list_filled = 0;
	last_node = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (ft_lstclear(&lst, free), NULL);
	set_lst = ft_set_lst(fd, &lst);
	if (!set_lst)
		return (ft_lstclear(&lst, free), NULL);
	line = ft_set_line(&lst);
	if (!line)
		return (ft_lstclear(&lst, free), NULL);
	last_node = ft_lstlast(lst);
	list_filled = ft_fill_list(&lst, last_node);
	if (!list_filled)
		return (ft_lstclear(&lst, free), NULL);
	return (line);
}

int	ft_set_lst(int fd, t_list **lst)
{
	int		_r;
	t_list	*node;

	_r = 0;
	node = 0;
	while (!ft_find_line_break(ft_lstlast(*lst)))
	{
		node = (t_list *)malloc(sizeof(t_list));
		if (!node)
			return (0);
		node->content = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!node->content)
			return (free(node), 0);
		_r = read(fd, node->content, BUFFER_SIZE);
		if (_r == 0)
			return (free(node->content), free(node), 1);
		if (_r < 0)
			return (free(node->content), free(node), 0);
		node->content[_r] = 0;
		node->next = NULL;
		ft_lstadd_back(lst, node);
		node = node->next;
	}
	return (1);
}

char	*ft_set_line(t_list **lst)
{
	char	*line;
	t_list	*current;
	int		i;
	int		j;

	i = 0;
	j = 0;
	current = *lst;
	line = (char *)malloc((ft_setsize_lastnode(*lst) + 1) * sizeof(char));
	if (!line)
		return (0);
	while (current)
	{
		while (current->content[i])
		{
			if (current->content[i] == '\n')
				return (line[j++] = current->content[i++], line[j] = 0, line);
			line[j++] = current->content[i++];
		}
		i = 0;
		current = current->next;
	}
	line[j] = 0;
	if (!line[0])
		return (free(line), NULL);
	return (line);
}

size_t	ft_setsize_lastnode(t_list *lst)
{
	size_t	size;
	size_t	i;
	t_list	*node;

	if (!lst)
		return (0);
	size = 0;
	i = 0;
	node = lst;
	while (node)
	{
		while (node->content[i])
		{
			if (node->content[i] == '\n')
				return (++size);
			size++;
			i++;
		}
		i = 0;
		node = node->next;
	}
	return (size);
}

int	ft_fill_list(t_list **lst, t_list *last_node)
{
	t_list	*new_node;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	if (last_node->content[i] == '\n')
		i++;
	j = i;
	while (last_node->content[i])
		i++;
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->content = (char *)malloc((i - j + 1) * sizeof(char));
	if (!new_node->content)
		return (free(new_node), 0);
	i = 0;
	while (last_node->content[j])
		new_node->content[i++] = last_node->content[j++];
	return (new_node->next = 0, new_node->content[i] = 0,
		ft_lstclear(lst, free), ft_lstadd_back(lst, new_node), 1);
}
