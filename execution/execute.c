/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/07/28 01:53:03 by salah            ###   ########.fr       */
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
        printf("=== DEBUG: Before fork ===\n");
        printf("Command: '%s'\n", clist->cmd ? clist->cmd : "NULL");
        int debug_i = 0;
        while (clist->array && clist->array[debug_i])
        {
            printf("array[%d] = '%s' (len: %zu)\n", debug_i, clist->array[debug_i], strlen(clist->array[debug_i]));
            debug_i++;
        }
        printf("========================\n");
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
            int k = 0;
            int b = 0;
            while(clist->array[k])
            {

                printf("clist->array[%d] = %s\n",b ,  clist->array[k]);
                b++;
                k++;
            }
            cmd_path = find_path(clist->array[0], envp);
            if (!cmd_path)
            {
                printf("fild_path is faled\n");
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
