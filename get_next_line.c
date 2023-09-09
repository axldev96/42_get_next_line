/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 07:52:22 by acaceres          #+#    #+#             */
/*   Updated: 2023/09/09 05:19:06 by acaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	create_list(int fd, t_list **lst);
static char	*set_line(t_list **lst, char *line);

void	print_list(t_list *list)
{
	if (!list)
		return ;
	printf("node->index: %li\tnode->content: %s\tnode->nl: %li\tnode->len: %li\n",
		list->index, list->content, list->nl, list->len);
	print_list(list->next);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) == -1)
		return (ft_lstclear(&lst, free), NULL);
	create_list(fd, &lst);
	//print_list(lst);
	line = set_line(&lst, line);
	if (!line)
		return (NULL);
	//printf("\n============after line================\n");
	//print_list(lst);
	//ft_lstclear(&lst, free);
	return (line);
}

static void	create_list(int fd, t_list **lst)
{
	int	_r;
	ssize_t	index;
	char	*buff;
	t_list	*node;

	_r = 0;
	index = 1;
	node = NULL;
	if (*lst && (*lst)->nl != -1)
		return ;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (ft_lstclear(lst, free));
	while (1)
	{
		_r = read(fd, buff, BUFFER_SIZE);
		if (_r == 0)
			return (free(buff));
		if (_r == -1)
			return (free(buff), ft_lstclear(lst, free));
		buff[_r] = '\0';
		node = create_node(buff, &index);
		if (!node)
			return (free(buff), ft_lstclear(lst, free));
		ft_lstadd_back(lst, node);
		if (node->nl != -1)
			return (free(buff));
		node = node->next;
	}
	free(buff);
}

static char	*set_line(t_list **lst, char *line)
{
	t_list	*new_lst;
	t_list	*tmp;
	//t_list	*del_tmp;
	ssize_t	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	tmp = NULL;
	//del_tmp = NULL;
	new_lst = NULL;
	len = 0;
	if (!*lst)
		return (NULL);
	tmp = *lst;
	while (tmp)
	{
		if (tmp->nl == -1)
			len += tmp->len;
		else
		{
			len += tmp->nl;
			len++;
			break ;
		}
		tmp = tmp->next;
	}
	if (len <= 0)
		return (ft_lstclear(lst, free), NULL);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (ft_lstclear(lst, free), NULL);
	tmp = *lst;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == '\n')
			{
				line[j++] = tmp->content[i];
				line[j] = '\0';
				len = 1;
				new_lst = create_node(&tmp->content[++i], &len);
				ft_lstclear(lst, free);
				*lst = new_lst;
				return (line);
			}
			//printf("len: %li\ti:%i\tj:%i\n", len, i, j);
			//return (free(line), ft_lstclear(lst, free), NULL);
			line[j] = tmp->content[i];
			i++;
			j++;
		}
		tmp = tmp->next;
	}
	line[j] = '\0';
	if (line[0] == '\0')
		return (free(line), ft_lstclear(lst, free), NULL);
	ft_lstclear(lst, free);
	return (line);
}
