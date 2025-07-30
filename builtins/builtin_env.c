/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:18:24 by salhali           #+#    #+#             */
/*   Updated: 2025/07/30 18:16:38 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_env(t_cmd *cmd, t_shell *shell)
{
    t_env *tmp = shell->envv;

    printf("cmd->pars->qflag: %d\n", cmd->pars->qflag);
    printf("cmd->array[1]: %s\n", cmd->array[1]);
    if(cmd->pars->qflag == 1)
    {
        ft_putstr_fd("env: ‘’: ", 2);

        // perror("No such file or directory\n");
        ft_putstr_fd("No such file or directory\n", 2);
        return(1);
    }
    while (tmp)
    {
        if (tmp->value)
        {
            printf("%s=%s\n", tmp->key, tmp->value);
        }
        tmp = tmp->next;
    }
    return 0;
}
