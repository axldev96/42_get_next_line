/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <acaceres@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 05:24:19 by acaceres          #+#    #+#             */
/*   Updated: 2023/09/11 06:16:10 by acaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*link;

	if (!lst || !del)
		return ;
	current = *lst;
	link = 0;
	while (current)
	{
		link = current->next;
		del(current->content);
		free(current);
		current = link;
	}
	*lst = NULL;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;
	t_list	*tail;

	tail = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tail = tmp;
	tail->next = new;
}

t_list	*create_node(char *content)
{
	t_list	*node;
	int		i;

	i = 0;
	if (!content)
		return (NULL);
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	while (content[i])
		i++;
	node->content = malloc(sizeof(char) * (i + 1));
	if (!node->content)
		return (free(node), NULL);
	i = -1;
	node->nl = -1;
	node->len = -1;
	while (content[++i])
	{
		if (node->nl == -1 && content[i] == '\n')
			node->nl = i;
		node->content[i] = content[i];
	}
	node->content[i] = '\0';
	return (node->len = i, node->next = NULL, node);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		s1_len;
	int		s2_len;

	i = 0;
	s1_len = 0;
	s2_len = 0;
	if (!s2)
		return (0);
	if (!s1)
		s1 = "";
	while (s1[s1_len])
		s1_len++;
	while (s2[s2_len])
		s2_len++;
	new_str = malloc(((s1_len + s2_len) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	while (*s1)
		new_str[i++] = *s1++;
	while (*s2)
		new_str[i++] = *s2++;
	return (new_str[i] = '\0', new_str);
}

char	*buff_size_1(int fd, char *line, char *tmp)
{
	char	*buff;
	int		_r;

	_r = 1;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (_r > 0)
	{
		_r = read(fd, buff, BUFFER_SIZE);
		if (_r == -1)
			return (free(buff), NULL);
		buff[_r] = '\0';
		tmp = line;
		line = ft_strjoin_gnl(tmp, buff);
		if (!line)
			return (free(buff), NULL);
		free(tmp);
		if (buff[0] == '\n')
			break ;
	}
	free(buff);
	if (line[0] == '\0')
		return (free(line), NULL);
	return (line);
}
