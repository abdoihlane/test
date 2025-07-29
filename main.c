/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/07/29 14:59:30 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_input(char *delimiter, t_red_list *head)
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
		expanded = expand_variables(line);
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

// minishell/
// ├── main.c               (your current main)
// ├── minishell.h         (your current header)
// ├── execution/
// │   ├── execute.c       (execute_cmds function)
// │   ├── redirections.c  (setup_redirections)
// │   └── path.c          (find_path)
// ├── builtins/
// │   ├── builtin_echo.c
// │   ├── builtin_cd.c
// │   ├── builtin_pwd.c
// │   ├── builtin_export.c
// │   ├── builtin_unset.c
// │   ├── builtin_env.c
// │   └── builtin_exit.c
// ├── parsing/
// │   ├── parser.c        (call_all, typesee, splitit)
// │   ├── tokenizer.c
// │   └── syntax.c        (HardcodeChecks)
// ├── utils/
// │   ├── env_utils.c     (environment functions)
// │   ├── memory.c        (free functions)
// │   └── signals.c       (signal handling)
// └── libft/              (your existing libft)
