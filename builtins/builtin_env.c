/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:18:24 by salhali           #+#    #+#             */
/*   Updated: 2025/07/29 16:52:08 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_env(t_cmd *cmd, t_shell *shell)
{
    t_env *tmp = shell->envv;

    if(cmd->array[1] && cmd->array[1][0] != '\0' && cmd->qflag == 1)
    {
        ft_putstr_fd("env: ", 2);
        ft_putstr_fd("too many arguments\n", 2);
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
