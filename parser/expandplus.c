/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandplus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:26:52 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/13 09:59:03 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_dollar(t_pars *pars)
{
	pars->numdollar = 0;
	pars->i = 0;
	while (pars->content[pars->i])
	{
		if (pars->content[pars->i] == '$')
			pars->numdollar++;
		pars->i++;
	}
	pars->i = 0;
}

char	*find_last_valid_dollar(char *str)
{
	char	*current;
	char	*last_valid;

	current = str;
	last_valid = NULL;
	while (*current)
	{
		if (*current == '$' && *(current + 1))
		{
			if (*(current + 1) == '?' || ft_isalpha(*(current + 1)) || *(current
					+ 1) == '_')
				last_valid = current;
		}
		current++;
	}
	return (last_valid);
}

char	*find_first_valid_dollar(char *str)
{
	char	*current;

	current = str;
	while (*current)
	{
		if (*current == '$' && *(current + 1))
		{
			if (*(current + 1) == '?' || ft_isalpha(*(current + 1)) || *(current
					+ 1) == '_')
				return (current);
		}
		current++;
	}
	return (NULL);
}

char	*get_env_value_ll(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	get_varname_length(char *start)
{
	int	len;

	len = 0;
	while (start[len] && (ft_isalnum(start[len]) || start[len] == '_'))
		len++;
	return (len);
}
