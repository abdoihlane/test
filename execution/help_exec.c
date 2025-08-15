/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:51:23 by salhali           #+#    #+#             */
/*   Updated: 2025/08/15 17:51:39 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_parent_process(int *in_fd, int *pipe_fd, t_cmd *clist)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (clist->next)
	{
		close(pipe_fd[1]);
		*in_fd = pipe_fd[0];
	}
}

void	setup_pipeline(t_cmd *clist, int *pipe_fd)
{
	if (clist->next)
		pipe(pipe_fd);
}

void	execute_cmds(t_cmd *clist, t_shell *shell)
{
	int		in_fd;
	int		pipe_fd[2];
	pid_t	pids[100];
	int		i;
	char	**envp;

	in_fd = 0;
	i = 0;
	envp = generate_envp_from_envlist(shell);
	while (clist)
	{
		setup_pipeline(clist, pipe_fd);
		pids[i] = fork();
		if (pids[i] == 0)
			handle_child_process(clist, shell, in_fd, pipe_fd);
		handle_parent_process(&in_fd, pipe_fd, clist);
		clist = clist->next;
		i++;
	}
	ft_waitpid(pids, i, shell);
	ft_free_2d_gc_array(envp);
}

void	ft_waitpid(pid_t *pids, int i, t_shell *shell)
{
	int	j;
	int	status;
	int	exit_status;

	j = 0;
	exit_status = 0;
	while (j < i)
	{
		waitpid(pids[j], &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		j++;
	}
	shell->last_exit_status = exit_status;
}
