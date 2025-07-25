/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:46:06 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/25 23:02:53 by salah            ###   ########.fr       */
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
			if ((sa[i] == '<' && sa[i + 1] == '<') ||
				(sa[i] == '>' && sa[i + 1] == '>'))
			{
				i += 2;
				continue;
			}
			j = i + 1;
			while (is_whitespace(sa[j]))
				j++;
			if (is_redirection(sa[j]))
				return (0);
		}
		i++;
	}
	return (1);
}



int	hardcodechecks(char *str)
{
	int	i;
	int	dquote;

	if (!str)
		return (0);
	i = 0;
	dquote = check_quotes_closed(str);
	if (dquote == 1)
		return (0);
	if (red_check(str) == 0 || str[0] == '>' || check_plus(str) == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}

int	red_check(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str) - 1;
	while (str && str[i] && str[i] <= 32)
		i++;
	if (str[i] == '|' || str[len] == '|')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (0);
		if (str[i] == '<' && str[i + 1] == '>')
			return (0);
		if (str[i] == '>' && str[i + 1] == '<')
			return (0);
		if ((str[i] == '>') && (str[i + 1] == '>') && (str[i + 2] == '>'))
			return (0);
		i++;
	}
	return (1);
}
