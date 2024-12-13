/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:57:55 by gabriede          #+#    #+#             */
/*   Updated: 2024/12/13 04:24:11 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_addnode(t_list **head, char *str)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_lstlast(*head);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*head = new_node;
	else
		last_node->next = new_node;
	new_node->buffer = str;
	new_node->next = NULL;
}

void	fresh_list(t_list **head)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		j;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (buffer == NULL || clean_node == NULL)
		return ;
	last_node = ft_lstlast(*head);
	i = 0;
	j = 0;
	while (last_node->buffer[i] && last_node->buffer[i] != '\n')
		i++;
	while (last_node->buffer[i] && last_node->buffer[++i])
		buffer[j++] = last_node->buffer[i];
	buffer[j] = 0;
	clean_node->buffer = buffer;
	clean_node->next = NULL;
	// printf("endereço de buffer = %p\n", buffer);
	// printf("endereço de clean_node = %p\n", clean_node);
	// printf("endereço de clean_node->buffer = %p\n", &clean_node->buffer);
	// printf("endereço de clean_node->buffer2 = %p\n", clean_node->buffer);
	// printf("endereço de clean_node->next = %p\n", clean_node->next);
	// printf("endereço de clean_node->buffer = %s\n", clean_node->buffer);
	ft_clear_list(head, clean_node, buffer);
}

char	*ft_get_line(t_list *node)
{
	int		size;
	char	*next_line;
	int		i;

	if (node == NULL)
		return (NULL);
	i = 0;
	size = ft_strlen_n(node);
	next_line = malloc(size + 1);
	while (i < size + 1)
	{
		next_line[i] = 0;
		i++;
	}
	if (next_line == NULL)
		return (NULL);
	ft_new_line(node, next_line);
	return (next_line);
}

void	ft_create_list(t_list **head, int fd)
{
	char	*buffer;
	int		read_bytes;

	while (ft_check_line(*head) == 0)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ;
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == 0)
		{
			free(buffer);
			return ;
		}
		if (read_bytes == -1)
		{
			// printf("endereço de *head = %p\n", *head);
			// printf("endereço de *head->buffer = %p\n", &(*head)->buffer);
			// printf("endereço de *head->buffer2 = %p\n", (*head)->buffer);
			// printf("endereço de *head->next = %p\n", &(*head)->next);
			// printf("head->buffer = %s\n", (*head)->buffer);
			// printf("head->next = %p\n", (*head)->next);
			//free((*head)->buffer);
			//free((*head));
			// printf("POS\n");
			// printf("endereço de *head = %p\n", *head);
			// printf("endereço de *head->buffer = %p\n", &(*head)->buffer);
			// printf("endereço de *head->buffer2 = %p\n", (*head)->buffer);
			// printf("endereço de *head->next = %p\n", &(*head)->next);
			// printf("head->buffer = %s\n", (*head)->buffer);
			// printf("head->next = %p\n", (*head)->next);
			free(buffer);
			*head = NULL;
			return ;
		}
		buffer[read_bytes] = 0;
		ft_addnode(head, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	char			*response;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_create_list(&head, fd);
	if (head == NULL)
		return (NULL);
	response = ft_get_line(head);
	fresh_list(&head);
	return (response);
}
