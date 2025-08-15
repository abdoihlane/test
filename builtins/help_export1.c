/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_export1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:11:49 by salhali           #+#    #+#             */
/*   Updated: 2025/08/15 16:12:03 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_env	*allocate_env_node(void)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

int	set_env_key(t_env *env, const char *key)
{
	env->key = strdup(key);
	if (!env->key)
		return (-1);
	return (0);
}
