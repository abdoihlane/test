/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:18:47 by salhali           #+#    #+#             */
/*   Updated: 2025/07/30 18:07:43 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	long long	exit_value;

	exit_value = 0;
	ft_putendl_fd("exit", 2);
	if (!cmd->array[1])
	{
		free_env_list(&shell->envv);
		ft_free_all();
		exit(shell->last_exit_status);
	}
	if (!is_numeric(cmd->array[1]))
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(cmd->array[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		free_env_list(&shell->envv);
		ft_free_all();
		exit(255);
	}
	if (cmd->array[2] != NULL)
	{
		ft_putendl_fd("bash: exit: too many arguments", 2);
		shell->last_exit_status = 1;
		return ;
	}
	exit_value = ft_atoi(cmd->array[1]);
	free_env_list(&shell->envv);
	ft_free_all();
	exit(exit_value % 256);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0); // ay char ma numeric
		i++;
	}
	return (1);
}
