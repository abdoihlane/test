/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/08/14 14:58:39 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void setup_child_input_output(int in_fd, t_cmd *clist, int *pipe_fd)
{
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (clist->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void handle_builtin_or_external(t_cmd *clist, t_shell *shell, char **envp)
{
	if (is_builtin(clist))
	{
		ft_free_2d_gc_array(envp);
		exit(execute_builtin(clist, shell));
	}
	if (!clist->array || !clist->array[0])
	{
		ft_free_2d_gc_array(envp);
		exit(0);
	}
	execute_external_command(clist, envp);
}

void handle_child_process(t_cmd *clist, t_shell *shell, int in_fd, int *pipe_fd)
{
	char **envp;
	
	envp = generate_envp_from_envlist(shell);
	setup_child_input_output(in_fd, clist, pipe_fd);
	setup_redirections(clist, shell, clist);
	handle_builtin_or_external(clist, shell, envp);
}

void	execute_external_command(t_cmd *clist, char **envp)
{
	char	*cmd_path;
	char	**filtered_args;

	cmd_path = find_path(clist->array[0], envp);
	if (cmd_path == (char *)-1)
	{
		ft_putstr_fd("bash: ", 2);
		printf("%s: Permission denied\n", clist->array[0]);
		ft_free_2d_gc_array(envp);
		exit(126);
	}
	if (!cmd_path)
	{
		ft_putstr_fd("bash: ", 2);
		printf("%s: command not found \n", clist->array[0]);
		ft_free_2d_gc_array(envp);
		exit(127);
	}
	filtered_args = filter_empty_args(clist);
	execve(cmd_path, filtered_args, envp);
	ft_free_2d_gc_array(envp);
	exit(127);
}

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
	WAITPID(pids, i, shell);
	ft_free_2d_gc_array(envp);
}

void	WAITPID(pid_t *pids, int i, t_shell *shell)
{
	int j;
	int status;
	int exit_status;

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
