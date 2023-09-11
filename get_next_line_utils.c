/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 07:58:06 by acaceres          #+#    #+#             */
/*   Updated: 2023/09/11 04:03:46 by acaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
