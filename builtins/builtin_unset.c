/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:51 by salhali           #+#    #+#             */
/*   Updated: 2025/07/24 19:50:17 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_unset(t_cmd *cmd, t_shell *shell)
{
    int i;

    if (!cmd->array || !cmd->array[1])
        return (0);

    i = 1;
    while (cmd->array[i])
    {
        delete_env_variable(shell, cmd->array[i]);
        i++;
    }

    return (0);
}


