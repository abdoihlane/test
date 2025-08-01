/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:46:56 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/01 17:32:08 by salhali          ###   ########.fr       */
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

void	free_clist(t_cmd **list)
{
	t_cmd	*curr;
	t_cmd	*next;
	t_pars	*pars_to_free = NULL;
	int		i;

	if (!list || !*list)
		return ;
	curr = *list;
	
	// Save pars pointer from first node to free it once
	if (curr && curr->pars)
		pars_to_free = curr->pars;
	
	while (curr)
	{
		next = curr->next;
		
		// Free the array of strings
		if (curr->array)
		{
			i = 0;
			while (curr->array[i])
			{
				free(curr->array[i]);
				i++;
			}
			free(curr->array);
		}
		
		// Free the cmd string
		if (curr->cmd)
			free(curr->cmd);
			
		// Free the redirection list
		if (curr->file)
			free_red_list(&curr->file);
		
		free(curr);
		curr = next;
	}
	
	// Free pars once at the end
	if (pars_to_free)
		free_plist(&pars_to_free);
	
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
