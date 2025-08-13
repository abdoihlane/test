/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_plus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:49:10 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/13 11:49:49 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_wlist(t_wlist **list)
{
	t_wlist	*curr;
	t_wlist	*next;

	if (!list || !*list)
		return ;
	curr = *list;
	while (curr)
	{
		next = curr->next;
		ft_free_single(curr);
		curr = next;
	}
	*list = NULL;
}

void	free_red_list(t_red_list **list)
{
	t_red_list	*curr;
	t_red_list	*next;

	if (!list || !*list)
		return ;
	curr = *list;
	while (curr)
	{
		next = curr->next;
		if (curr->content)
			ft_free_single(curr->content);
		ft_free_single(curr);
		curr = next;
	}
	*list = NULL;
}
