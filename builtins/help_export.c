/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:34:59 by salhali           #+#    #+#             */
/*   Updated: 2025/08/15 16:15:02 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_export_with_value(t_shell *shell, char *arg)
{
	char	*equal;
	int		result;
	char	*key;
	char	*value;

	equal = ft_strchr(arg, '=');
	result = 0;
	*equal = '\0';
	key = arg;
	value = equal + 1;
	if (!is_valid_var(key))
	{
		printf("bash: export: `%s=%s': not a valid identifier\n", key, value);
		*equal = '=';
		return (1);
	}
	if (!update_export_variable(shell, key, value))
	{
		if (create_export_variable(shell, key, value) == -1)
			result = -1;
	}
	*equal = '=';
	return (result);
}

int	handle_export_without_value(t_shell *shell, const char *arg)
{
	if (!is_valid_var(arg))
	{
		printf("bash: export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	if (!find_env_variable(shell, arg))
	{
		if (create_export_variable(shell, arg, "") == -1)
			return (-1);
	}
	return (0);
}

int	fun_condition(t_cmd *cmd, t_shell *shell, char *value, int i)
{
	int	result;
	int	exit_status;

	result = 0;
	exit_status = 0;
	if (value != NULL)
	{
		result = handle_export_with_value(shell, cmd->array[i]);
		if (result == -1)
			return (-1);
		else if (result == 1)
			exit_status = 1;
	}
	else
	{
		result = handle_export_without_value(shell, cmd->array[i]);
		if (result == -1)
			return (-1);
		else if (result == 1)
			exit_status = 1;
	}
	return (exit_status);
}

t_env	*find_env_variable(t_shell *shell, const char *key)
{
	t_env	*node;

	node = shell->envv;
	while (node)
	{
		if (ft_strcmp(node->key, (char *)key) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

int	create_export_variable(t_shell *shell, const char *key, const char *value)
{
	t_env	*new;

	new = allocate_env_node();
	if (!new)
		return (-1);
	if (set_env_key(new, key) == -1)
	{
		free_env_node(new);
		return (-1);
	}
	if (set_env_value(new, value) == -1)
	{
		free_env_node(new);
		return (-1);
	}
	add_env_to_shell(shell, new);
	return (0);
}
