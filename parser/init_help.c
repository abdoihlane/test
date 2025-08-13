/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:25:07 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/13 10:42:33 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_pipes(t_pars *pars)
{
	int	i;

	i = 0;
	pars->nbofpipes = 0;
	while (pars->content[i])
	{
		if (pars->content[i] == '<' || pars->content[i] == '>'
			|| pars->content[i] == '|')
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

void	calculate_len(t_pars *pars)
{
	while (pars->content[pars->i])
	{
		skipwhitespaces(pars);
		if (pars->content[pars->i] == '\0')
			break ;
		while (!is_whitespace(pars->content[pars->i]) && pars->content[pars->i])
			pars->i++;
		pars->lenofarray++;
	}
	pars->i = 0;
}

void	init_wlist(t_wlist *w)
{
	if (!w)
		return ;
	w->content = NULL;
	w->next = NULL;
	w->index = 0;
}

void	init_parsa(t_pars *p)
{
	if (!p)
		return ;
	ft_memset(p, 0, sizeof(t_pars));
	p->c = '\0';
	p->content1 = NULL;
	p->content = NULL;
}
