/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:35:35 by salhali           #+#    #+#             */
/*   Updated: 2025/07/26 17:59:57 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// int	handle_builtin_parent(t_cmd *clist, t_shell *shell, int in_fd)
// {
// 	if (is_builtin(clist) && !clist->next && in_fd == 0)
// 	{
// 		setup_redirections(clist);
// 		shell->last_exit_status = execute_builtin(clist, shell);
// 		return (1);
// 	}
// 	return (0);
// }

// void	wait_for_children(pid_t *pids, int count)
// {
// 	int	j;

// 	j = 0;
// 	while (j < count)
// 	{
// 		waitpid(pids[j], NULL, 0);
// 		j++;
// 	}
// }

// void	handle_parent_process(int *in_fd, int *pipe_fd, int has_next)
// {
// 	if (*in_fd != 0)
// 		close(*in_fd);
// 	if (has_next)
// 	{
// 		close(pipe_fd[1]);
// 		*in_fd = pipe_fd[0];
// 	}
// }

// void	process_single_command(t_cmd **clist, t_shell *shell, char **envp,
// 			int *in_fd, int *pipe_fd, pid_t *pids, int *i)
// {
// 	if (handle_builtin_parent(*clist, shell, *in_fd))
// 	{
// 		*clist = (*clist)->next;
// 		return ;
// 	}
// 	if ((*clist)->next)
// 		pipe(pipe_fd);
// 	pids[*i] = fork();
// 	if (pids[*i] == 0)
// 	{
// 		setup_child_pipes(*in_fd, pipe_fd, (*clist)->next != NULL);
// 		execute_child_process(*clist, shell, envp);
// 	}
// 	handle_parent_process(in_fd, pipe_fd, (*clist)->next != NULL);
// 	*clist = (*clist)->next;
// 	(*i)++;
// }

// void	execute_command_loop(t_cmd *clist, t_shell *shell, char **envp)
// {
// 	int		in_fd;
// 	int		pipe_fd[2];
// 	pid_t	pids[100];
// 	int		i;

// 	in_fd = 0;
// 	i = 0;
// 	while (clist)
// 		process_single_command(&clist, shell, envp, &in_fd, pipe_fd, pids, &i);
// 	wait_for_children(pids, i);
// }
