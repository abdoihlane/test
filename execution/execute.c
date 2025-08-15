/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:51:07 by salhali           #+#    #+#             */
/*   Updated: 2025/08/15 13:52:52 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_child_input_output(int in_fd, t_cmd *clist, int *pipe_fd)
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

void	handle_builtin_or_external(t_cmd *clist, t_shell *shell, char **envp)
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

void	handle_child_process(t_cmd *clist, t_shell *shell, int in_fd,
		int *pipe_fd)
{
	char	**envp;

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
		ft_putstr_fd("bash: command not found \n ", 2);
		ft_free_2d_gc_array(envp);
		exit(127);
	}
	filtered_args = filter_empty_args(clist);
	execve(cmd_path, filtered_args, envp);
	ft_free_2d_gc_array(envp);
	exit(127);
}
