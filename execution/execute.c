/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:16:53 by salhali           #+#    #+#             */
/*   Updated: 2025/07/25 21:46:47 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_non_empty_args(t_cmd *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd->array[i])
	{
		if (ft_strlen(cmd->array[i]) > 0)
			count++;
		i++;
	}
	return (count);
}

void	copy_non_empty_args(t_cmd *cmd, char **filtered)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->array[i])
	{
		if (ft_strlen(cmd->array[i]) > 0)
		{
			filtered[j] = cmd->array[i];
			j++;
		}
		i++;
	}
	filtered[j] = NULL;
}

char	**filter_empty_args(t_cmd *cmd)
{
	char	**filtered;
	int		count;

	if (cmd->qflag == 0 || cmd->array == NULL)
		return (cmd->array);
	count = count_non_empty_args(cmd);
	filtered = malloc(sizeof(char *) * (count + 1));
	if (!filtered)
		return (cmd->array);
	copy_non_empty_args(cmd, filtered);
	return (filtered);
}

void	setup_child_pipes(int in_fd, int *pipe_fd, int has_next)
{
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (has_next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void	execute_child_process(t_cmd *clist, t_shell *shell, char **envp)
{
	char	*cmd_path;
	char	**filtered_args;

	setup_redirections(clist);
	if (is_builtin(clist))
		exit(execute_builtin(clist, shell));
	cmd_path = find_path(clist->array[0], envp);
	if (!cmd_path)
	{
		printf("Command not found: %s\n", clist->array[0]);
		exit(127);
	}
	filtered_args = filter_empty_args(clist);
	execve(cmd_path, filtered_args, envp);
	exit(127);
}

int	handle_builtin_parent(t_cmd *clist, t_shell *shell, int in_fd)
{
	if (is_builtin(clist) && !clist->next && in_fd == 0)
	{
		setup_redirections(clist);
		shell->last_exit_status = execute_builtin(clist, shell);
		return (1);
	}
	return (0);
}

void	wait_for_children(pid_t *pids, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
}

void	handle_parent_process(int *in_fd, int *pipe_fd, int has_next)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (has_next)
	{
		close(pipe_fd[1]);
		*in_fd = pipe_fd[0];
	}
}

void	process_single_command(t_cmd **clist, t_shell *shell, char **envp,
			int *in_fd, int *pipe_fd, pid_t *pids, int *i)
{
	if (handle_builtin_parent(*clist, shell, *in_fd))
	{
		*clist = (*clist)->next;
		return;
	}
	if ((*clist)->next)
		pipe(pipe_fd);
	pids[*i] = fork();
	if (pids[*i] == 0)
	{
		setup_child_pipes(*in_fd, pipe_fd, (*clist)->next != NULL);
		execute_child_process(*clist, shell, envp);
	}
	handle_parent_process(in_fd, pipe_fd, (*clist)->next != NULL);
	*clist = (*clist)->next;
	(*i)++;
}

void	execute_command_loop(t_cmd *clist, t_shell *shell, char **envp)
{
	int		in_fd;
	int		pipe_fd[2];
	pid_t	pids[100];
	int		i;

	in_fd = 0;
	i = 0;
	while (clist)
		process_single_command(&clist, shell, envp, &in_fd, pipe_fd, pids, &i);
	wait_for_children(pids, i);
}

void	execute_cmds(t_cmd *clist, t_shell *shell)
{
	char	**envp;

	envp = generate_envp_from_envlist(shell);
	execute_command_loop(clist, shell, envp);
	ft_free_2d_array(envp);
}
