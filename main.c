/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/08/15 13:49:20 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_dollars(char *sa)
{
	int	dollar;
	int	i;

	dollar = 0;
	i = 0;
	while (sa[i])
	{
		if (sa[i] == '$')
			dollar++;
		i++;
	}
	return (dollar);
}

void	call_all(char *input, t_wlist **wlist, t_cmd **clist, t_shell *shell)
{
	t_pars	*pars;
	t_token	*token;
	t_cmd	*tmp;

	pars = NULL;
	token = NULL;
	init_all(pars, token, *clist, *wlist);
	pars = init_pars(input);
	if (!pars)
		return ;
	fill_the_array(pars, shell);
	commandornot(pars, wlist);
	token = typesee(wlist);
	splitit(token, clist);
	tmp = *clist;
	while (tmp)
	{
		tmp->pars = pars;
		tmp = tmp->next;
	}
	if (token)
		free_token_list(&token);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	if (validate_args(argc, envp))
		return (1);
	init_shell(&shell, envp);
	shell_loop(&shell);
	cleanup_shell(&shell);
	return (0);
}
