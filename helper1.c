/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:20:16 by salhali           #+#    #+#             */
/*   Updated: 2025/08/13 23:18:42 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


int count_env_variables(t_shell *shell)
{
	t_env *tmp = shell->envv;
	int count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return count;
}

char *build_env_string(const char *key, const char *value)
{
	size_t len = ft_strlen(key) + (value ? ft_strlen(value) : 0) + 2;
	char *env_str = (char *)ft_malloc(len);
	if (!env_str)
		return NULL;
	strcpy(env_str, key);
	strcat(env_str, "=");
	if (value)
		strcat(env_str, value);
	return env_str;
}

char **generate_envp_from_envlist(t_shell *shell)
{
	int count = count_env_variables(shell);
	char **envp = (char **)ft_malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return NULL;
	t_env *tmp = shell->envv;
	int i = 0;
	while (tmp)
	{
		envp[i] = build_env_string(tmp->key, tmp->value);
		if (!envp[i])
			return NULL;
		tmp = tmp->next;
		i++;
	}
	envp[count] = NULL;
	return envp;
}

char	*ft_strjoin_triple(char *a, char *b, char *c)
{
	char *tmp = ft_strjoin(a, b);
	char *res = ft_strjoin(tmp, c);
	ft_free_single(tmp);
	return (res);
}
