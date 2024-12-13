/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 00:21:38 by gabriede          #+#    #+#             */
/*   Updated: 2024/12/13 04:15:00 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_clear_list(t_list **head, t_list *clean_node, char *buffer)
{
	t_list	*temp;

	if (*head == NULL)
		return ;
	while (*head)
	{
		temp = (*head)->next;
		free((*head)->buffer);
		free(*head);
		*head = temp;
	}
	*head = NULL;
	if (clean_node->buffer[0])
		*head = clean_node;
	else
	{
		free(buffer);
		free(clean_node);
	}
}

void	ft_new_line(t_list *node, char *next_line)
{
	int	i;
	int	k;

	if (NULL == node)
		return ;
	k = 0;
	while (node)
	{
		i = 0;
		while (node->buffer[i])
		{
			if (node->buffer[i] == '\n')
			{
				next_line[k++] = '\n';
				next_line[k] = '\0';
				return ;
			}
			next_line[k++] = node->buffer[i++];
		}
		node = node->next;
	}
	next_line[k] = '\0';
}

int	ft_strlen_n(t_list *node)
{
	int	i;
	int	size;

	if (node == NULL)
		return (0);
	size = 0;
	while (node)
	{
		i = 0;
		while (node->buffer[i] != 0)
		{
			if (node->buffer[i] == '\n')
			{
				size++;
				return (size);
			}
			i++;
			size++;
		}
		node = node->next;
	}
	return (size);
}

int	ft_check_line(t_list *node)
{
	int	i;

	if (node == NULL)
		return (0);
	while (node != NULL)
	{
		i = 0;
		while (node->buffer[i] != 0 && i < BUFFER_SIZE)
		{
			if (node->buffer[i] == '\n')
				return (1);
			i++;
		}
		node = node->next;
	}
	return (0);
}

t_list	*ft_lstlast(t_list *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}
