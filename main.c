/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/08/14 14:56:47 by salhali          ###   ########.fr       */
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
	if (hardcodechecks(input) == 0)
	{
		printf("syntax error\n");
		return;
	}
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
	t_cmd	*clist;
	t_wlist	*wlist;
	char	*input;

	clist = NULL;
	wlist = NULL;
	if (argc != 1)
		return (1);
	(void)argv;
	if (!envp)
		return (1);
	shell.envv = convert_envp_to_envlist(envp);
	if (!shell.envv)
		return (1);
	shell.last_exit_status = 0;
	while (1)
	{
		signe();
		input = readline("➜  minishell : ");
		if (!input)
			break ;
		call_all(input, &wlist, &clist, &shell);
		execute(clist, wlist, &shell);
		add_history(input);
		free_wlist(&wlist);
		free_clist(&clist);
		free(input);
		wlist = NULL;
		clist = NULL;
	}
	free_env_list(&shell.envv);
	ft_free_all();
	return (0);
}
