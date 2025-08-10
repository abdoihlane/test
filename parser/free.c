/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:46:56 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/06 18:02:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_wlist(t_wlist **list)
{
    t_wlist *curr;
    t_wlist *next;

    if (!list || !*list)
        return;
    
    curr = *list;
    while (curr)
    {
        next = curr->next;
        ft_free_single(curr);
        curr = next;
    }
    *list = NULL;
}

void free_red_list(t_red_list **list)
{
    t_red_list *curr;
    t_red_list *next;

    if (!list || !*list)
        return;
    
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

void free_clist(t_cmd **list)
{
    t_cmd *curr;
    t_cmd *next;
    t_pars *pars_to_free = NULL;
    int i;

    if (!list || !*list)
        return;
    
    curr = *list;
    
    if (curr && curr->pars)
        pars_to_free = curr->pars;
    
    while (curr)
    {
        next = curr->next;
        
        if (curr->array)
        {
            i = 0;
            while (curr->array[i])
            {
                ft_free_single(curr->array[i]);
                i++;
            }
            ft_free_single(curr->array);
        }
        
        if (curr->cmd)
            ft_free_single(curr->cmd);
            
        if (curr->file)
            free_red_list(&curr->file);
        
        ft_free_single(curr);
        curr = next;
    }
    
    if (pars_to_free)
        free_plist(&pars_to_free);
    
    *list = NULL;
}

void free_plist(t_pars **par)
{
    t_pars *p;
    int i;

    if (!par || !*par)
        return;
    
    p = *par;
    
    if (p->content)
        ft_free_single(p->content);
    
    if (p->content1)
    {
        i = 0;
        while (p->content1[i])
        {
            ft_free_single(p->content1[i]);
            i++;
        }
        ft_free_single(p->content1);
    }
    
    ft_free_single(p);
    *par = NULL;
}

void free_token_list(t_token **list)
{
    t_token *curr;
    t_token *next;

    if (!list || !*list)
        return;
    
    curr = *list;
    while (curr)
    {
        next = curr->next;
        if (curr->value)
            ft_free_single(curr->value);
        ft_free_single(curr);
        curr = next;
    }
    *list = NULL;
}

void free_env_list(t_env **list)
{
    t_env *curr;
    t_env *next;

    if (!list || !*list)
        return;
    
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