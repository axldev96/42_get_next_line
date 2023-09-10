/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <acaceres@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 05:26:30 by acaceres          #+#    #+#             */
/*   Updated: 2023/09/10 05:29:05 by acaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# ifndef FD_MAX
#  define FD_MAX 1024
# endif
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_list {
	char			*content;
	ssize_t			nl;
	ssize_t			len;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
void	ft_find_line_break(t_list *node, ssize_t *size);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
t_list	*ft_lstlast(t_list *lst);
t_list	*create_node(char *content);

#endif
