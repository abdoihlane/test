/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:26:52 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/05 17:58:15 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(char *str)
{
	size_t	len;
	char	*new;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"')
		|| (str[0] == '\'' && str[len - 1] == '\'')))
		new = ft_substr(str, 1, len - 2);
	else
		new = ft_strdup(str);
	return (new);
}

char	*build_result(char *input, char *varname, int var_len,t_shell *shell)
{
	char	*env;
	char	*prefix;
	char	*suffix;
	char	*tmp;
	char	*result;

	if(strcmp("?",varname) == 0)
	{
		env = ft_itoa(shell->last_exit_status);
		return env;
	}
	env = get_env_value_ll(shell->envv,varname);
	env = remove_quotes(env);
	prefix = ft_substr(input, 0, ft_strchr(input, '$') - input);
	suffix = ft_strdup(ft_strchr(input, '$') + var_len + 1);
	if (env)
		tmp = ft_strjoin(prefix, env);
	else
		tmp = ft_strjoin(prefix, "");
	result = ft_strjoin(tmp, suffix);
	free(prefix);
	free(suffix);
	free(tmp);
	return (result);
}
char	*ft_substrr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	str = ft_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
char	*expand_variables(char *input,t_shell *shell)
{
	int		i;
	char	*pos;
	char	*key;
	char	*varname;
	char	*result;

	if (!input || !ft_strchr(input, '$'))
		return (ft_strdup(input));
	pos = ft_strchr(input, '$');
	key = pos + 1;
	if (*key == '\0')
		return (ft_strdup(input));
	if(*key == '?')
		{
			result = ft_itoa(shell->last_exit_status);
			return result;
		}
	i = 0;
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
		i++;
	varname = ft_substrr(key, 0, i);
	result = build_result(input, varname, i,shell);
	return (result);
}

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
