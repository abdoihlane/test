/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:02 by salhali           #+#    #+#             */
/*   Updated: 2025/08/14 23:08:06 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	update_export_variable(t_shell *shell, const char *key, const char *value)
{
	t_env	*node;

	node = find_env_variable(shell, key);
	if (node)
	{
		free(node->value);
		node->value = strdup(value);
		return (1);
	}
	return (0);
}

int	create_export_variable(t_shell *shell, const char *key, const char *value)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->key = strdup(key);
	new->value = value ? strdup(value) : NULL;
	new->next = shell->envv;
	shell->envv = new;
	return (0);
}

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
int fun_condition(t_cmd *cmd,t_shell *shell,char *value,int i)
{
	int result;
	int exit_status;

	result =0;
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
	return exit_status;
}
int	loops_s(t_cmd *cmd, t_shell *shell)
{
	char *value;
	int i;
	int		exit_status;

	i =1;
	exit_status = 0;
	while (cmd->array[i])
	{
		value = ft_strchr(cmd->array[i], '=');
		exit_status = fun_condition(cmd,shell,value,i);
		if(exit_status == -1)
			return -1;
		i++;
	}
	return exit_status;
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
	exit_status = loops_s(cmd,shell);
	if(exit_status == -1)
		return -1;
	return (exit_status);
}
