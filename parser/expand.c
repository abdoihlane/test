/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:26:52 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/11 13:35:21 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_variable_value(char *var_start, int var_len, t_shell *shell)
{
	char	*var_name;
	char	*env_value;

	if (var_len == 1 && *var_start == '?')
		return (ft_itoa(shell->last_exit_status));
	var_name = ft_substr(var_start, 0, var_len);
	env_value = get_env_value_ll(shell->envv, var_name);
	ft_free_single(var_name);
	if (!env_value)
		return (ft_strdup1(""));
	return (ft_strdup1(env_value));
}

char	*build_result_string(char *input, char *dollar_pos, char *env_value,
		int var_len)
{
	char	*result;
	int		prefix_len;
	int		total_len;

	prefix_len = dollar_pos - input;
	total_len = prefix_len + ft_strlen(env_value) + ft_strlen(dollar_pos
			+ var_len + 1);
	result = ft_malloc(total_len + 1);
	ft_strlcpy(result, input, prefix_len + 1);
	ft_strlcat(result, env_value, total_len + 1);
	ft_strlcat(result, dollar_pos + var_len + 1, total_len + 1);
	return (result);
}

char	*expand_variables(char *input, t_shell *shell)
{
	char	*last_dollar;
	char	*env_value;
	char	*result;
	int		var_len;

	if (!input)
		return (NULL);
	last_dollar = find_last_valid_dollar(input);
	if (!last_dollar)
		return (ft_strdup1(input));
	if (*(last_dollar + 1) == '?')
		var_len = 1;
	else
	{
		var_len = get_varname_length(last_dollar + 1);
		if (var_len == 0)
			return (ft_strdup1(input));
	}
	env_value = get_variable_value(last_dollar + 1, var_len, shell);
	result = build_result_string(input, last_dollar, env_value, var_len);
	ft_free_single(env_value);
	return (result);
}

char	*expand_all_variables(char *input, t_shell *shell)
{
	char	*current;
	char	*next;
	int		max_iterations;
	int		iterations;

	max_iterations = 100;
	iterations = 0;
	if (!input || !ft_strchr(input, '$'))
		return (ft_strdup1(input));
	current = ft_strdup1(input);
	while (ft_strchr(current, '$') && iterations < max_iterations)
	{
		next = expand_variables(current, shell);
		if (ft_strcmp(current, next) == 0)
		{
			ft_free_single(next);
			break ;
		}
		ft_free_single(current);
		current = next;
		iterations++;
	}
	return (current);
}

char	*expand_variables_fixed(char *input, t_shell *shell)
{
	char	*first_dollar;
	char	*env_value;
	char	*result;
	int		var_len;

	if (!input)
		return (NULL);
	first_dollar = find_first_valid_dollar(input);
	if (!first_dollar)
		return (ft_strdup1(input));
	if (*(first_dollar + 1) == '?')
		var_len = 1;
	else
	{
		var_len = get_varname_length(first_dollar + 1);
		if (var_len == 0)
			return (ft_strdup1(input));
	}
	env_value = get_variable_value(first_dollar + 1, var_len, shell);
	result = build_result_string(input, first_dollar, env_value, var_len);
	ft_free_single(env_value);
	return (result);
}
