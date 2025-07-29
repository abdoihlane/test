/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:20:16 by salhali           #+#    #+#             */
/*   Updated: 2025/07/29 17:26:16 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void update_env_variable(t_shell *shell, const char *name, const char *value)
{
	t_env *tmp = shell->envv;

	while (tmp)
	{
		if (ft_strcmp(tmp->key, (char *)name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return;
		}
		tmp = tmp->next;
	}

	// variable not found → add it
	t_env *new = malloc(sizeof(t_env));
	if (!new)
		return;
	new->key = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = shell->envv;
	shell->envv = new;
}

void delete_env_variable(t_shell *shell, const char *name)
{
	t_env *curr = shell->envv;
	t_env *prev = NULL;

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
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

char **generate_envp_from_envlist(t_shell *shell)
{
	int count = 0;
	t_env *tmp = shell->envv;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	char **envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return NULL;

	tmp = shell->envv;
	int	i = 0;
	while (tmp)
	{
		envp[i] = ft_strjoin_triple(tmp->key, "=", tmp->value);
		tmp = tmp->next;
		i++;
	}
	envp[count] = NULL;
	return envp;
}

char *ft_strjoin_triple(char *a, char *b, char *c)
{
	char *tmp = ft_strjoin(a, b);
	char *res = ft_strjoin(tmp, c);
	free(tmp);
	return res;
}
