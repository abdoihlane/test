/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:27:09 by salhali           #+#    #+#             */
/*   Updated: 2025/08/14 17:27:26 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_args(int argc, char **envp)
{
	if (argc != 1)
		return (1);
	if (!envp)
		return (1);
	return (0);
}

int	init_shell(t_shell *shell, char **envp)
{
	shell->envv = convert_envp_to_envlist(envp);
	if (!shell->envv)
		return (1);
	shell->last_exit_status = 0;
	return (0);
}

void	process_input(char *input, t_wlist **wlist, t_cmd **clist, t_shell *shell)
{
	call_all(input, wlist, clist, shell);
	execute(*clist, *wlist, shell);
	add_history(input);
}

void	cleanup_iteration(t_wlist **wlist, t_cmd **clist, char *input)
{
	free_wlist(wlist);
	free_clist(clist);
	free(input);
	*wlist = NULL;
	*clist = NULL;
}

void	shell_loop(t_shell *shell)
{
	t_cmd	*clist;
	t_wlist	*wlist;
	char	*input;

	clist = NULL;
	wlist = NULL;
	while (1)
	{
		signe();
		input = readline("➜  minishell : ");
		if (!input)
			break ;
		process_input(input, &wlist, &clist, shell);
		cleanup_iteration(&wlist, &clist, input);
	}
}

void	cleanup_shell(t_shell *shell)
{
	free_env_list(&shell->envv);
	ft_free_all();
}
