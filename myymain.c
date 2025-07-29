/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myymain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 04:46:55 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/29 16:14:49 by salhali          ###   ########.fr       */
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
void	heredoc_input(char *delimiter, t_red_list *head, t_shell *shell, t_cmd *clist)
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
		{
			printf("Error reading input\n");
			free(line);
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			printf("hereeee check line = %s\n", line);
			free(line);      //  free line
			line = NULL;     //  reset line bach ma n3awdch nfreeeha
			break;
		}
		if(clist->pars && clist->pars->dflag == 0)
		{
			int i = 0;
			int dollar = count_dollars(line);
			while(dollar > 0 && i < dollar)
			{
				line = expand_variables(line,shell);
				i++;	
			}
			expanded = ft_strdup(line);
		}
		else
			expanded = ft_strdup(line);

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
void	split_env(char *equal, t_env *node, char **envp, int i)
{
	// printf("is here !!\n");
	*equal = '\0'; // temporarily break key=value
	node->key = ft_strdup(envp[i]);
	node->value = ft_strdup(equal + 1);
	*equal = '=';  // restore original string
}
t_env *convert_envp_to_envlist(char **envp)
{
	t_env *head = NULL;
	t_env *last = NULL;
	char *equal;
	t_env *node;
    int i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal == NULL)
			continue;

		node = malloc(sizeof(t_env));
		if (node == NULL)
			return NULL;

		split_env(equal, node, envp, i);
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
	t_cmd *tmp = *clist;
	while (tmp)
	{
		tmp->pars = pars;
		tmp = tmp->next;
	}
}

void	execute(t_cmd *clist, t_wlist *wlist, t_shell shell)
{
	if (clist && is_builtin(clist) && clist->next == NULL && clist->file == NULL)
		execute_builtin(clist, &shell);
	else
		execute_cmds(clist, &shell);
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
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline("\001\033[38;2;255;105;180m\002➜  minishell \001\033[0m\002");
		if (!input)
			break;
		call_all(input, &wlist, &clist, &shell);
		execute(clist, wlist, shell);
		add_history(input);
		free_wlist(&wlist);
		free_clist(&clist);
		free(input);
	}
	return (0);
}
