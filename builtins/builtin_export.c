/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:02 by salhali           #+#    #+#             */
/*   Updated: 2025/08/14 01:04:17 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *find_env_variable(t_shell *shell, const char *key)
{
	t_env *node = shell->envv;
	while (node)
	{
		if (ft_strcmp(node->key, (char *)key) == 0)
			return node;
		node = node->next;
	}
	return NULL;
}

int update_export_variable(t_shell *shell, const char *key, const char *value)
{
	t_env *node = find_env_variable(shell, key);
	if (node)
	{
		free(node->value);
		node->value = strdup(value);
		return 1;
	}
	return 0;
}

int create_export_variable(t_shell *shell, const char *key, const char *value)
{
	t_env *new = ft_malloc(sizeof(t_env));
	if (!new)
		return -1;
	new->key = strdup(key);
	new->value = value ? strdup(value) : NULL;
	new->next = shell->envv;
	shell->envv = new;
	return 0;
}

int handle_export_with_value(t_shell *shell, char *arg)
{
	char *equal = ft_strchr(arg, '=');
	int result = 0;
	*equal = '\0';
	char *key = arg;
	char *value = equal + 1;
	if (!is_valid_var(key))
	{
		printf("bash: export: `%s=%s': not a valid identifier\n", key, value);
		*equal = '=';
		return 1;
	}
	if (!update_export_variable(shell, key, value))
	{
		if (create_export_variable(shell, key, value) == -1)
			result = -1;
	}
	*equal = '=';
	return result;
}

int handle_export_without_value(t_shell *shell, const char *arg)
{
	if (!is_valid_var(arg))
	{
		printf("bash: export: `%s': not a valid identifier\n", arg);
		return 1;
	}
	if (!find_env_variable(shell, arg))
	{
		if (create_export_variable(shell, arg, "") == -1)
			return -1;
	}
	return 0;
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*value;
	int		exit_status;
	t_env	*tmp;
	int		result;

	i = 1;
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
	while (cmd->array[i])
	{
		value = ft_strchr(cmd->array[i], '=');
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
				return (-1); // ft_malloc failed
			else if (result == 1)
				exit_status = 1;
			i++;
		}
		return (exit_status);
	}
}
