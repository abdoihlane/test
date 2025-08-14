/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:57:53 by salhali           #+#    #+#             */
/*   Updated: 2025/08/14 20:59:17 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_save	*g_save = NULL;

t_save	**save_add(void)
{
	return (&g_save);
}

void	*ft_malloc(size_t size)
{
	void	*add;
	t_save	*head;

	add = malloc(size);
	if (!add)
		return (NULL);
	head = malloc(sizeof(t_save));
	if (!head)
	{
		free(add);
		return (NULL);
	}
	head->add = add;
	head->next = g_save;
	g_save = head;
	return (add);
}

int	is_malloc_ptr(void *ptr)
{
	t_save	*head;

	head = g_save;
	while (head)
	{
		if (head->add == ptr)
			return (1);
		head = head->next;
	}
	return (0);
}

void	ft_free_single(void *ptr)
{
	t_save	*head;
	t_save	*prev;

	head = g_save;
	prev = NULL;
	if (!ptr)
		return ;
	while (head)
	{
		if (head->add == ptr)
		{
			if (prev)
				prev->next = head->next;
			else
				g_save = head->next;
			free(head->add);
			free(head);
			return ;
		}
		prev = head;
		head = head->next;
	}
	if (ptr)
		free(ptr);
}

void	ft_free_all(void)
{
	t_save	*head;
	t_save	*temp;

	head = g_save;
	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->add)
		{
			free(temp->add);
			temp->add = NULL;
		}
		free(temp);
	}
	g_save = NULL;
}
