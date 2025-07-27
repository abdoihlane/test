/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myymain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 04:46:55 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/27 20:50:58 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_input(char *delimiter, t_red_list *head,t_shell *shell)
{
	char	*line = NULL;
    char    *expanded = NULL;
	size_t	len = 0;
    signal(SIGINT, sigint_heredoc);

	int		fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc open");
		return;
	}

	while (1)
	{
		write(1, "> ", 2);
		ssize_t nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);      //  free line
			line = NULL;     //  reset line bach ma n3awdch nfreeeha
			break;
		}
		expanded = expand_variables(line,shell);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	head->content = ft_strdup(".heredoc_tmp");
	head->inout = 0; //  set inout to 0 for file input redirection
	if (line)               //  free ghir ila mazal line ma tfreeatch
		free(line);
	close(fd);
}

t_env *convert_envp_to_envlist(char **envp)
{
	t_env *head = NULL;
	t_env *last = NULL;
    int i = 0;
	while (envp[i])
	{
		char *equal = ft_strchr(envp[i], '=');
		if (!equal)
			continue;

		t_env *node = malloc(sizeof(t_env));
		if (!node)
			return NULL;

		*equal = '\0'; // temporarily break key=value
		node->key = ft_strdup(envp[i]);
		node->value = ft_strdup(equal + 1);
		*equal = '=';  // restore original string

		node->next = NULL;
		if (!head)
			head = node;
		else
			last->next = node;
		last = node;
        i++;
	}
	return head;
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
	print_cmd_list(*clist);
	free_plist(&pars);
}

// void	call_all(char *in, t_wlist **wlist)
// {
// 	t_token	*token;
// 	t_pars	*pars;
// 	char	*history_in;
// 	t_cmd	*clist;
// 	t_pars	*pars;

// 	pars = NULL;
// 	if (hardcodechecks(in) == 0)
// 	{
// 		printf("syntax error\n");
// 		return ;
// 	}
// 	if (in)
// 	{
// 		history_in = ft_strdup(in);
// 		add_history(history_in);
// 	}
// 	clist = NULL;
// 	pars = init_pars(in);
// 	fill_the_array(pars);
// 	commandornot(pars, wlist);
// 	token = typesee(wlist);
// 	splitit(token, &clist);
// 	free_plist(&pars);
// }

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_cmd	*clist = NULL;
	t_wlist	*wlist = NULL;
	char	*input;

	(void)argc;
	(void)argv;
	shell.envv = convert_envp_to_envlist(envp);
	shell.last_exit_status = 0;

	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline("\001\033[38;2;255;105;180m\002➜  minishell \001\033[0m\002");
		if (!input)
			break;
		call_all(input, &wlist, &clist,&shell);  // call_all builds wlist and clist
		if (clist && is_builtin(clist) && clist->next == NULL && clist->file == NULL)
			execute_builtin(clist, &shell);
		else
			execute_cmds(clist, &shell);
		add_history(input);
		free_wlist(&wlist);
		// free_clist(&clist);
		free(input);
	}
	return (0);
}
