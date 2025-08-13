/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:59:41 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/13 10:34:06 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_array(int max_tokens, t_pars *pars)
{
	int	i;

	i = -1;
	while (i < max_tokens && pars->content1[++i])
		ft_free_single(pars->content1[i]);
	ft_free_single(pars->content1);
	pars->content1 = NULL;
}

int	check3(char *sa)
{
	int	i;

	i = 0;
	while (sa[i])
	{
		if (sa[i] != '$')
			return (1);
		i++;
	}
	return (0);
}

char	*call_expand(t_pars *pars, t_shell *shell, char *part)
{
	char	*expanded;

	while (ft_strchr(part, '$'))
	{
		expanded = expand_variables(part, shell);
		if (ft_strcmp(part, expanded) == 0)
		{
			ft_free_single(expanded);
			break ;
		}
		pars->expand_flag = 1;
		ft_free_single(part);
		part = expanded;
	}
	return (part);
}

void	fill_array_plus(t_pars *pars)
{
	if (pars->content[pars->i] == pars->content[pars->i + 1]
		&& (pars->content[pars->i] == '<' || pars->content[pars->i] == '>'))
	{
		pars->content1[pars->k++] = ft_substr(pars->content, pars->i, 2);
		if (pars->content[pars->i] == '<')
			pars->herdoc_flag = 1;
		pars->i += 2;
	}
	else
	{
		pars->content1[pars->k++] = ft_substr(pars->content, pars->i, 1);
		pars->i++;
	}
}
