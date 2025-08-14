/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_source.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 23:55:00 by salah             #+#    #+#             */
/*   Updated: 2025/08/14 20:47:15 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_source(t_cmd *cmd)
{
	if (!cmd->array[1])
	{
		ft_putstr_fd(".: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		return (2);
	}
	ft_putstr_fd(".: ", 2);
	ft_putstr_fd(cmd->array[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}
