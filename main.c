/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/07/30 20:43:57 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_dollars(char *sa)
{
	int dollar =0;
	int i =0;
	while(sa[i])
	{
		if(sa[i] == '$')
			dollar++;
		i++;
	}
	return dollar;
}

void	call_all(char *input, t_wlist **wlist, t_cmd **clist,t_shell *shell)
{
	t_pars	*pars = NULL;
	t_token	*token;

	if (hardcodechecks(input) == 0)
	{
		printf("syntax error\n");
		return ;
	}
	pars = init_pars(input);
	fill_the_array(pars,shell);
	commandornot(pars, wlist);
	token = typesee(wlist);
	splitit(token, clist);
	t_cmd *tmp = *clist;
	while (tmp)
	{
		tmp->pars = pars;
		tmp = tmp->next;
	}
	print_cmd_list(*clist);
}
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_cmd	*clist = NULL;
	t_wlist	*wlist = NULL;
	char	*input;
	t_pars	*pars = NULL;  // Declare pars here so we can free it later

	(void)argc;
	(void)argv;
	shell.envv = convert_envp_to_envlist(envp);
	shell.last_exit_status = 0;

	while (1)
	{
		signe();
		input = readline("\001\033[38;2;255;105;180m\002➜  minishell \001\033[0m\002");
		if (!input)
			break;
		call_all(input, &wlist, &clist, &shell);
		execute(clist, wlist, &shell);
		add_history(input);
		free_wlist(&wlist);
		free_clist(&clist);
		free(input);
	}
	return (0);
}
