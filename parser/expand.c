/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:26:52 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/10 18:35:55 by ahabibi-         ###   ########.fr       */
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
		new = ft_strdup1(str);
	return (new);
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

char	*build_result(char *input, char *varname, int var_len, t_shell *shell)
{
	char	*env_value;
	char	*env_processed;
	char	*prefix;
	char	*suffix;
	char	*tmp;
	char	*result;
	char	*dollar_pos;

	if (strcmp("?", varname) == 0)
		return (ft_itoa(shell->last_exit_status));

	env_value = get_env_value_ll(shell->envv, varname);
	if (env_value)
		env_processed = remove_quotes(env_value);
	else
		env_processed = NULL;

	dollar_pos = ft_strchr(input, '$');
	prefix = ft_substr(input, 0, dollar_pos - input);
	suffix = ft_strdup1(dollar_pos + var_len + 1);

	if (env_processed)
		tmp = ft_strjoin(prefix, env_processed);
	else
		tmp = ft_strjoin(prefix, "");

	result = ft_strjoin(tmp, suffix);

	ft_free_single(prefix);
	ft_free_single(suffix);
	ft_free_single(tmp);
	if (env_processed)
		ft_free_single(env_processed);

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
		return (ft_strdup1(""));
	if (len > s_len - start)
		len = s_len - start;
	str = ft_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

char	*expand_variables(char *input, t_shell *shell)
{
	int		i;
	char	*pos;
	char	*key;
	char	*varname;
	char	*result;

	if (!input || !ft_strchr(input, '$'))
		return (ft_strdup1(input));

	pos = ft_strchr(input, '$');
	key = pos + 1;

	if (*key == '\0')
		return (ft_strdup1(input));
	if (*key == '?')
		return (ft_itoa(shell->last_exit_status));

	i = 0;
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
		i++;

	varname = ft_substrr(key, 0, i);
	result = build_result(input, varname, i, shell);
	ft_free_single(varname);

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
