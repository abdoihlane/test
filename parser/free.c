/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:46:56 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/07 16:58:04 by ahabibi-         ###   ########.fr       */
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
		// Note: content is owned by pars->content1, don't free it here
		free(curr);
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
			free(curr->content);
		free(curr);
		curr = next;
	}
	*list = NULL;
}
void	free_clist(t_cmd **list,int nb)
{
	t_cmd	*curr;
	t_cmd	*next;
	int		i;

	if (!list || !*list)
		return ;
	curr = *list;
	while (curr)
	{
		next = curr->next;
		// Free array
		if (curr->array)
		{
			i = 0;
			while (curr->array[i])
				free(curr->array[i++]);
			free(curr->array);
		}
		// Free cmd string
		if (curr->cmd)
			free(curr->cmd);
		// Free redirection list
		if (curr->file && nb == 0)
			free_red_list(&curr->file);
		// Free pars if present
		// if (curr->pars)
		// 	free_plist(&curr->pars);
		free(curr);
		curr = next;
	}
	*list = NULL;
}
void	free_plist(t_pars **par)
{
	t_pars	*p;
	int		i;

	if (!par || !*par)
		return ;
	p = *par;
	if (p->content1)
	{
		i = 0;
		while (p->content1[i])
			free(p->content1[i++]);
		free(p->content1);
	}
	free(p);
	*par = NULL;
}
void	free_token_list(t_token **list)
{
	t_token	*curr;
	t_token	*next;

	if (!list || !*list)
		return ;
	curr = *list;
	while (curr)
	{
		next = curr->next;
		if (curr->value)
			free(curr->value);
		free(curr);
		curr = next;
	}
	*list = NULL;
}
void	free_env_list(t_env **list)
{
	t_env	*curr;
	t_env	*next;

	if (!list || !*list)
		return ;
	curr = *list;
	while (curr)
	{
		next = curr->next;
		if (curr->key)
			free(curr->key);
		if (curr->value)
			free(curr->value);
		free(curr);
		curr = next;
	}
	*list = NULL;
}
