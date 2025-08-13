/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:20:16 by salhali           #+#    #+#             */
/*   Updated: 2025/08/10 04:43:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_variable(t_shell *shell, const char *name, const char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = shell->envv;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, (char *)name) == 0)
		{
			free(tmp->value);
			tmp->value = strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = strdup(name);
	new->value = strdup(value);
	new->next = shell->envv;
	shell->envv = new;
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

char	**generate_envp_from_envlist(t_shell *shell)
{
	int		count;
	t_env	*tmp;
	int		i;
	char	**envp;
	size_t	len;

	count = 0;
	tmp = shell->envv;
	i = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = (char **)ft_malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = shell->envv;
	while (tmp)
	{
		len = ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2;
		envp[i] = (char *)ft_malloc(len);
		if (!envp[i])
		{
			return (NULL);
		}
		strcpy(envp[i], tmp->key);
		strcat(envp[i], "=");
		strcat(envp[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	envp[count] = NULL;
	return (envp);
}

char	*ft_strjoin_triple(char *a, char *b, char *c)
{
	char *tmp = ft_strjoin(a, b);
	char *res = ft_strjoin(tmp, c);
	ft_free_single(tmp);
	return (res);
}