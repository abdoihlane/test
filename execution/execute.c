/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/07/28 02:27:08 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_cmds(t_cmd *clist, t_shell *shell)
{
    int in_fd = 0;
    int pipe_fd[2];
    pid_t pids[100];
    int i = 0;
    char *cmd_path;
    char **filtered_args;
    char **envp = generate_envp_from_envlist(shell);
    t_cmd *original_clist = clist;  // Save the original command list head

    while (clist)
    {
        if (clist->next)
            pipe(pipe_fd);

        pids[i] = fork();
        if (pids[i] == 0)
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
            setup_redirections(clist, shell, original_clist);
            if (is_builtin(clist))
            {
                printf("Executing builtin command from exetuce_cmds : %s\n", clist->cmd);
                exit(execute_builtin(clist, shell));
            }
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
        if (in_fd != 0)
            close(in_fd);
        if (clist->next)
        {
            close(pipe_fd[1]);
            in_fd = pipe_fd[0];
        }
        clist = clist->next;
        i++;
    }
    WAITPID(pids, i);
    ft_free_2d_array(envp);
}

void    WAITPID(pid_t *pids, int i)
{
    int j = 0;
    while (j < i)
    {
        waitpid(pids[j], NULL, 0);
        j++;
    }
}
