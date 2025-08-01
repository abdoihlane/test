/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/08/01 14:35:28 by salah            ###   ########.fr       */
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
            setup_redirections(clist, shell, clist);
            if (is_builtin(clist))
                exit(execute_builtin(clist, shell));
            cmd_path = find_path(clist->array[0], envp);
            if (cmd_path == (char *)-1)
            {
                ft_putstr_fd("bash: " ,2);
                printf("%s: Permission denied\n", clist->array[0]);
                exit(126);
            }
            if (!cmd_path)
            {
                ft_putstr_fd("bash: " ,2);
                printf("%s: command not found \n", clist->array[0]);
                exit(127);
            }
            filtered_args = filter_empty_args(clist);
            execve(cmd_path, filtered_args, envp);
            printf("here \n");
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
    WAITPID(pids, i, shell);
    ft_free_2d_array(envp);
}

void WAITPID(pid_t *pids, int i, t_shell *shell)
{
    int j = 0;
    int status;
    int exit_status = 0;

    while (j < i)
    {
        waitpid(pids[j], &status, 0);
        if (WIFEXITED(status))
            exit_status = WEXITSTATUS(status);
        j++;
    }

    // Update shell exit status
    shell->last_exit_status = exit_status;
}
