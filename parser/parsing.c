/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:58:39 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/13 10:37:29 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_plus(char *sa)
{
	int	i;
	int	j;

	i = 0;
	while (sa[i])
	{
		if (is_redirection(sa[i]))
		{
			j = i + 1;
			while (is_whitespace(sa[j]))
				j++;
			if (is_redirection(sa[j]) && is_whitespace(sa[j - 1]))
				return (0);
		}
		i++;
	}
	return (1);
}

int	hardcodechecks(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (check_quotes_closed(str))
		return (0);
	if (!red_check(str) || !check_plus(str))
		return (0);
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (0);
		i++;
	}
	return (1);
}

int	check_dup_red(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (0);
		if (str[i] == '<' && str[i + 1] == '>')
			return (0);
		if (str[i] == '>' && str[i + 1] == '<')
			return (0);
		if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			return (0);
		i++;
	}
	return (1);
}

int	red_check(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && is_whitespace(str[i]))
		i++;
	if (str[i] == '|')
		return (0);
	i = ft_strlen(str) - 1;
	while (i > 0 && is_whitespace(str[i]))
		i--;
	if (str[i] == '|')
		return (0);
	i = 0;
	if (check_dup_red(str) == 0)
		return (0);
	return (1);
}
