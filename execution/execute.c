/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:16:53 by salhali           #+#    #+#             */
/*   Updated: 2025/07/26 14:37:15 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_cmds(t_cmd *clist, t_shell *shell)
{
	char	**envp;

	envp = generate_envp_from_envlist(shell);
	execute_command_loop(clist, shell, envp);
	ft_free_2d_array(envp);
}
