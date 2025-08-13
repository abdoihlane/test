/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:46:22 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/13 10:36:24 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pars	*init_pars(char *in)
{
	t_pars	*pars;

	pars = ft_malloc(sizeof(t_pars));
	pars->i = 0;
	pars->k = 0;
	pars->lenofarray = 0;
	pars->nbofpipes = 0;
	pars->content = ft_strdup(in);
	pars->content1 = NULL;
	pars->i = 0;
	calculate_len(pars);
	count_pipes(pars);
	pars->content1 = ft_malloc(sizeof(char *) * (pars->lenofarray
				+ pars->nbofpipes + 1));
	if (pars->content1)
		ft_memset(pars->content1, 0, sizeof(char *) * (pars->lenofarray
				+ pars->nbofpipes + 1));
	return (pars);
}

void	init_red_list(t_red_list *r)
{
	if (!r)
		return ;
	r->content = NULL;
	r->inout = 0;
	r->next = NULL;
}

void	init_token(t_token *t)
{
	if (!t)
		return ;
	t->type = TOKEN_WORD;
	t->next = NULL;
	t->index = 0;
	t->value = NULL;
}

void	init_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd->index = 0;
	cmd->capacity = 0;
	cmd->array = NULL;
	cmd->cmd = NULL;
	cmd->qflag = 0;
	cmd->file = NULL;
	cmd->next = NULL;
	cmd->pars = NULL;
}

void	init_all(t_pars *p, t_token *t, t_cmd *cmd, t_wlist *w)
{
	init_parsa(p);
	init_token(t);
	init_cmd(cmd);
	init_wlist(w);
}
