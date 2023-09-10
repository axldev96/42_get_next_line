/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 07:52:22 by acaceres          #+#    #+#             */
/*   Updated: 2023/09/10 05:20:21 by acaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	create_list(int fd, t_list **lst);
static char	*set_line(t_list **lst, char *line);

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) == -1)
		return (ft_lstclear(&lst, free), NULL);
	create_list(fd, &lst);
	line = set_line(&lst, line);
	if (!line)
		return (NULL);
	return (line);
}

static void	create_list(int fd, t_list **lst)
{
	t_list	*node;
	char	*buff;
	int		_r;

	_r = 1;
	node = NULL;
	if (*lst && (*lst)->nl != -1)
		return ;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (ft_lstclear(lst, free));
	while (_r > 0)
	{
		_r = read(fd, buff, BUFFER_SIZE);
		if (_r == -1)
			return (free(buff), ft_lstclear(lst, free));
		buff[_r] = '\0';
		node = create_node(buff);
		if (!node)
			return (free(buff), ft_lstclear(lst, free));
		ft_lstadd_back(lst, node);
		if (node->nl != -1)
			return (free(buff));
	}
	free(buff);
}

static ssize_t	line_len(t_list **lst)
{
	t_list	*tmp;
	ssize_t	len;

	len = 0;
	if (!*lst)
		return (0);
	tmp = *lst;
	while (tmp)
	{
		if (tmp->nl == -1)
			len += tmp->len;
		else
			return (len += tmp->nl, ++len);
		tmp = tmp->next;
	}
	return (len);
}

static	char
	*fill_line(t_list **lst, t_list *tmp, t_list *new_lst, char *line)
{
	int	i;
	int	j;

	j = 0;
	while (tmp)
	{
		i = -1;
		while (tmp->content[++i])
		{
			if (tmp->content[i] == '\n')
			{
				line[j++] = tmp->content[i];
				line[j] = '\0';
				new_lst = create_node(&tmp->content[++i]);
				if (!new_lst)
					return (NULL);
				return (ft_lstclear(lst, free),
					ft_lstadd_back(lst, new_lst), line);
			}
			line[j++] = tmp->content[i];
		}
		tmp = tmp->next;
	}
	return (ft_lstclear(lst, free), line[j] = '\0', line);
}

static char	*set_line(t_list **lst, char *line)
{
	t_list	*new_lst;
	t_list	*tmp;

	tmp = NULL;
	new_lst = NULL;
	if (!*lst)
		return (NULL);
	tmp = *lst;
	line = malloc(sizeof(char) * (line_len(lst) + 1));
	if (!line)
		return (ft_lstclear(lst, free), NULL);
	line = fill_line(lst, tmp, new_lst, line);
	if (!line || line[0] == '\0')
		return (free(line), ft_lstclear(lst, free), NULL);
	return (line);
}
