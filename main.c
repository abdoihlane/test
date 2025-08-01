/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/07/31 16:46:52 by salah            ###   ########.fr       */
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
	
	// Free the token list as it's no longer needed
	free_token_list(&token);
	
	// Note: pars will be freed when the clist is freed since each cmd has a reference to it
	// print_cmd_list(*clist);
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
	printf("DEBUG: Starting minishell\n");
	fflush(stdout);
	
	if (!envp)
	{
		printf("ERROR: envp is NULL\n");
		return 1;
	}
	
	shell.envv = convert_envp_to_envlist(envp);
	if (!shell.envv)
	{
		printf("ERROR: Failed to convert environment\n");
		return 1;
	}
	shell.last_exit_status = 0;
	printf("DEBUG: Environment loaded\n");
	fflush(stdout);

	while (1)
	{
		printf("DEBUG: Setting up signals\n");
		fflush(stdout);
		signe();
		printf("DEBUG: Calling readline\n");
		fflush(stdout);
		input = readline("\001\033[38;2;255;105;180m\002➜  minishell \001\033[0m\002");
		printf("DEBUG: Got input: %s\n", input ? input : "(null)");
		fflush(stdout);
		if (!input)
			break;
		printf("DEBUG: Calling call_all\n");
		fflush(stdout);
		call_all(input, &wlist, &clist, &shell);
		printf("DEBUG: Calling execute\n");
		fflush(stdout);
		execute(clist, wlist, &shell);
		printf("DEBUG: Adding to history\n");
		fflush(stdout);
		add_history(input);
		printf("DEBUG: Freeing structures\n");
		fflush(stdout);
		free_wlist(&wlist);
		free_clist(&clist);
		free(input);
		printf("DEBUG: End of loop iteration\n");
		fflush(stdout);
	}
	
	printf("DEBUG: Cleaning up on exit\n");
	fflush(stdout);
	// Clean up on exit
	free_env_list(&shell.envv);
	return (0);
}
