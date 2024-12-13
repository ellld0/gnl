/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 00:18:54 by gabriede          #+#    #+#             */
/*   Updated: 2024/12/13 04:26:50 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

// # define read(fd, buffer, bytes) mock_read(fd, buffer, bytes);

typedef struct buf_list
{
	char			*buffer;
	struct buf_list	*next;
}	t_list;

//  size_t	mock_read(int fd, void *buf, size_t count); // remova
char	*get_next_line(int fd);
int		ft_strlen_n(t_list *node);
void	ft_create_list(t_list **head, int fd);
t_list	*ft_lstlast(t_list *node);
void	ft_addnode(t_list **head, char *str);
int		ft_check_line(t_list *node);
char	*ft_get_line(t_list *node);
void	ft_new_line(t_list *node, char *next_line);
void	fresh_list(t_list **head);
void	ft_clear_list(t_list **head, t_list *clean_node, char *buffer);

#endif // GET_NEXT_LINE_H