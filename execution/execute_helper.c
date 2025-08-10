/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:34:57 by salhali           #+#    #+#             */
/*   Updated: 2025/08/10 04:43:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// int	count_non_empty_args(t_cmd *cmd)
// {
// 	int	count;
// 	int	i;

// 	count = 0;
// 	i = 0;
// 	while (cmd->array[i])
// 	{
// 		if (ft_strlen(cmd->array[i]) > 0)
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }
// void	copy_non_empty_args(t_cmd *cmd, char **filtered)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (cmd->array[i])
// 	{
// 		if (ft_strlen(cmd->array[i]) > 0)
// 		{
// 			filtered[j] = cmd->array[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	filtered[j] = NULL;
// }
// char	**filter_empty_args(t_cmd *cmd)
// {
// 	char	**filtered;
// 	int		count;

// 	if (cmd->qflag == 0 || cmd->array == NULL)
// 		return (cmd->array);
// 	count = count_non_empty_args(cmd);
// 	filtered = ft_malloc(sizeof(char *) * (count + 1));
// 	if (!filtered)
// 		return (cmd->array);
// 	copy_non_empty_args(cmd, filtered);
// 	return (filtered);
// }

// void	setup_child_pipes(int in_fd, int *pipe_fd, int has_next)
// {
// 	if (in_fd != 0)
// 	{
// 		dup2(in_fd, STDIN_FILENO);
// 		close(in_fd);
// 	}
// 	if (has_next)
// 	{
// 		close(pipe_fd[0]);
// 		dup2(pipe_fd[1], STDOUT_FILENO);
// 		close(pipe_fd[1]);
// 	}
// }
// void	execute_child_process(t_cmd *clist, t_shell *shell, char **envp)
// {
// 	char	*cmd_path;
// 	char	**filtered_args;

// 	setup_redirections(clist);
// 	if (is_builtin(clist))
// 		exit(execute_builtin(clist, shell));
// 	cmd_path = find_path(clist->array[0], envp);
// 	if (!cmd_path)
// 	{
// 		printf("Command not found: %s\n", clist->array[0]);
// 		exit(127);
// 	}
// 	filtered_args = filter_empty_args(clist);
// 	execve(cmd_path, filtered_args, envp);
// 	exit(127);
// }
