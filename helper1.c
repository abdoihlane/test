/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:20:16 by salhali           #+#    #+#             */
/*   Updated: 2025/08/14 14:57:18 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_env_variables(t_shell *shell)
{
	t_env *tmp;
	int count;

	count = 0;
	tmp = shell->envv;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return count;
}

char	*build_env_string(const char *key, const char *value)
{
	size_t	len;
	char	*env_str;

	len = ft_strlen(key);
	if (value)
		len += ft_strlen(value);
	len += 2;
	env_str = (char *)ft_malloc(len);
	if (!env_str)
		return (NULL);
	strcpy(env_str, key);
	strcat(env_str, "=");
	if (value)
		strcat(env_str, value);
	return (env_str);
}

char **generate_envp_from_envlist(t_shell *shell)
{
	int i;
	t_env *tmp;
	int count;
	char **envp;

	count = count_env_variables(shell);
	envp = (char **)ft_malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return NULL;
	tmp = shell->envv;
	i = 0;
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
