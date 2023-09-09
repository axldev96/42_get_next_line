/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 07:58:06 by acaceres          #+#    #+#             */
/*   Updated: 2023/09/09 05:42:32 by acaceres         ###   ########.fr       */
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

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	if (!lst->next)
		return (lst);
	return (ft_lstlast(lst->next));
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tail;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = ft_lstlast(*lst);
	tail->next = new;
}

t_list	*create_node(char *content, ssize_t *index)
{
	int	i;
	t_list	*node;

	i = 0;
	node = NULL;
	if (!content)
		return (NULL);
	while (content[i])
		i++;
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = malloc(sizeof(char) * (i + 1));
	if (!node->content)
		return (free(node), NULL);
	i = 0;
	node->nl = -1;
	node->len = -1;
	while (content[i])
	{
		if (node->nl == -1 && content[i] == '\n')
			node->nl = i;
		node->content[i] = content[i];
		i++;
	}
	node->content[i] = '\0';
	return (node->len = i, node->index = (*index)++, node->next = NULL, node);
}
