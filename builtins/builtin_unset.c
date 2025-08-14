/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:51 by salhali           #+#    #+#             */
/*   Updated: 2025/08/14 09:12:50 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

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
void	delete_env_variable(t_shell *shell, const char *name)
{
	t_env	*curr;
	t_env	*prev;

	curr = shell->envv;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, (char *)name) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->envv = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
