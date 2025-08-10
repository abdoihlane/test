/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:46:22 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/10 17:33:42 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void count_pipes(t_pars *pars); // <-- Add this prototype before using it

t_pars	*init_pars(char *in)
{
    t_pars	*pars;

    pars = ft_malloc(sizeof(t_pars));
    pars->i = 0;
    pars->k = 0;
    pars->lenofarray = 0;
    pars->nbofpipes = 0;
    pars->content = ft_strdup(in);
    pars->content1 = NULL; // Initialize to NULL for safety

    // Calculate lenofarray
    pars->i = 0;
    while (pars->content[pars->i])
    {
        skipwhitespaces(pars);
        if (pars->content[pars->i] == '\0')
            break ;
        while (!is_whitespace(pars->content[pars->i]) && pars->content[pars->i])
            pars->i++;
        pars->lenofarray++;
    }

    // Reset i for count_pipes
    pars->i = 0;
    count_pipes(pars);

    // Allocate content1 with correct size
    pars->content1 = ft_malloc(sizeof(char *) * (pars->lenofarray + pars->nbofpipes + 1));
    if (pars->content1)
        memset(pars->content1, 0, sizeof(char *) * (pars->lenofarray + pars->nbofpipes + 1));
    return (pars);
}

void	count_pipes(t_pars *pars)
{
    int i = 0;
    pars->nbofpipes = 0;
    while (pars->content[i])
    {
        if (pars->content[i] == '<' || pars->content[i] == '>' || pars->content[i] == '|')
        {
            if (i != 0 && !is_whitespace(pars->content[i - 1])
                && !is_whitespace(pars->content[i + 1]))
                pars->nbofpipes += 2;
            else
                pars->nbofpipes += 1;
        }
        i++;
    }
}

void init_red_list(t_red_list *r)
{
    if (!r)
        return;
    r->content = NULL;
    r->inout = 0;
    r->next = NULL;
}

void init_token(t_token *t)
{
    if (!t)
        return;
    t->type = TOKEN_WORD; // default, can change later
    t->next = NULL;
    t->index = 0;
    t->value = NULL;
}

void init_cmd(t_cmd *cmd)
{
    if (!cmd)
        return;
    cmd->index = 0;
    cmd->capacity = 0;
    cmd->array = NULL;
    cmd->cmd = NULL;
    cmd->qflag = 0;
    cmd->file = NULL;
    cmd->next = NULL;
    cmd->pars = NULL;
}

void init_wlist(t_wlist *w)
{
    if (!w)
        return;
    w->content = NULL;
    w->next = NULL;
    w->index = 0;
}

void init_parsa(t_pars *p)
{
    if (!p)
        return;
    memset(p, 0, sizeof(t_pars)); // Sets all integers to 0 and pointers to NULL
    p->c = '\0'; // Explicitly set char to null terminator
    p->content1 = NULL;
    p->content = NULL;
}


void init_all(t_pars *p, t_token *t, t_cmd *cmd, t_wlist *w)
{
    init_parsa(p);
    // init_red_list(r);
    init_token(t);
    init_cmd(cmd);
    init_wlist(w);
}