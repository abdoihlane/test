/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:02 by salhali           #+#    #+#             */
/*   Updated: 2025/08/15 16:12:07 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_env_value(t_env *env, const char *value)
{
	if (value)
	{
		env->value = strdup(value);
		if (!env->value)
			return (-1);
	}
	else
		env->value = NULL;
	return (0);
}

void	free_env_node(t_env *env)
{
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

void	add_env_to_shell(t_shell *shell, t_env *env)
{
	env->next = shell->envv;
	shell->envv = env;
}

int	loops_s(t_cmd *cmd, t_shell *shell)
{
	char	*value;
	int		i;
	int		exit_status;

	i = 1;
	exit_status = 0;
	while (cmd->array[i])
	{
		value = ft_strchr(cmd->array[i], '=');
		exit_status = fun_condition(cmd, shell, value, i);
		if (exit_status == -1)
			return (-1);
		i++;
	}
	return (exit_status);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int		exit_status;
	t_env	*tmp;

	exit_status = 0;
	if (cmd->array[1] == NULL)
	{
		tmp = shell->envv;
		while (tmp)
		{
			printf("declare -x %s", tmp->key);
			if (tmp->value)
				printf("=\"%s\"", tmp->value);
			printf("\n");
			tmp = tmp->next;
		}
		return (0);
	}
	exit_status = loops_s(cmd, shell);
	if (exit_status == -1)
		return (-1);
	return (exit_status);
}
